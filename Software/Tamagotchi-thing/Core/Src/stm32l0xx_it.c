/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usb_user.h"
#include "tim.h"
#include "lptim.h"

volatile uint32_t ticks_h = 0;

/* USER CODE END Includes */


/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern LPTIM_HandleTypeDef hlptim1;
extern TIM_HandleTypeDef htim7;
extern PCD_HandleTypeDef hpcd_USB_FS;
extern TIM_HandleTypeDef htim2;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable Interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles LPTIM1 global interrupt / LPTIM1 wake-up interrupt through EXTI line 29.
  */
void LPTIM1_IRQHandler(void)
{
  /* USER CODE BEGIN LPTIM1_IRQn 0 */
  /* Counter direction change up event */
	if (__HAL_LPTIM_GET_FLAG(&hlptim1, LPTIM_FLAG_DOWN) != RESET) {
		if (__HAL_LPTIM_GET_IT_SOURCE(&hlptim1, LPTIM_IT_DOWN) != RESET) {
			__HAL_LPTIM_CLEAR_FLAG(&hlptim1, LPTIM_FLAG_DOWN);
		}
	}

	/* Counter direction change down to up event */
	if (__HAL_LPTIM_GET_FLAG(&hlptim1, LPTIM_FLAG_UP) != RESET) {
		if (__HAL_LPTIM_GET_IT_SOURCE(&hlptim1, LPTIM_IT_UP) != RESET) {
			__HAL_LPTIM_CLEAR_FLAG(&hlptim1, LPTIM_FLAG_UP);
		}
	}

	/* Autoreload register update OK event */
	if (__HAL_LPTIM_GET_FLAG(&hlptim1, LPTIM_FLAG_ARROK) != RESET) {
		if (__HAL_LPTIM_GET_IT_SOURCE(&hlptim1, LPTIM_IT_ARROK) != RESET) {
			__HAL_LPTIM_CLEAR_FLAG(&hlptim1, LPTIM_FLAG_ARROK);
		}
	}

	/* Compare register update OK event */
	if (__HAL_LPTIM_GET_FLAG(&hlptim1, LPTIM_FLAG_CMPOK) != RESET) {
		if (__HAL_LPTIM_GET_IT_SOURCE(&hlptim1, LPTIM_IT_CMPOK) != RESET) {
			__HAL_LPTIM_CLEAR_FLAG(&hlptim1, LPTIM_FLAG_CMPOK);
		}
	}

	/* External trigger edge event */
	if (__HAL_LPTIM_GET_FLAG(&hlptim1, LPTIM_FLAG_EXTTRIG) != RESET) {
		if (__HAL_LPTIM_GET_IT_SOURCE(&hlptim1, LPTIM_IT_EXTTRIG) != RESET) {
			__HAL_LPTIM_CLEAR_FLAG(&hlptim1, LPTIM_FLAG_EXTTRIG);
		}
	}

	/* Compare match event */
	if (__HAL_LPTIM_GET_FLAG(&hlptim1, LPTIM_FLAG_CMPM) != RESET) {
		if (__HAL_LPTIM_GET_IT_SOURCE(&hlptim1, LPTIM_IT_CMPM) != RESET) {
			__HAL_LPTIM_CLEAR_FLAG(&hlptim1, LPTIM_FLAG_CMPM);
			/* Just wake the CPU */
		}
	}

	/* Autoreload match event */
	if (__HAL_LPTIM_GET_FLAG(&hlptim1, LPTIM_FLAG_ARRM) != RESET) {
		if (__HAL_LPTIM_GET_IT_SOURCE(&hlptim1, LPTIM_IT_ARRM) != RESET) {
			__HAL_LPTIM_CLEAR_FLAG(&hlptim1, LPTIM_FLAG_ARRM);
			ticks_h++;
		}
	}
  return;
  /* USER CODE END LPTIM1_IRQn 0 */
  HAL_LPTIM_IRQHandler(&hlptim1);
  /* USER CODE BEGIN LPTIM1_IRQn 1 */

  /* USER CODE END LPTIM1_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */

  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/**
  * @brief This function handles USB event interrupt / USB wake-up interrupt through EXTI line 18.
  */
void USB_IRQHandler(void)
{
  /* USER CODE BEGIN USB_IRQn 0 */
  tud_int_handler(0);
  return;
  /* USER CODE END USB_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
  /* USER CODE BEGIN USB_IRQn 1 */

  /* USER CODE END USB_IRQn 1 */
}

/* USER CODE BEGIN 1 */

extern RTC_HandleTypeDef hrtc;

void RTC_WKUP_IRQHandler(void)
{
    HAL_RTCEx_WakeUpTimerIRQHandler(&hrtc);
}

/* USER CODE END 1 */
