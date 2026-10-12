#include "hcsr04.h"
#include "systick.h"

void HCSR04_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    // Trig - PB6
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Echo - PB7
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_Cmd(TIM4, DISABLE);
}

float HCSR04_GetValue(void) {
    uint32_t time = 0;
    GPIO_SetBits(GPIOB, GPIO_Pin_6);
    delay_us(15);
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);

    uint16_t timeout = 0;
    while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == RESET) {
        timeout++;
        if(timeout > 50000) return -1.0f;
    }

    TIM_SetCounter(TIM4, 0);
    TIM_Cmd(TIM4, ENABLE);

    while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == SET);

    TIM_Cmd(TIM4, DISABLE);
    time = TIM_GetCounter(TIM4);

    return ((float)time * 0.017f);
}
