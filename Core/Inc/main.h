/* USER CODE BEGIN Header */
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
#define ENABLE2_SCISSORS_Pin GPIO_PIN_14
#define ENABLE2_SCISSORS_GPIO_Port GPIOC
#define ENABLE1_SCISSORS_Pin GPIO_PIN_2
#define ENABLE1_SCISSORS_GPIO_Port GPIOA
#define OLD_ENA_Pin GPIO_PIN_3
#define OLD_ENA_GPIO_Port GPIOA
#define ENABLE2_SLIDE_Pin GPIO_PIN_4
#define ENABLE2_SLIDE_GPIO_Port GPIOA
#define ENABLE1_SLIDE_Pin GPIO_PIN_5
#define ENABLE1_SLIDE_GPIO_Port GPIOA
#define LIMIT_SW3_Pin GPIO_PIN_12
#define LIMIT_SW3_GPIO_Port GPIOB
#define LIMIT_SW2_Pin GPIO_PIN_13
#define LIMIT_SW2_GPIO_Port GPIOB
#define LIMIT_SW1_Pin GPIO_PIN_14
#define LIMIT_SW1_GPIO_Port GPIOB
#define ECHO_4_Pin GPIO_PIN_11
#define ECHO_4_GPIO_Port GPIOA
#define ECHO_4_EXTI_IRQn EXTI15_10_IRQn
#define TRIGGER_4_Pin GPIO_PIN_12
#define TRIGGER_4_GPIO_Port GPIOA
#define ECHO_3_Pin GPIO_PIN_15
#define ECHO_3_GPIO_Port GPIOA
#define ECHO_3_EXTI_IRQn EXTI15_10_IRQn
#define TRIGGER_3_Pin GPIO_PIN_3
#define TRIGGER_3_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_9
#define LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
