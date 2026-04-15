#pragma once

#include <stdbool.h>

#ifdef MATLAB_MEX_FILE
  #include <stdint.h>
  typedef uint32_t uint32_T;   // Make Simulink-style type exist in PC simulation
#else
  #include "rtwtypes.h"        // Provides uint32_T for code generation
#endif

#ifdef __cplusplus
extern "C" {
#endif

bool FaultNv_Read(uint32_T *outMask);
bool FaultNv_Write(uint32_T mask);
bool FaultNv_Clear(void);

#ifdef __cplusplus
}
#endif
