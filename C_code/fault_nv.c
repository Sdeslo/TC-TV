#include "fault_nv.h"

#ifdef MATLAB_MEX_FILE
// =====================
// PC simulation (MEX)
// =====================

static uint32_T sim_mask = 0u;

bool FaultNv_Read(uint32_T *outMask)
{
  if (!outMask) return false;
  *outMask = sim_mask;
  return true;
}

bool FaultNv_Write(uint32_T mask)
{
  sim_mask = mask;
  return true;
}

bool FaultNv_Clear(void)
{
  sim_mask = 0u;
  return true;
}

#else
// =====================
// Embedded STM32 build
// =====================

#include <stdint.h>                 // uintptr_t
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_flash_ex.h"

// F446RE: Sector 7 base (last sector if 512KB flash layout)
// IMPORTANT: Make sure your linker/script does NOT place code/data in this sector.
#define FAULT_NV_BASE        (0x08060000u)
#define FAULT_NV_MAX_BYTES   (128u * 1024u)   // Sector 7 size

#define FAULT_MAGIC          (0xF411FA17u)
#define FAULT_VERSION        (1u)

typedef struct
{
  uint32_T magic;
  uint32_T version;
  uint32_T mask;
  uint32_T invmask;   // integrity check: invmask == ~mask
} FaultRecord;

static uint32_T record_count_max(void)
{
  return (uint32_T)(FAULT_NV_MAX_BYTES / (uint32_T)sizeof(FaultRecord));
}

static volatile const FaultRecord* record_ptr(uint32_T idx)
{
  return (volatile const FaultRecord*)((uintptr_t)FAULT_NV_BASE +
         (uintptr_t)idx * (uintptr_t)sizeof(FaultRecord));
}

static bool record_valid(volatile const FaultRecord* r)
{
  return (r->magic   == (uint32_T)FAULT_MAGIC) &&
         (r->version == (uint32_T)FAULT_VERSION) &&
         (r->invmask == (uint32_T)(~r->mask));
}

bool FaultNv_Read(uint32_T *outMask)
{
  if (!outMask) return false;

  uint32_T lastMask = 0u;
  bool found = false;

  for (uint32_T i = 0u; i < record_count_max(); i++)
  {
    volatile const FaultRecord* r = record_ptr(i);

    // Empty flash word is 0xFFFFFFFF
    if ((uint32_t)r->magic == 0xFFFFFFFFu) break;

    if (record_valid(r))
    {
      lastMask = r->mask;
      found = true;
    }
  }

  *outMask = found ? lastMask : 0u;
  return true;
}

static bool flash_write_record(const FaultRecord* rec)
{
  // Find first empty slot
  uint32_T i;
  for (i = 0u; i < record_count_max(); i++)
  {
    volatile const FaultRecord* r = record_ptr(i);
    if ((uint32_t)r->magic == 0xFFFFFFFFu) break;
  }

  if (i >= record_count_max())
  {
    // Sector full -> erase then start over
    if (!FaultNv_Clear()) return false;
    i = 0u;
  }

  uint32_t addr = (uint32_t)(uintptr_t)record_ptr(i);

  HAL_FLASH_Unlock();

  // Program as 32-bit words
  const uint32_T* w = (const uint32_T*)rec;
  const uint32_T nwords = (uint32_T)(sizeof(FaultRecord) / 4u);

  for (uint32_T k = 0u; k < nwords; k++)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,
                          addr + 4u*(uint32_t)k,
                          (uint32_t)w[k]) != HAL_OK)
    {
      HAL_FLASH_Lock();
      return false;
    }
  }

  HAL_FLASH_Lock();
  return true;
}

bool FaultNv_Write(uint32_T mask)
{
  FaultRecord rec;
  rec.magic   = (uint32_T)FAULT_MAGIC;
  rec.version = (uint32_T)FAULT_VERSION;
  rec.mask    = mask;
  rec.invmask = (uint32_T)(~mask);

  return flash_write_record(&rec);
}

bool FaultNv_Clear(void)
{
  HAL_FLASH_Unlock();

  FLASH_EraseInitTypeDef erase;
  uint32_t sectorError = 0u;

  erase.TypeErase    = FLASH_TYPEERASE_SECTORS;
  erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
  erase.Sector       = FLASH_SECTOR_7;
  erase.NbSectors    = 1u;

  HAL_StatusTypeDef st = HAL_FLASHEx_Erase(&erase, &sectorError);

  HAL_FLASH_Lock();
  return (st == HAL_OK);
}

#endif
