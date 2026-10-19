#include "Scissors.h"

ScissorsHandler scissors;

void scissors_init(){
	// Démarrage Timer pour le PWM
	HAL_TIM_PWM_Start(scissors.timer, scissors.channel);
}

void scissors_retract(){
	// Définit le sens du moteur
	HAL_GPIO_WritePin(ENABLE2_SCISSORS_GPIO_Port, ENABLE2_SCISSORS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(ENABLE1_SCISSORS_GPIO_Port, ENABLE1_SCISSORS_Pin, GPIO_PIN_SET);

	// PWM on
	__HAL_TIM_SET_COMPARE(scissors.timer, scissors.channel, SCISSORS_PWM);
}

void scissors_extend(){
	// Définit le sens du moteur
	HAL_GPIO_WritePin(ENABLE1_SCISSORS_GPIO_Port, ENABLE1_SCISSORS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(ENABLE2_SCISSORS_GPIO_Port, ENABLE2_SCISSORS_Pin, GPIO_PIN_SET);

	// PWM on
	__HAL_TIM_SET_COMPARE(scissors.timer, scissors.channel, SCISSORS_PWM);
}

void scissors_stop(){
	// Bloque le moteur
	HAL_GPIO_WritePin(ENABLE2_SCISSORS_GPIO_Port, ENABLE2_SCISSORS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(ENABLE1_SCISSORS_GPIO_Port, ENABLE1_SCISSORS_Pin, GPIO_PIN_RESET);

	// PWM off
	__HAL_TIM_SET_COMPARE(scissors.timer, scissors.channel, 0);
}
