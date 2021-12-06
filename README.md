
# STM32-WS2812B


This is a project to run WS2812B LEDs with an STM32 microcontroller. This library is written in register code and uses double-buffer DMA and PWM to produce the data signal with a minimal processor and memory consumption.

While this is written for an STM32F030K6T6 MCU, it can be configured to work with other STM32 MCUs as well.
I believe it can be used for other WS variants by changing the timing and sequence of the data signal. The IDE used is Keil MDK Version 5.


## Configuration

Firstly, for the data pin, choose an I/O pin having a timer capable of generating PWM signals.

### In `config.h`:
Specify the pin number and port of your data pin.
```c
#define RGB_DATA_Pin 				6U
#define RGB_DATA_GPIO_Port 			GPIOA
```

### In `WS2812B.h`:
Specify the number of LEDs.
```c
#define LED_NUM 6
```

### In `GPIO.c`:
Enable the peripheral clock of the data pin port.
```c
RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* Enable GPIOA clock */
```

Find the alternate function corresponding to the timer on the data pin. For example, in the corresponding [datasheet](https://www.st.com/resource/en/datasheet/stm32f030k6.pdf) under *Alternate functions selected through GPIOA_AFR*:

| Pin name | AF0       | AF1      | AF2       | AF3 | AF4        | AF5           | AF6      |
| :------: | :-------: | :------: | :-------: | :-: | :--------: | :-----------: | :------: |
| PA5      | SPI1_MISO | TIM3_CH1 | TIM1_BKIN | -   | USART3_CTS | **TIM16_CH1** | EVENTOUT |

Set the alternate function to be the timer on the pin.
```c
RGB_DATA_GPIO_Port->AFR[0] |= 5U << (RGB_DATA_Pin << 2); /* Alternate function (TIM16_CH1 AF5) */
```

### In `WS2812B.c`:
Replace `TIM16` with the timer used.

Find the DMA channel corresponding to TIMx_UP. For example, in the corresponding [reference manual](https://www.st.com/resource/en/reference_manual/rm0360-stm32f030x4x6x8xc-and-stm32f070x6xb-advanced-armbased-32bit-mcus-stmicroelectronics.pdf) under *DMA interrupts*:

| Pin Peripherals | Channel 1 | Channel 2 | Channel 3                        | Channel 4                    | Channel 5 |
| :-------------: | :-------: | :-------: | :------------------------------: | :--------------------------: | :-------: |
| TIM16           | -         | -         | TIM16_CH1(1)<br/>**TIM16_UP(1)** | TIM16_CH1(2)<br/>TIM16_UP(2) | -         |

Replace `DMA1_Channel3` with the new DMA channel.

Enable the peripheral clock of the timer.
```c
RCC->APB2ENR |= RCC_APB2ENR_TIM16EN; /* Enable TIM16 clock */
```
Enable the timer channel corresponding to the data pin.
```c
TIM16->CCER |= TIM_CCER_CC1E; /* Enable capture/compare 1 output */
```

### In `DMA.c`:
Enable the peripheral clock of the DMA.
```c
RCC->AHBENR |= RCC_AHBENR_DMA1EN;
```
## Usage

First queue all the changes that should happen at once using `WS_Queue(uint8_t index, uint8_t r, uint8_t g, uint8_t b)`.
```c
WS_Queue(0, 140, 0, 0);
WS_Queue(1, 0, 140, 0);
WS_Queue(2, 0, 0, 140);
```

To apply the changes, call `WS_Send()`.
```c
WS_Send();
```

In addition, the `TIM_Delay(uint32_t ms)` function can be used to create delays in ms.
```c
TIM_Delay(500);
```


## Author

- [@AmirParsaMahdian](https://www.github.com/AmirParsaMahdian)


## License

[MIT](https://choosealicense.com/licenses/mit/)

