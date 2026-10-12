#include "rgb.h"

void RGB_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    RGB_SetColor(RGB_OFF);
}

void RGB_SetColor(RGB_Color_t color) {
    GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10);
    switch(color) {
        case RED:   GPIO_SetBits(GPIOB, GPIO_Pin_0); break;
        case GREEN: GPIO_SetBits(GPIOB, GPIO_Pin_1); break;
        case BLUE:  GPIO_SetBits(GPIOB, GPIO_Pin_10); break;
        default: break;
    }
}
