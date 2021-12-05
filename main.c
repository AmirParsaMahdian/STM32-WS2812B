#include "main.h"
#include "config.h"

int main(void)
{
	FLASH_Init();
	RCC_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	NVIC_SetPriority(SysTick_IRQn, 14);
	GPIO_Init();
	
	WS2812B_Init();
	
	while(1)
	{
		for (uint8_t i = 0; i < LED_NUM; i++) WS_Queue(i, 140, 0, 0);
		WS_Send();
		TIM_Delay(500);
		
		for (uint8_t i = 0; i < LED_NUM; i++) WS_Queue(i, 0, 140, 0);
		WS_Send();
		TIM_Delay(500);
		
		for (uint8_t i = 0; i < LED_NUM; i++) WS_Queue(i, 0, 0, 140);
		WS_Send();
		TIM_Delay(500);
		
		for (uint8_t i = 0; i < LED_NUM; i++) WS_Queue(i, 80, 80, 0);
		WS_Send();
		TIM_Delay(500);
		
		for (uint8_t i = 0; i < LED_NUM; i++) WS_Queue(i, 50, 0, 100);
		WS_Send();
	}
}
