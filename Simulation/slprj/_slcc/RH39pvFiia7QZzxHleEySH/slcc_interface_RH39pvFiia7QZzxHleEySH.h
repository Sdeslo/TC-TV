#include "customcode_RH39pvFiia7QZzxHleEySH.h"
#ifdef __cplusplus
extern "C" {
#endif


/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
DLL_EXPORT_CC extern const char_T *get_dll_checksum_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T FaultNv_Read_RH39pvFiia7QZzxHleEySH(uint32_T *outMask);
DLL_EXPORT_CC extern boolean_T FaultNv_Write_RH39pvFiia7QZzxHleEySH(uint32_T mask);
DLL_EXPORT_CC extern boolean_T FaultNv_Clear_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T Map_APPS_RH39pvFiia7QZzxHleEySH(uint16_T APPS1_raw, uint16_T APPS2_raw, real32_T APPS1_min, real32_T APPS1_max, real32_T APPS2_min, real32_T APPS2_max, uint16_T adc_vrefint, boolean_T *improb);
DLL_EXPORT_CC extern real32_T Map_BSE_RH39pvFiia7QZzxHleEySH(uint16_T BSE1_raw, uint16_T BSE2_raw, real32_T BSE1_min, real32_T BSE1_max, real32_T BSE2_min, real32_T BSE2_max, uint16_T adc_vrefint, boolean_T *improb);
DLL_EXPORT_CC extern real32_T Map_SPS_RH39pvFiia7QZzxHleEySH(uint16_T SPS_raw, real32_T SPS_min, real32_T SPS_max, uint16_T adc_vrefint, boolean_T *improb);
DLL_EXPORT_CC extern void CAN_Init_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern void CAN_Poll_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern uint32_T CAN_GetFifo0Level_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern uint32_T CAN_GetFifo1Level_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_DASH_Fan_BTN_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_DASH_Pump_BTN_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_DASH_RTD_BTN_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_DASH_DEBUG_MODE_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_DASH_BLEED_MODE_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_RCP_AccelX_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_RCP_AccelY_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_RCP_AccelZ_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_RCP_Pitch_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_RCP_Roll_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_RCP_Yaw_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_BMS_Min_CV_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern int16_T CAN_Get_BMS_Max_Temp_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_BMS_Error_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_BMS_IMD_Error_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern int32_T CAN_Get_DI1_RPM_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_DI1_Cont_Temp_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_DI1_Mot_Temp_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_DI1_Error_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern int32_T CAN_Get_DI2_RPM_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_DI2_Cont_Temp_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_DI2_Mot_Temp_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_DI2_Error_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern int32_T CAN_Get_DI3_RPM_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_DI3_Cont_Temp_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_DI3_Mot_Temp_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_DI3_Error_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern int32_T CAN_Get_DI4_RPM_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_DI4_Cont_Temp_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern real32_T CAN_Get_DI4_Mot_Temp_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern boolean_T CAN_Get_DI4_Error_RH39pvFiia7QZzxHleEySH(void);
DLL_EXPORT_CC extern void torque_DDCG_RH39pvFiia7QZzxHleEySH(real32_T *torque, real32_T *last_torque, real32_T max_accel);
DLL_EXPORT_CC extern void computeTorqueAdjustments_RH39pvFiia7QZzxHleEySH(real32_T ax, real32_T ay, real32_T mass, real32_T cgHeight, real32_T trackWidth, real32_T wheelRadius, real32_T maxAx, real32_T *deltaYaw, real32_T *frontTorqueReduction, real32_T power_limiter_pct, real32_T front_reduc_pct, real32_T max_torque, real32_T roll_to_yaw_gain);

/* Function Definitions */
DLL_EXPORT_CC const uint8_T *get_checksum_source_info(int32_T *size);
#ifdef __cplusplus
}
#endif

