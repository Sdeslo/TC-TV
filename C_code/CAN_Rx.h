#ifndef CAN_RX_H
#define CAN_RX_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void CAN_Init(void);
void CAN_Poll(void);

/* FIFO/debug info */
uint32_t CAN_GetFifo0Level(void);
uint32_t CAN_GetFifo1Level(void);

/* DASH */
bool CAN_Get_DASH_Fan_BTN(void);
bool CAN_Get_DASH_Pump_BTN(void);
bool CAN_Get_DASH_RTD_BTN(void);
bool CAN_Get_DASH_DEBUG_MODE(void);

/* RCP */
float CAN_Get_RCP_AccelX(void);
float CAN_Get_RCP_AccelY(void);
float CAN_Get_RCP_AccelZ(void);
float CAN_Get_RCP_Pitch(void);
float CAN_Get_RCP_Roll(void);
float CAN_Get_RCP_Yaw(void);

/* BMS */
float CAN_Get_BMS_Min_CV(void);
int16_t CAN_Get_BMS_Max_Temp(void);
bool CAN_Get_BMS_Error(void);
bool CAN_Get_BMS_IMD_Error(void);

/* DI1 */
int32_t CAN_Get_DI1_RPM(void);
float CAN_Get_DI1_Cont_Temp(void);
float CAN_Get_DI1_Mot_Temp(void);
bool CAN_Get_DI1_Error(void);

/* DI2 */
int32_t CAN_Get_DI2_RPM(void);
float CAN_Get_DI2_Cont_Temp(void);
float CAN_Get_DI2_Mot_Temp(void);
bool CAN_Get_DI2_Error(void);

/* DI3 */
int32_t CAN_Get_DI3_RPM(void);
float CAN_Get_DI3_Cont_Temp(void);
float CAN_Get_DI3_Mot_Temp(void);
bool CAN_Get_DI3_Error(void);

/* DI4 */
int32_t CAN_Get_DI4_RPM(void);
float CAN_Get_DI4_Cont_Temp(void);
float CAN_Get_DI4_Mot_Temp(void);
bool CAN_Get_DI4_Error(void);

#ifdef __cplusplus
}
#endif

#endif