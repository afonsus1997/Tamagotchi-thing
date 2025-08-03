/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External TIM handles */
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;

/* USER CODE BEGIN Private defines */

/* MCU timer frequency settings (timer tick frequency) */
#define MCU_TIME_FREQ_NUM    131072ULL       // Approximate timer frequency (ticks per second)
#define MCU_TIME_FREQ_DEN    1000000ULL      // Denominator for frequency calculation (microseconds base)

/* Convert microseconds to MCU timer ticks */
#define US_TO_MCU_TIME(t)    (((uint64_t)(t) * MCU_TIME_FREQ_NUM + MCU_TIME_FREQ_DEN - 1) / MCU_TIME_FREQ_DEN)

/* Convert milliseconds to MCU timer ticks */
#define MS_TO_MCU_TIME(t)    (US_TO_MCU_TIME((uint64_t)(t) * 1000ULL))

/* Timer frequency scaled by 1,000 (for convenience, if needed) */
#define MCU_TIME_FREQ_X1000  ((1000000000ULL / MCU_TIME_FREQ_DEN) * MCU_TIME_FREQ_NUM)

typedef uint32_t mcu_time_t;

/* USER CODE END Private defines */

/* Initialization functions */
void MX_TIM3_Init(void);
void MX_TIM6_Init(void);
void MX_TIM7_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN Prototypes */

void time_init(void);

mcu_time_t time_get(void);
void time_wait_until(mcu_time_t time);
void time_delay(mcu_time_t time);
void TIM6_DAC_IRQHandler_user(void);/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */
