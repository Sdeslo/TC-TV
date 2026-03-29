#include <stdint.h>
#include <stdbool.h>

static inline float min(float a, float b)
{
    return (a < b) ? a : b;
}

static inline float max(float a, float b)
{
    return (a > b) ? a : b;
}

// #TODO
// Function to recreate the Dynamic drive curve generator from Schwarzmuler Inverter 
// refer to Bloc DDCG.pdf
void torque_DDCG(float* torque, float* last_torque, float max_accel)
{
    float delta = *torque - *last_torque;

    float step = delta * delta;

    // limit step
    step = min(step, max_accel);

    if (delta > 0)
    {
        *torque = *last_torque + step;
    }
    else if (delta < 0)
    {
        *torque = *last_torque - step;
    }
    else
    {
        *torque = *last_torque;
    }
}

// Cahnged Macros to parameters for params
// Compute torque vectoring correction and front wheel torque reduction
void computeTorqueAdjustments(
    float ax, float ay,              // Longitudinal and lateral acceleration [m/s^2]
    float mass,                      // Vehicle mass [kg]
    float cgHeight,                 // CG height [m]
    float trackWidth,               // Track width [m]    
    float wheelRadius,
    float maxAx,                    // Max expected acceleration for scaling
    float* deltaYaw,                // [out] torque delta for yaw correction
    float* frontTorqueReduction,     // [out] torque reduction for front axle
    float power_limiter_pct,         // power limiter [%]
    float front_reduc_pct,           // max front torque reduction [%]
    float max_torque,                // max torque [Nm]
    float roll_to_yaw_gain)
    {
    // Roll moment calculation
    float Mx = mass * ay * cgHeight;
    float Mz = Mx * roll_to_yaw_gain; //misleading name should be changed
    float torqueDiff = (Mz * 2 * wheelRadius) / trackWidth;
    float torque1 = max_torque * power_limiter_pct;
    float torque2 = max_torque * power_limiter_pct;
    float torque3 = max_torque * power_limiter_pct;
    float torque4 = max_torque * power_limiter_pct;
    if (ay > 0){
        *deltaYaw = (torqueDiff / max((torque2 + torque4), 1.0f)) * 100;
    }
    
    if (ay < 0){
        *deltaYaw = (torqueDiff / max((torque1 + torque3), 1.0f)) * 100;
    }
    *deltaYaw = max(-1.0f, min(1.0f, *deltaYaw));
    // Front Torque Reduction from Longitudinal Acceleration 
    // Normalize ax to [0, 1]
    float axNorm = max(0, min(1, ax / maxAx));

    // Define how much of front torque can be reduced at full acceleration
    *frontTorqueReduction = (front_reduc_pct * axNorm) / 100;  // 0.0 to 0.3 (fraction of front torque)
}