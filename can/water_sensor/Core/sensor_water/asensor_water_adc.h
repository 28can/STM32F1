#ifndef __SENSOR_WATER_ADC_H
#define __SENSOR_WATER_ADC_H

#include "stdint.h"
#include "adc.h"

float Get_Adc_Average(uint16_t times);
float  Water_read(void);

#endif

