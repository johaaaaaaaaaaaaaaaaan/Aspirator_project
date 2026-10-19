
#include "ServoMotor.h"

ServoMotorsHandler servomotors;

void servomotor_init(){
	// On démarre tous les channels des timers des servos
	HAL_TIM_PWM_Start(servomotors.timer_bl, servomotors.channel_bl);
	HAL_TIM_PWM_Start(servomotors.timer_br, servomotors.channel_br);
	HAL_TIM_PWM_Start(servomotors.timer_fr, servomotors.channel_fr);
	// HAL_TIMEx_PWMN_Start(servomotors.timer_fl, servomotors.channel_fl); // TODO
}

void robot_forward(){
	__HAL_TIM_SET_COMPARE(servomotors.timer_bl, servomotors.channel_bl, SERVOMOTOR_PWM_COUNTER_CLOCKWISE);
	__HAL_TIM_SET_COMPARE(servomotors.timer_br, servomotors.channel_br, SERVOMOTOR_PWM_CLOCKWISE);
	__HAL_TIM_SET_COMPARE(servomotors.timer_fr, servomotors.channel_fr, SERVOMOTOR_PWM_COUNTER_CLOCKWISE);
	// TODO manque 1 moteur
}

void robot_backward(){
	__HAL_TIM_SET_COMPARE(servomotors.timer_bl, servomotors.channel_bl, SERVOMOTOR_PWM_CLOCKWISE);
	__HAL_TIM_SET_COMPARE(servomotors.timer_br, servomotors.channel_br, SERVOMOTOR_PWM_COUNTER_CLOCKWISE);
	__HAL_TIM_SET_COMPARE(servomotors.timer_fr, servomotors.channel_fr, SERVOMOTOR_PWM_CLOCKWISE);
	// TODO manque 1 moteur
}

void robot_left(){
	// TODO
}

void robot_right(){
	// TODO
}

void robot_stop(){
	__HAL_TIM_SET_COMPARE(servomotors.timer_bl, servomotors.channel_bl, SERVOMOTOR_PWM_STOP);
	__HAL_TIM_SET_COMPARE(servomotors.timer_br, servomotors.channel_br, SERVOMOTOR_PWM_STOP);
	__HAL_TIM_SET_COMPARE(servomotors.timer_fr, servomotors.channel_fr, SERVOMOTOR_PWM_STOP);
	// TODO manque 1 moteur
}




