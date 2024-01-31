#ifndef __SENSOR_WATER_ADC_C
#define __SENSOR_WATER_ADC_C
#include "sensor_water_adc.h"
uint16_t temp_val;
uint16_t adcx;
float Get_Adc_Average(uint16_t times){
	uint16_t temp_val;
	uint8_t t;
	for(t=0;t<times;t++){
		temp_val+=HAL_ADC_GetValue(&hadc1);
		HAL_Delay(5);
	}
	return temp_val/times;
}
float Water_read(void){
	uint16_t adcx;
	float voltage;
	adcx=Get_Adc_Average(10);
	voltage=(float)3300000/4096*adcx/1000;
	return voltage;
}

#endif
