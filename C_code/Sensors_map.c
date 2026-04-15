#include <stdint.h>
#include <stdbool.h>

#define ADC_MAX        4095.0f
#define VDDA_CALIB    3.0f
#define VREFINT_CAL   (*(uint16_t*)0x1FFF7A2A)

static inline float clampf(float x, float a, float b)
{
    float lo = (a < b) ? a : b;
    float hi = (a < b) ? b : a;
    return (x < lo) ? lo : (x > hi) ? hi : x;
}

static float adc_to_voltage(uint16_t adc_raw, uint16_t adc_vrefint)
{
    float vdda = VDDA_CALIB * ((float)VREFINT_CAL / (float)adc_vrefint);
    return ((float)adc_raw * vdda) / ADC_MAX;
}

float Map_APPS(uint16_t APPS1_raw, uint16_t APPS2_raw, float APPS1_min, float APPS1_max,
               float APPS2_min, float APPS2_max, uint16_t adc_vrefint, bool *improb)
{
    bool implausible = false;

    float apps1_v = adc_to_voltage(APPS1_raw, adc_vrefint);
    float apps2_v = adc_to_voltage(APPS2_raw, adc_vrefint);

    /* Voltage range check */
    if (apps1_v < 0.7f || apps1_v > 2.7f ||
        apps2_v < 0.7f || apps2_v > 2.7f)
    {
        implausible = true;
    }

    /* Clamp to calibrated ranges */
    apps1_v = clampf(apps1_v, APPS1_min, APPS1_max);
    apps2_v = clampf(apps2_v, APPS2_min, APPS2_max);

    /* Map to 0–100 % */
    float apps1 = (apps1_v - APPS1_min) * 100.0f / (APPS1_max - APPS1_min);
    float apps2 = (apps2_v - APPS2_min) * 100.0f / (APPS2_max - APPS2_min);

    /* Plausibility check refer to rulebook */
    float diff = (apps1 > apps2) ? (apps1 - apps2) : (apps2 - apps1);
    if (diff > 10.0f) {
        implausible = true;
    }

    if (improb) {
        *improb = implausible;
    }

    /* Output */
    if (implausible) {
        return 0.0f;
    } else {
        return 0.5f * (apps1 + apps2);
    }
}

float Map_BSE(uint16_t BSE1_raw, uint16_t BSE2_raw, float BSE1_min, float BSE1_max,
               float BSE2_min, float BSE2_max, uint16_t adc_vrefint, bool *improb)
{
    bool implausible = false;

    float bse1_v = adc_to_voltage(BSE1_raw, adc_vrefint);
    float bse2_v = adc_to_voltage(BSE2_raw, adc_vrefint);

    /* Voltage range check */
    if (bse1_v < 0.7f || bse1_v > 2.7f ||
        bse2_v < 0.7f || bse2_v > 2.7f)
    {
        implausible = true;
    }

    /* Clamp to calibrated ranges */
    bse1_v = clampf(bse1_v, BSE1_min, BSE1_max);
    bse2_v = clampf(bse2_v, BSE2_min, BSE2_max);

    /* Map to 0–100 % */
    float bse1 = (bse1_v - BSE1_min) * 100.0f / (BSE1_max - BSE1_min);
    float bse2 = (bse2_v - BSE2_min) * 100.0f / (BSE2_max - BSE2_min);

    if (improb) {
        *improb = implausible;
    }

    /* Output */
    if (implausible) {
        return 100.0f;
    } else {
        return 0.5f * (bse1 + bse2);
    }
}

float Map_SPS(uint16_t SPS_raw, float SPS_min, float SPS_max, uint16_t adc_vrefint, bool *improb)
{
    bool implausible = false;

    float sps_v = adc_to_voltage(SPS_raw, adc_vrefint);

    /* Voltage range check */
    if (sps_v < 0.2f || sps_v > 3.1f)
    {
        implausible = true;
    }

    /* Clamp to calibrated ranges */
    sps_v = clampf(sps_v, SPS_min, SPS_max);

    /* Map to -110–110 deg */
    float sps = (sps_v - SPS_min) * (110.0f - (-110.0f)) / (SPS_max - SPS_min) + (-110.0f);

    if (improb) {
        *improb = implausible;
    }

    /* Output */
    if (implausible) {
        return 0.0f;
    } else {
        return sps;
    }
}
