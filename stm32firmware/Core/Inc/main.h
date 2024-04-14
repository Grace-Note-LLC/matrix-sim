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
#include "stm32f1xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CORNER_LED_0_Pin GPIO_PIN_0
#define CORNER_LED_0_GPIO_Port GPIOA
#define CORNER_LED_1_Pin GPIO_PIN_1
#define CORNER_LED_1_GPIO_Port GPIOA
#define CORNER_LED_2_Pin GPIO_PIN_2
#define CORNER_LED_2_GPIO_Port GPIOA
#define CORNER_LED_3_Pin GPIO_PIN_3
#define CORNER_LED_3_GPIO_Port GPIOA
#define CORNER_LED_4_Pin GPIO_PIN_4
#define CORNER_LED_4_GPIO_Port GPIOA
#define CORNER_LED_5_Pin GPIO_PIN_5
#define CORNER_LED_5_GPIO_Port GPIOA
#define CORNER_LED_6_Pin GPIO_PIN_6
#define CORNER_LED_6_GPIO_Port GPIOA
#define CORNER_LED_7_Pin GPIO_PIN_7
#define CORNER_LED_7_GPIO_Port GPIOA
#define TRANSISTOR_0_Pin GPIO_PIN_4
#define TRANSISTOR_0_GPIO_Port GPIOB
#define TRANSISTOR_1_Pin GPIO_PIN_5
#define TRANSISTOR_1_GPIO_Port GPIOB
#define TRANSISTOR_2_Pin GPIO_PIN_6
#define TRANSISTOR_2_GPIO_Port GPIOB
#define TRANSISTOR_3_Pin GPIO_PIN_7
#define TRANSISTOR_3_GPIO_Port GPIOB
#define TRANSISTOR_4_Pin GPIO_PIN_8
#define TRANSISTOR_4_GPIO_Port GPIOB
#define TRANSISTOR_5_Pin GPIO_PIN_9
#define TRANSISTOR_5_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
