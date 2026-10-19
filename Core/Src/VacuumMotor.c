#include "VacuumMotor.h"

VacuumMotorHandler vacuum_motor;


void vacuum_motor_init(){
	// Démarrage Timer pour le PWM
	HAL_TIM_PWM_Start(vacuum_motor.timer, vacuum_motor.channel);
}

void vacuum_motor_run(){
	// HAL_TIM_PWM_Start(vacuum_motor.timer, vacuum_motor.channel);
	// PWM on
	__HAL_TIM_SET_COMPARE(vacuum_motor.timer, vacuum_motor.channel, VACUUM_PWM);
}

void vacuum_motor_stop(){
	// PWM off
	__HAL_TIM_SET_COMPARE(vacuum_motor.timer, vacuum_motor.channel, 0);
	// HAL_TIM_PWM_Stop(vacuum_motor.timer, vacuum_motor.channel);
}