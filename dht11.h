#ifndef __DHT11_H__
#define __DHT11_H__

#include "stm32f10x.h"

void DHT11_Init(void);
int DHT11_Read_Data(uint8_t *temp, uint8_t *hum);

#endif
