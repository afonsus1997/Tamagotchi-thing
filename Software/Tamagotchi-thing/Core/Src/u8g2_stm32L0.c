/*
  ******************************************************************************
  * File Name          : u8x8_stm32_HAL.c
  * Description        : Main program body
  ******************************************************************************
  * �C-spezifische Anweisungen zw. u8g2/u8x8 und stm32
  * Hal-Driver im Einsatz
  ******************************************************************************
*/

#include "u8g2.h"
#include "stm32l0xx_hal.h"
#include "u8x8_stm32_HAL.h"

uint8_t u8x8_stm32_gpio_and_delay_cb(U8X8_UNUSED u8x8_t *u8x8,
                                     uint8_t msg,
                                     uint8_t arg_int,
                                     void *arg_ptr)
{
    switch (msg)
    {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:
        break;
    case U8X8_MSG_DELAY_NANO:
        break;
    case U8X8_MSG_DELAY_100NANO:
        break;
    case U8X8_MSG_DELAY_10MICRO:
        for (uint32_t i = 0; i < (SystemCoreClock / 1000000) * 10 * arg_int / 5; i++) {
            __NOP();
        }
        break;
    case U8X8_MSG_DELAY_MILLI:
        HAL_Delay(arg_int);
        break;
    case U8X8_MSG_DELAY_I2C:
        for (volatile uint32_t i = 0; i < 10; i++) {
            __NOP();
        }
        break;
    case U8X8_MSG_GPIO_RESET:
        // Optional: control a RESET GPIO if your SH1106 has one
        // HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, arg_int ? GPIO_PIN_SET : GPIO_PIN_RESET);
        break;
    default:
        break;
    }
    return 1;
}
 //   case U8X8_MSG_GPIO_MENU_SELECT:
 //     u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
 //     break;
 //   case U8X8_MSG_GPIO_MENU_NEXT:
 //     u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
 //     break;
 //   case U8X8_MSG_GPIO_MENU_PREV:
 //     u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
 //     break;
 //   case U8X8_MSG_GPIO_MENU_HOME:
 //     u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
 //     break;
 //   default:
 //     u8x8_SetGPIOResult(u8x8, 1);	*/		// default return value


uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8,
                         uint8_t msg,
                         uint8_t arg_int,
                         void *arg_ptr)
{
    static uint8_t buffer[DATA_BUFFER_SIZE];
    static uint8_t buffer_count;
    uint8_t *data;

    switch (msg)
    {
    case U8X8_MSG_BYTE_SEND:
        data = (uint8_t *)arg_ptr;
        for (uint8_t i = 0; i < arg_int && buffer_count < DATA_BUFFER_SIZE; i++) {
            buffer[buffer_count++] = *data++;
        }
        break;

    case U8X8_MSG_BYTE_INIT:
        // Already initialized elsewhere
        break;

    case U8X8_MSG_BYTE_SET_DC:
        // Not used for I2C
        break;

    case U8X8_MSG_BYTE_START_TRANSFER:
        buffer_count = 0;
        break;

    case U8X8_MSG_BYTE_END_TRANSFER:
        if (HAL_I2C_Master_Transmit(&I2C_HANDLER, DEVICE_ADDRESS, buffer, buffer_count, HAL_MAX_DELAY) != HAL_OK) {
            // Handle error
            return 0;
        }
        break;

    default:
        return 0;
    }

    return 1;
}
