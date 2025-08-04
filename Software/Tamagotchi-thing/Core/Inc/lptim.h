/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    lptim.h
  * @brief   This file contains all the function prototypes for
  *          the lptim.c file
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
#ifndef __LPTIM_H__
#define __LPTIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "hal_types.h"
/* USER CODE END Includes */

extern LPTIM_HandleTypeDef hlptim1;



/* USER CODE BEGIN Private defines */
typedef uint32_t mcu_time_t;

#define US_TO_MCU_TIME(t)				((t * MCU_TIME_FREQ_NUM + MCU_TIME_FREQ_DEN - 1)/MCU_TIME_FREQ_DEN)
#define MS_TO_MCU_TIME(t)				(US_TO_MCU_TIME(t * 1000ULL))

#define MCU_TIME_FREQ_X1000 				((1000000000ULL/MCU_TIME_FREQ_DEN) * MCU_TIME_FREQ_NUM)


/* MCU time frequency is LSE/4 = 8,192 kHz = ((1000000/MCU_TIME_FREQ_DEN) * MCU_TIME_FREQ_NUM) */
#define MCU_TIME_FREQ_NUM					128ULL
#define MCU_TIME_FREQ_DEN					15625ULL
/* USER CODE END Private defines */

void MX_LPTIM1_Init(void);

/* USER CODE BEGIN Prototypes */
void time_init(void);
mcu_time_t time_get(void);
void time_wait_until(mcu_time_t time);
void time_delay(mcu_time_t time);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __LPTIM_H__ */

