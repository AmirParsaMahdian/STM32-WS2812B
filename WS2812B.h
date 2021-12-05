#ifndef WS2812B_H
#define WS2812B_H

#include "stm32f030x6.h"

/* Total number of LEDs */
#define LED_NUM 6


void WS2812B_Init(void);
void WS_Queue(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void WS_Send(void);

#endif // WS2812B_H
