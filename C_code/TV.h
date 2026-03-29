#ifndef TV_H
#define TV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

void torque_DDCG(float *torque,
                 float *last_torque,
                 float    max_accel);

void computeTorqueAdjustments(float  ax,
                              float  ay,
                              float  mass,
                              float  cgHeight,
                              float  trackWidth,
                              float  wheelRadius,
                              float  maxAx,
                              float *deltaYaw,
                              float *frontTorqueReduction,
                              float  power_limiter_pct,
                              float  front_reduc_pct,
                              float  max_torque,
                              float  roll_to_yaw_gain);

#ifdef __cplusplus
}
#endif

#endif 
