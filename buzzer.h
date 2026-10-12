#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "stm32f10x.h"

void Buzzer_Init(void);
void Buzzer_SetFreq(uint16_t freq);
void Buzzer_Off(void);

#endif
