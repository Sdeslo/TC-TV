#include <stdint.h>
#include <stdbool.h>
#include <math.h>

static inline float minf_custom(float a, float b)
{
    return (a < b) ? a : b;
}

static inline float maxf_custom(float a, float b)
{
    return (a > b) ? a : b;
}

static inline float clampf_custom(float x, float xmin, float xmax)
{
    return maxf_custom(xmin, minf_custom(x, xmax));
}

// #TODO
// Function to recreate the Dynamic drive curve generator from Schwarzmuler Inverter 
// refer to Bloc DDCG.pdf
void torque_DDCG(float* torque, float* last_torque, float max_accel, float degree)
{
    float delta = *torque - *last_torque;

    float step = powf(fabsf(delta), degree);
    step = minf_custom(step, max_accel);

    float new_torque;

    if (delta > 0)
        new_torque = *last_torque + step;
    else if (delta < 0)
        new_torque = *last_torque - step;
    else
        new_torque = *last_torque;

    *torque = clampf_custom(new_torque, 0.0f, 100.0f);
    *last_torque = *torque;
}


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
    float torque_pct)
{
    float steering_used = steering_deg;
    float ay_used = ay;
    float ax_used = ax;

    float yawRateTarget_deg_s;
    float yawError_deg_s;

    // Deadbands + enable
    if (fabsf(steering_used) < steer_deadband_deg || torque_pct < torque_enable_threshold)
        steering_used = 0.0f;

    if (fabsf(ay_used) < ay_deadband || torque_pct < torque_enable_threshold)
        ay_used = 0.0f;

    // Target yaw from steering
    yawRateTarget_deg_s = steering_gain * steering_used;

    // Yaw error
    yawError_deg_s = yawRateTarget_deg_s - yawRate_deg_s;

    if (fabsf(yawError_deg_s) < yaw_deadband_deg_s || torque_pct < torque_enable_threshold)
        yawError_deg_s = 0.0f;

    // TV command = feedforward + feedback
    float ff = ay_gain * ay_used;
    float fb = yaw_gain * yawError_deg_s;

    *deltaYaw = clampf_custom(ff + fb, -deltaYaw_max, deltaYaw_max);

    // Front torque reduction
    if (fabsf(ax_used) < ax_deadband || torque_pct < torque_enable_threshold)
        ax_used = 0.0f;

    if (ax_used > 0.0f)
    {
        float axNorm = clampf_custom(ax_used / maxAx, 0.0f, 1.0f);
        *frontTorqueReduction = (front_reduc_pct * axNorm) / 100.0f;
    }
    else
    {
        *frontTorqueReduction = 0.0f;
    }
}