#ifndef ADXL_H
#define ADXL_H

#include "stm32f10x.h"
#include <math.h>

#define CS_ON()		GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define CS_OFF()	GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define LED_ON()		GPIO_ResetBits(GPIOC, GPIO_Pin_9)
#define LED_OFF()	GPIO_SetBits(GPIOC, GPIO_Pin_9)

void adxl_read(uint16_t temp[]);
void adxl_init(void);
void GPIO_Configuration(void);
void SPI_ini(void);
#endif
