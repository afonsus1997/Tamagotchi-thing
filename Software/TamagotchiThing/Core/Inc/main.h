/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD2_A0_Pin GPIO_PIN_2
#define LCD2_A0_GPIO_Port GPIOC
#define LCD2_RES_Pin GPIO_PIN_3
#define LCD2_RES_GPIO_Port GPIOC
#define SW_LEFT_Pin GPIO_PIN_2
#define SW_LEFT_GPIO_Port GPIOA
#define SW_CENTER_Pin GPIO_PIN_3
#define SW_CENTER_GPIO_Port GPIOA
#define LCD2_CS_Pin GPIO_PIN_4
#define LCD2_CS_GPIO_Port GPIOC
#define OLED_RST_Pin GPIO_PIN_5
#define OLED_RST_GPIO_Port GPIOC
#define VBAT_SENSE_Pin GPIO_PIN_0
#define VBAT_SENSE_GPIO_Port GPIOB
#define LCD_BL_Pin GPIO_PIN_1
#define LCD_BL_GPIO_Port GPIOB
#define SW_RIGHT_Pin GPIO_PIN_2
#define SW_RIGHT_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_8
#define LCD_DC_GPIO_Port GPIOA
#define SPK_Pin GPIO_PIN_4
#define SPK_GPIO_Port GPIOB
#define LCD2_BL_Pin GPIO_PIN_5
#define LCD2_BL_GPIO_Port GPIOB
#define VBUS_SENSE_Pin GPIO_PIN_8
#define VBUS_SENSE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
