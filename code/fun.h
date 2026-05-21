#ifndef _fun_h
#define _fun_h
#include "stm32g4xx.h" 


void  led_show(uint8_t led,uint8_t mode);
uint8_t key_scan();
void lcd_show();
void ma();
void key();
double get_vol(ADC_HandleTypeDef *hadc);

#endif