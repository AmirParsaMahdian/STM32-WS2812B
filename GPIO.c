#include "GPIO.h"
#include "config.h"

void GPIO_Init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* Enable GPIOA clock */
	
	RGB_DATA_GPIO_Port->MODER |= 0x02U << (RGB_DATA_Pin << 1); /* Alternate function mode */
	RGB_DATA_GPIO_Port->AFR[0] |= 5U << (RGB_DATA_Pin << 2); /* Alternate function (TIM16_CH1 AF5) */
	RGB_DATA_GPIO_Port->OSPEEDR |= 0b11 << (RGB_DATA_Pin << 1); /* output high-speed */
}
