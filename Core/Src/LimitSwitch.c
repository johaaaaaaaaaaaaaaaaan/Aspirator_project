#include "LimitSwitch.h"
#include "main.h"

bool is_limit_switch_active(short index){

	// Mesure de l'état du capteur indiqué

	switch(index){
		case LIMIT_SWITCH_SCISSORS:
			return !HAL_GPIO_ReadPin(LIMIT_SW1_GPIO_Port, LIMIT_SW1_Pin);
		case LIMIT_SWITCH_SLIDE_IN:
			return !HAL_GPIO_ReadPin(LIMIT_SW2_GPIO_Port, LIMIT_SW2_Pin);
		case LIMIT_SWITCH_SLIDE_OUT:
			return !HAL_GPIO_ReadPin(LIMIT_SW3_GPIO_Port, LIMIT_SW3_Pin);
	}
	return false;
}
