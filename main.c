#include "stm32f10x.h"
#include "systick.h"
#include "oled.h"
#include "hcsr04.h"
#include "dht11.h"
#include "buzzer.h"
#include "motor.h"
#include "rgb.h"

int main(void) {
    delay_init();
    OLED_Init();
    OLED_Clear();
    HCSR04_Init();
    DHT11_Init();
    Buzzer_Init();
    Motor_Init();
    RGB_Init();

		OLED_Clear();
		Delay_50ms(20);
    OLED_ShowString(0, 0, (uint8_t*)"Dist:    cm", 16);
    OLED_ShowString(0, 2, (uint8_t*)"Temp:    C", 16);
    OLED_ShowString(0, 4, (uint8_t*)"Humi:    RH", 16);

    float distance = 0.0f;
    uint8_t temp = 0, humi = 0;
	

    while(1) {
        
        distance = HCSR04_GetValue();
        if(distance >= 0) {
            OLED_ShowNum(48, 0, (uint32_t)distance, 3, 16);
        }

        if(distance > 0 && distance < 10.0f) {
            Buzzer_SetFreq(2000);  
        } else if(distance >= 10.0f && distance < 30.0f) {
            Buzzer_SetFreq(500);   
        } else {
            Buzzer_Off();          
        }

        
        if(DHT11_Read_Data(&temp, &humi) == 0) {
            OLED_ShowNum(48, 2, temp, 2, 16);
            OLED_ShowNum(48, 4, humi, 2, 16);

            if(temp < 25) {
                RGB_SetColor(BLUE);     
                Motor_SetSpeed(0);
            } else if(temp <= 27) {
                RGB_SetColor(GREEN);    
                Motor_SetSpeed(50);
            } else {
                RGB_SetColor(RED);      
                Motor_SetSpeed(100);
            }
        }

        delay_ms(150);
    }
}
