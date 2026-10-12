#include "dht11.h"
#include "systick.h"

static void DHT11_Mode_Out(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void DHT11_Mode_In(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DHT11_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    DHT11_Mode_Out();
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
}

int DHT11_Read_Data(uint8_t *temp, uint8_t *hum) {
    uint8_t data[5] = {0};
    uint8_t i, j;

    DHT11_Mode_Out();
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    delay_ms(20);
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    delay_us(30);

    DHT11_Mode_In();
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == SET) return -1;
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == RESET);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == SET);

    for(i = 0; i < 5; i++) {
        for(j = 0; j < 8; j++) {
            while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == RESET);
            delay_us(30);
            if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == SET) {
                data[i] |= (1 << (7 - j));
                while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == SET);
            }
        }
    }

    if(data[0] + data[1] + data[2] + data[3] == data[4]) {
        *hum = data[0];
        *temp = data[2];
        return 0;
    }
    return -1;
}
