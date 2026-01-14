/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fdcan.h"
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_3_Pin GPIO_PIN_7
#define BUTTON_3_GPIO_Port GPIOB
#define BUTTON_3_EXTI_IRQn EXTI7_IRQn
#define LCD_DISP_RESET_Pin GPIO_PIN_7
#define LCD_DISP_RESET_GPIO_Port GPIOH
#define CTP_RST_Pin GPIO_PIN_3
#define CTP_RST_GPIO_Port GPIOE
#define BUTTON_1_Pin GPIO_PIN_5
#define BUTTON_1_GPIO_Port GPIOI
#define BUTTON_1_EXTI_IRQn EXTI5_IRQn
#define USR_BTN_1_Pin GPIO_PIN_3
#define USR_BTN_1_GPIO_Port GPIOJ
#define USR_LED_1_Pin GPIO_PIN_5
#define USR_LED_1_GPIO_Port GPIOE
#define TEST_3_Pin GPIO_PIN_10
#define TEST_3_GPIO_Port GPIOA
#define TEST_3_EXTI_IRQn EXTI10_IRQn
#define BUTTON_4_Pin GPIO_PIN_3
#define BUTTON_4_GPIO_Port GPIOG
#define BUTTON_4_EXTI_IRQn EXTI3_IRQn
#define CTP_INT_Pin GPIO_PIN_6
#define CTP_INT_GPIO_Port GPIOE
#define USB_PWR_EN_Pin GPIO_PIN_8
#define USB_PWR_EN_GPIO_Port GPIOG
#define USB_OVERCURRENT_Pin GPIO_PIN_0
#define USB_OVERCURRENT_GPIO_Port GPIOJ
#define R_RST_Pin GPIO_PIN_4
#define R_RST_GPIO_Port GPIOF
#define BUTTON_2_Pin GPIO_PIN_4
#define BUTTON_2_GPIO_Port GPIOA
#define BUTTON_2_EXTI_IRQn EXTI4_IRQn
#define R_CS_Pin GPIO_PIN_1
#define R_CS_GPIO_Port GPIOG
#define R_INT_Pin GPIO_PIN_4
#define R_INT_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
