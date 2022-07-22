/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Down_Pin GPIO_PIN_14
#define Down_GPIO_Port GPIOC
#define Up_Pin GPIO_PIN_15
#define Up_GPIO_Port GPIOC
#define Cancel_Pin GPIO_PIN_0
#define Cancel_GPIO_Port GPIOA
#define Next_Pin GPIO_PIN_1
#define Next_GPIO_Port GPIOA
#define OK_Pin GPIO_PIN_5
#define OK_GPIO_Port GPIOA
#define DB7_Pin GPIO_PIN_7
#define DB7_GPIO_Port GPIOA
#define DB6_Pin GPIO_PIN_0
#define DB6_GPIO_Port GPIOB
#define DB5_Pin GPIO_PIN_1
#define DB5_GPIO_Port GPIOB
#define DB4_Pin GPIO_PIN_12
#define DB4_GPIO_Port GPIOB
#define MODE_Pin GPIO_PIN_13
#define MODE_GPIO_Port GPIOB
#define Buzzer_Pin GPIO_PIN_8
#define Buzzer_GPIO_Port GPIOA
#define E_Pin GPIO_PIN_3
#define E_GPIO_Port GPIOB
#define RW_Pin GPIO_PIN_4
#define RW_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_5
#define RS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
