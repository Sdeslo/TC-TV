#ifndef TV_H
#define TV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* Torque ramp / DDCG */
void torque_DDCG(float *torque,
                 float *last_torque,
                 float max_accel,
                 float degree);

/* Torque vectoring + front torque reduction */
void computeTorqueAdjustments(
    float ax,
    float ay,
    float steering_deg,
    float yawRate_deg_s,

    float *deltaYaw,
    float *frontTorqueReduction,

    float steering_gain,
    float ay_gain,
    float yaw_gain,

    float steer_deadband_deg,
    float ay_deadband,
    float yaw_deadband_deg_s,
    float deltaYaw_max,

    float ax_deadband,
    float maxAx,
    float front_reduc_pct,

    float torque_enable_threshold,
    float torque_pct);

#ifdef __cplusplus
}
#endif

#endif /* TV_H */
