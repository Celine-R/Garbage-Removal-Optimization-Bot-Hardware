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
#include "stm32f4xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
#define LBrush_PWM_Pin GPIO_PIN_4
#define LBrush_PWM_GPIO_Port GPIOB
#define RBrush_PWM_Pin GPIO_PIN_7
#define RBrush_PWM_GPIO_Port GPIOA
#define Flipper_PWM_Pin GPIO_PIN_10
#define Flipper_PWM_GPIO_Port GPIOB
#define Winch_FWD_PWM_Pin GPIO_PIN_6
#define Winch_FWD_PWM_GPIO_Port GPIOB
#define Winch_REV_PWM_Pin GPIO_PIN_7
#define Winch_REV_PWM_GPIO_Port GPIOB
#define Winch_FWD_EN_Pin GPIO_PIN_5
#define Winch_FWD_EN_GPIO_Port GPIOB
#define Winch_REV_EN_Pin GPIO_PIN_10
#define Winch_REV_EN_GPIO_Port GPIOA
#define Ultrasonic1_Trig_Pin GPIO_PIN_8
#define Ultrasonic1_Trig_GPIO_Port GPIOA
#define Ultrasonic1_Echo_Pin GPIO_PIN_1
#define Ultrasonic1_Echo_GPIO_Port GPIOC
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
