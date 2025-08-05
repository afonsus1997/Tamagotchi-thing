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
// Timekeeping definitions and functions
typedef uint32_t mcu_time_t;


// Timer base frequency (TIM6): 131.072 kHz
#define SET_FRAMERATE 3           //3fps for 131147ULL 
#define MCU_TIME_FREQ_HZ          (1000000ULL)
#define MCU_TIME_FREQ_X1000       (MCU_TIME_FREQ_HZ * 1000ULL)
#define US_TO_MCU_TIME(t)         (((t) * MCU_TIME_FREQ_HZ + 999999ULL) / 1000000ULL)
#define MS_TO_MCU_TIME(t)         (((t) * MCU_TIME_FREQ_HZ + 999ULL) / 1000ULL)
/* USER CODE END Includes */

extern TIM_HandleTypeDef htim3;

extern TIM_HandleTypeDef htim6;

extern TIM_HandleTypeDef htim7;

/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */

void MX_TIM3_Init(void);
void MX_TIM6_Init(void);
void MX_TIM7_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN Prototypes */



void tim_increment_ticks();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

