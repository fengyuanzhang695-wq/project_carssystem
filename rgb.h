#ifndef __RGB_H__
#define __RGB_H__

#include "stm32f10x.h"

typedef enum { RGB_OFF = 0, RED, GREEN, BLUE } RGB_Color_t;

void RGB_Init(void);
void RGB_SetColor(RGB_Color_t color);

#endif
