#include "Slide.h"

SlideHandler slide;

void slide_init(){
	// Démarre le timer
	HAL_TIM_PWM_Start(slide.timer, slide.channel);
}

void slide_retract(){
	// Sens de rotation du moteur
	HAL_GPIO_WritePin(ENABLE2_SLIDE_GPIO_Port, ENABLE2_SLIDE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(ENABLE1_SLIDE_GPIO_Port, ENABLE1_SLIDE_Pin, GPIO_PIN_SET);

	// PWM on
	__HAL_TIM_SET_COMPARE(slide.timer, slide.channel, SLIDE_PWM);
}

void slide_extend(){
	// Sens de rotation du moteur
	HAL_GPIO_WritePin(ENABLE1_SLIDE_GPIO_Port, ENABLE1_SLIDE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(ENABLE2_SLIDE_GPIO_Port, ENABLE2_SLIDE_Pin, GPIO_PIN_SET);

	// PWM on
	__HAL_TIM_SET_COMPARE(slide.timer, slide.channel, SLIDE_PWM);
}

void slide_stop(){
	// Bloque le moteur
	HAL_GPIO_WritePin(ENABLE2_SLIDE_GPIO_Port, ENABLE2_SLIDE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(ENABLE1_SLIDE_GPIO_Port, ENABLE1_SLIDE_Pin, GPIO_PIN_RESET);

	// PWM off
	__HAL_TIM_SET_COMPARE(slide.timer, slide.channel, 0);
}
