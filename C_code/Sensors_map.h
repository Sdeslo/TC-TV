#pragma once

#include <stdint.h>
#include <stdbool.h>


float Map_APPS(uint16_t APPS1_raw, uint16_t APPS2_raw, float APPS1_min,
               float APPS1_max, float APPS2_min, float APPS2_max, uint16_t adc_vrefint, bool *improb);

float Map_BSE(uint16_t BSE1_raw, uint16_t BSE2_raw, float BSE1_min, float BSE1_max,
               float BSE2_min, float BSE2_max, uint16_t adc_vrefint, bool *improb);

float Map_SPS(uint16_t SPS_raw, float SPS_min, float SPS_max, uint16_t adc_vrefint, bool *improb);
