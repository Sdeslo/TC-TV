#include "CAN_Rx.h"

#ifndef MATLAB_MEX_FILE
#include "main.h"
#endif

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef MATLAB_MEX_FILE

void CAN_Init(void) {}
void CAN_Poll(void) {}

uint32_t CAN_GetFifo0Level(void) { return 0; }
uint32_t CAN_GetFifo1Level(void) { return 0; }

/* BMS */
float CAN_Get_BMS_Min_CV(void) { return 0.0f; }
int16_t CAN_Get_BMS_Max_Temp(void) { return 0; }
bool CAN_Get_BMS_Error(void) { return false; }
bool CAN_Get_BMS_IMD_Error(void) { return false; }

/* DASH */
bool CAN_Get_DASH_Fan_BTN(void)  { return false; }
bool CAN_Get_DASH_Pump_BTN(void) { return false; }
bool CAN_Get_DASH_RTD_BTN(void)  { return false; }
bool CAN_Get_DASH_DEBUG_MODE(void)  { return false; }

/* RCP */
float CAN_Get_RCP_AccelX(void) { return 0.0f; }
float CAN_Get_RCP_AccelY(void) { return 0.0f; }
float CAN_Get_RCP_AccelZ(void) { return 0.0f; }
float CAN_Get_RCP_Pitch(void)  { return 0.0f; }
float CAN_Get_RCP_Roll(void)   { return 0.0f; }
float CAN_Get_RCP_Yaw(void)    { return 0.0f; }

/* DI */
int32_t CAN_Get_DI1_RPM(void)       { return 0; }
float   CAN_Get_DI1_Cont_Temp(void) { return 0.0f; }
float   CAN_Get_DI1_Mot_Temp(void)  { return 0.0f; }
bool    CAN_Get_DI1_Error(void)     { return 0; }

int32_t CAN_Get_DI2_RPM(void)       { return 0; }
float   CAN_Get_DI2_Cont_Temp(void) { return 0.0f; }
float   CAN_Get_DI2_Mot_Temp(void)  { return 0.0f; }
bool    CAN_Get_DI2_Error(void)     { return 0; }

int32_t CAN_Get_DI3_RPM(void)       { return 0; }
float   CAN_Get_DI3_Cont_Temp(void) { return 0.0f; }
float   CAN_Get_DI3_Mot_Temp(void)  { return 0.0f; }
bool    CAN_Get_DI3_Error(void)     { return 0; }

int32_t CAN_Get_DI4_RPM(void)       { return 0; }
float   CAN_Get_DI4_Cont_Temp(void) { return 0.0f; }
float   CAN_Get_DI4_Mot_Temp(void)  { return 0.0f; }
bool    CAN_Get_DI4_Error(void)     { return 0; }

#else 

/* hcan1 is created in main.c */
extern CAN_HandleTypeDef hcan1;

typedef struct
{
    uint8_t data[8];
    uint8_t dlc;
    uint8_t valid;
} MyCanMsg_t;

/* Stored latest messages */
static MyCanMsg_t msg_601;
static MyCanMsg_t msg_501;
static MyCanMsg_t msg_502;

static MyCanMsg_t msg_02040000;
static MyCanMsg_t msg_02070000;

static MyCanMsg_t msg_401;
static MyCanMsg_t msg_441;
static MyCanMsg_t msg_402;
static MyCanMsg_t msg_442;
static MyCanMsg_t msg_403;
static MyCanMsg_t msg_443;
static MyCanMsg_t msg_404;
static MyCanMsg_t msg_444;

/* decoded signals */
static bool DASH_Fan_BTN;
static bool DASH_Pump_BTN;
static bool DASH_RTD_BTN;
static bool DASH_DEBUG_MODE;

static float RCP_AccelX;
static float RCP_AccelY;
static float RCP_AccelZ;
static float RCP_Pitch;
static float RCP_Roll;
static float RCP_Yaw;

static float BMS_Min_CV;
static int16_t BMS_Max_Temp;
static bool BMS_Error;
static bool BMS_IMD_Error;

static int32_t DI1_RPM;
static float DI1_Cont_Temp;
static float DI1_Mot_Temp;
static bool DI1_Error;

static int32_t DI2_RPM;
static float DI2_Cont_Temp;
static float DI2_Mot_Temp;
static bool DI2_Error;

static int32_t DI3_RPM;
static float DI3_Cont_Temp;
static float DI3_Mot_Temp;
static bool DI3_Error;

static int32_t DI4_RPM;
static float DI4_Cont_Temp;
static float DI4_Mot_Temp;
static bool DI4_Error;

static void ClearMsg(MyCanMsg_t *msg)
{
    memset(msg->data, 0, sizeof(msg->data));
    msg->dlc = 0;
    msg->valid = 0;
}

void CAN_Init(void)
{
    ClearMsg(&msg_601);
    ClearMsg(&msg_501);
    ClearMsg(&msg_502);

    ClearMsg(&msg_02040000);
    ClearMsg(&msg_02070000);

    ClearMsg(&msg_401);
    ClearMsg(&msg_441);
    ClearMsg(&msg_402);
    ClearMsg(&msg_442);
    ClearMsg(&msg_403);
    ClearMsg(&msg_443);
    ClearMsg(&msg_404);
    ClearMsg(&msg_444);

    DASH_Fan_BTN = 0;
    DASH_Pump_BTN = 0;
    DASH_RTD_BTN = 0;
    DASH_DEBUG_MODE = 0;

    RCP_AccelX = 0;
    RCP_AccelY = 0;
    RCP_AccelZ = 0;
    RCP_Pitch = 0;
    RCP_Roll = 0;
    RCP_Yaw = 0;

    BMS_Min_CV = 0;
    BMS_Max_Temp = 0;
    BMS_Error = 0;
    BMS_IMD_Error = 0;

    DI1_RPM = 0;
    DI1_Cont_Temp = 0;
    DI1_Mot_Temp = 0;
    DI1_Error = 0;

    DI2_RPM = 0;
    DI2_Cont_Temp = 0;
    DI2_Mot_Temp = 0;
    DI2_Error = 0;

    DI3_RPM = 0;
    DI3_Cont_Temp = 0;
    DI3_Mot_Temp = 0;
    DI3_Error = 0;

    DI4_RPM = 0;
    DI4_Cont_Temp = 0;
    DI4_Mot_Temp = 0;
    DI4_Error = 0;
}

static void StoreRaw(MyCanMsg_t *dst, const uint8_t data[8], uint8_t dlc)
{
    uint8_t i;
    dst->dlc = dlc;
    dst->valid = 1U;

    for (i = 0; i < 8; i++)
    {
        dst->data[i] = data[i];
    }
}

static void Decode_DI(uint32_t id, const uint8_t data[8], uint8_t dlc,
                      int32_t *DI1_RPM, float *DI1_Cont_Temp, float *DI1_Mot_Temp, bool *DI1_Error,
                      int32_t *DI2_RPM, float *DI2_Cont_Temp, float *DI2_Mot_Temp, bool *DI2_Error,
                      int32_t *DI3_RPM, float *DI3_Cont_Temp, float *DI3_Mot_Temp, bool *DI3_Error,
                      int32_t *DI4_RPM, float *DI4_Cont_Temp, float *DI4_Mot_Temp, bool *DI4_Error)
{
    switch (id)
    {
    case 0x401:
        StoreRaw(&msg_401, data, dlc);

        if ((DI1_RPM != NULL) && (dlc >= 6U))
        {
            *DI1_RPM = (((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) | ((uint32_t)data[2] << 8)  | ((uint32_t)data[3])) / 4;
        }
        break;

    case 0x441:
        StoreRaw(&msg_441, data, dlc);

        if (DI1_Cont_Temp != NULL)
        {
            *DI1_Cont_Temp = (float)((((uint16_t)data[0] << 8) | data[1]) / 10.0f);
        }

         if (DI1_Mot_Temp != NULL)
        {
            *DI1_Mot_Temp = (float)((((uint16_t)data[2] << 8) | data[3]) / 10.0f);
        }

        if (DI1_Error != NULL)
        {
            uint8_t byte = data[4];
            *DI1_Error = (byte >= 2 && byte <= 7);
        }
        break;
    
    case 0x402:
        StoreRaw(&msg_402, data, dlc);

        if ((DI2_RPM != NULL) && (dlc >= 6U))
        {
            *DI2_RPM = (((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) | ((uint32_t)data[2] << 8)  | ((uint32_t)data[3])) / 4;
        }
        break;

    case 0x442:
        StoreRaw(&msg_442, data, dlc);

        if ((DI2_Cont_Temp != NULL) && (dlc >= 6U))
        {
            *DI2_Cont_Temp = (float)((((uint16_t)data[0] << 8) | data[1]) / 10.0f);
        }

         if ((DI2_Mot_Temp != NULL) && (dlc >= 6U))
        {
            *DI2_Mot_Temp = (float)((((uint16_t)data[2] << 8) | data[3]) / 10.0f);
        }
        if (DI2_Error != NULL)
        {
            uint8_t byte = data[4];
            *DI2_Error = (byte >= 2 && byte <= 7);
        }
        break;
        
    case 0x403:
        StoreRaw(&msg_403, data, dlc);

        if ((DI3_RPM != NULL) && (dlc >= 6U))
        {
            *DI3_RPM = (((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) | ((uint32_t)data[2] << 8)  | ((uint32_t)data[3])) / 4;
        }
        break;

    case 0x443:
        StoreRaw(&msg_443, data, dlc);

        if ((DI3_Cont_Temp != NULL) && (dlc >= 6U))
        {
            *DI3_Cont_Temp = (float)((((uint16_t)data[0] << 8) | data[1]) / 10.0f);
        }

         if ((DI3_Mot_Temp != NULL) && (dlc >= 6U))
        {
            *DI3_Mot_Temp = (float)((((uint16_t)data[2] << 8) | data[3]) / 10.0f);
        }
        if (DI3_Error != NULL)
        {
            uint8_t byte = data[4];
            *DI3_Error = (byte >= 2 && byte <= 7);
        }
        break;

    case 0x404:
        StoreRaw(&msg_404, data, dlc);

        if ((DI4_RPM != NULL) && (dlc >= 6U))
        {
            *DI4_RPM = (((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) | ((uint32_t)data[2] << 8)  | ((uint32_t)data[3])) / 4;
        }
        break;

    case 0x444:
        StoreRaw(&msg_444, data, dlc);

        if ((DI4_Cont_Temp != NULL) && (dlc >= 6U))
        {
            *DI4_Cont_Temp = (float)((((uint16_t)data[0] << 8) | data[1]) / 10.0f);
        }

        if ((DI4_Mot_Temp != NULL) && (dlc >= 6U))
        {
            *DI4_Mot_Temp = (float)((((uint16_t)data[2] << 8) | data[3]) / 10.0f);
        }
        if (DI4_Error != NULL)
        {
            uint8_t byte = data[4];
            *DI4_Error = (byte >= 2 && byte <= 7);
        }
        break;

    default:
        break;
    }
}

static void Decode_RCP(uint32_t id, const uint8_t data[8], uint8_t dlc,
                       float *RCP_AccelX, float *RCP_AccelY, float *RCP_AccelZ,
                       float *RCP_Pitch, float *RCP_Roll, float *RCP_Yaw)
{
    switch (id)
    {
    case 0x501:
        StoreRaw(&msg_501, data, dlc);

        if ((RCP_AccelX != NULL))
        {
            *RCP_AccelX = (float)((((uint16_t)data[0] << 8) | data[1]) / 100.0f);
        }

         if ((RCP_AccelY != NULL))
        {
            *RCP_AccelY = (float)((((uint16_t)data[2] << 8) | data[3]) / 100.0f);
        }

         if ((RCP_AccelZ != NULL))
        {
            *RCP_AccelZ = (float)((((uint16_t)data[4] << 8) | data[5]) / 100.0f);
        }
        break;

    case 0x502:
        StoreRaw(&msg_502, data, dlc);

        if ((RCP_Yaw != NULL))
        {
            *RCP_Yaw = (float)((((uint16_t)data[0] << 8) | data[1]) / 100.0f);
        }

         if ((RCP_Pitch != NULL))
        {
            *RCP_Pitch = (float)((((uint16_t)data[2] << 8) | data[3]) / 100.0f);
        }

         if ((RCP_Roll != NULL))
        {
            *RCP_Roll = (float)((((uint16_t)data[4] << 8) | data[5]) / 100.0f);
        }
        break;

    default:
        break;
    }
}

static void Decode_DASH(uint32_t id, const uint8_t data[8], uint8_t dlc,
                       bool *DASH_Fan_BTN, bool *DASH_Pump_BTN, bool *DASH_RTD_BTN,
                       bool *DASH_DEBUG_MODE)
{
    switch (id)
    {
    case 0x601:
        StoreRaw(&msg_601, data, dlc);

        if ((DASH_RTD_BTN != NULL))
        {
            *DASH_RTD_BTN = ((data[3]) & 0x01U) != 0U;
        }

         if ((DASH_Pump_BTN != NULL))
        {
            *DASH_Pump_BTN = ((data[3] >> 1) & 0x01U) != 0U;
        }

         if ((DASH_Fan_BTN != NULL))
        {
            *DASH_Fan_BTN = ((data[3] >> 2) & 0x01U) != 0U;
        }

        if ((DASH_DEBUG_MODE != NULL))
        {
            *DASH_DEBUG_MODE = ((data[3] >> 3) & 0x01U) != 0U;
        }
        break;

    default:
        break;
    }
}

static void Decode_BMS(uint32_t id, const uint8_t data[8], uint8_t dlc,
                       bool *BMS_Error, bool *BMS_IMD_Error, float *BMS_Min_CV, int16_t *BMS_Max_Temp)
{
    switch (id)
    {
    case 0x02040000UL:
        StoreRaw(&msg_02040000, data, dlc);

        if (BMS_Min_CV != NULL) 
        {
            *BMS_Min_CV = (float)((((uint16_t)data[0] << 8) | data[1]) / 10000.0f);
        }
        break;
        if (BMS_Max_Temp != NULL) 
        {
            *BMS_Max_Temp = (((uint16_t)data[6] << 8) | data[7]) / 100.0f;
        }
        break;

    case 0x02070000UL:
        StoreRaw(&msg_02070000, data, dlc);

        if (BMS_Error != NULL)
        {
            *BMS_Error = ((data[5] >> 4) & 0x01U) != 0U;
        }

        if (BMS_IMD_Error != NULL)
        {
            *BMS_IMD_Error = ((data[5] >> 1) & 0x01U) != 0U;
        }
        break;

    default:
        break;
    }
}

static void HandleMessage(const CAN_RxHeaderTypeDef *hdr, const uint8_t data[8])
{
    if (hdr->IDE == CAN_ID_STD)
    {
        Decode_DASH(hdr->StdId, data, hdr->DLC, &DASH_Fan_BTN, &DASH_Pump_BTN, &DASH_RTD_BTN,
                    &DASH_DEBUG_MODE);
        Decode_RCP(hdr->StdId, data, hdr->DLC, &RCP_AccelX, &RCP_AccelY, &RCP_AccelZ,
                   &RCP_Pitch, &RCP_Roll, &RCP_Yaw);
        Decode_DI(hdr->StdId, data, hdr->DLC,
                  &DI1_RPM, &DI1_Cont_Temp, &DI1_Mot_Temp, &DI1_Error,
                  &DI2_RPM, &DI2_Cont_Temp, &DI2_Mot_Temp, &DI1_Error,
                  &DI3_RPM, &DI3_Cont_Temp, &DI3_Mot_Temp, &DI1_Error,
                  &DI4_RPM, &DI4_Cont_Temp, &DI4_Mot_Temp, &DI1_Error);
    }
    else
    {
        Decode_BMS(hdr->ExtId, data, hdr->DLC, &BMS_Error, &BMS_IMD_Error, &BMS_Min_CV, &BMS_Max_Temp);
    }
}

static void DrainFifo(uint32_t fifo)
{
    CAN_RxHeaderTypeDef hdr;
    uint8_t data[8];

    while (HAL_CAN_GetRxFifoFillLevel(&hcan1, fifo) > 0U)
    {
        if (HAL_CAN_GetRxMessage(&hcan1, fifo, &hdr, data) == HAL_OK)
        {
            HandleMessage(&hdr, data);
        }
        else
        {
            break;
        }
    }
}

void CAN_Poll(void)
{
    /* Drain both FIFOs fully every call */
    DrainFifo(CAN_RX_FIFO0);
    DrainFifo(CAN_RX_FIFO1);
}

/* FIFO/debug */
uint32_t CAN_GetFifo0Level(void) { return HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0); }
uint32_t CAN_GetFifo1Level(void) { return HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO1); }

/* Public getters */

/* DASH */
bool CAN_Get_DASH_Fan_BTN(void)  { return DASH_Fan_BTN; }
bool CAN_Get_DASH_Pump_BTN(void) { return DASH_Pump_BTN; }
bool CAN_Get_DASH_RTD_BTN(void)  { return DASH_RTD_BTN; }
bool CAN_Get_DASH_DEBUG_MODE(void)  { return DASH_DEBUG_MODE; }

/* RCP */
float CAN_Get_RCP_AccelX(void) { return RCP_AccelX; }
float CAN_Get_RCP_AccelY(void) { return RCP_AccelY; }
float CAN_Get_RCP_AccelZ(void) { return RCP_AccelZ; }
float CAN_Get_RCP_Pitch(void)  { return RCP_Pitch; }
float CAN_Get_RCP_Roll(void)   { return RCP_Roll; }
float CAN_Get_RCP_Yaw(void)    { return RCP_Yaw; }

/* BMS */
float CAN_Get_BMS_Min_CV(void) { return BMS_Min_CV; }
int16_t CAN_Get_BMS_Max_Temp(void) { return BMS_Max_Temp; }
bool CAN_Get_BMS_Error(void)           { return BMS_Error; }
bool CAN_Get_BMS_IMD_Error(void)       { return BMS_IMD_Error; }

/* DI1 */
int32_t CAN_Get_DI1_RPM(void)       { return DI1_RPM; }
float   CAN_Get_DI1_Cont_Temp(void) { return DI1_Cont_Temp; }
float   CAN_Get_DI1_Mot_Temp(void)  { return DI1_Mot_Temp; }
bool    CAN_Get_DI1_Error(void)     { return DI1_Error; }

/* DI2 */
int32_t CAN_Get_DI2_RPM(void)       { return DI2_RPM; }
float   CAN_Get_DI2_Cont_Temp(void) { return DI2_Cont_Temp; }
float   CAN_Get_DI2_Mot_Temp(void)  { return DI2_Mot_Temp; }
bool    CAN_Get_DI2_Error(void)     { return DI2_Error; }

/* DI3 */
int32_t CAN_Get_DI3_RPM(void)       { return DI3_RPM; }
float   CAN_Get_DI3_Cont_Temp(void) { return DI3_Cont_Temp; }
float   CAN_Get_DI3_Mot_Temp(void)  { return DI3_Mot_Temp; }
bool    CAN_Get_DI3_Error(void)     { return DI3_Error; }

/* DI4 */
int32_t CAN_Get_DI4_RPM(void)       { return DI4_RPM; }
float   CAN_Get_DI4_Cont_Temp(void) { return DI4_Cont_Temp; }
float   CAN_Get_DI4_Mot_Temp(void)  { return DI4_Mot_Temp; }
bool    CAN_Get_DI4_Error(void)     { return DI4_Error; }

#endif