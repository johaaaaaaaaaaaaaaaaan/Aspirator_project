#include "UltrasonicSensor.h"

UltrasonicSensorsHandler ultrasonic_sensors;

// indices des unltrasons
#define ULTRASONIC_INDEX_BACK 0
#define ULTRASONIC_INDEX_BOTTOM 1
#define ULTRASONIC_INDEX_LEFT 2
#define ULTRASONIC_INDEX_RIGHT 3
// Dernière messure effectué ou en cours
short current_mesure = ULTRASONIC_INDEX_RIGHT;

// Etat des messures possibles
#define ULTRASONIC_MESURE_WAITING 0
#define ULTRASONIC_MESURE_RECEIVING 1
#define ULTRASONIC_MESURE_ENDED 2
// Etat de la messure en cours
short mesure_step = ULTRASONIC_MESURE_ENDED;

void ultrasonic_sensor_init(){
	// __next_mesure();
}

void ultrasonic_sensor_mesure_all(){
	while (mesure_step != ULTRASONIC_MESURE_ENDED){
		// Attendre la fin des autres messures
	}
	current_mesure = ULTRASONIC_INDEX_RIGHT; // On met le compteur au max
	// On fait la mesure (donc pour le preier capteur car le compteur est au max)
	ultrasonic_sensor_next_mesure();

	// On attend d'avoir fait tout les capteurs
	while (current_mesure != ULTRASONIC_INDEX_RIGHT){
		ultrasonic_sensor_next_mesure();
	}
}


void ultrasonic_sensor_next_mesure(){

	// Fait rien si déja une messure en cours
	if (mesure_step != ULTRASONIC_MESURE_ENDED){
		return;
	}

	// On trouve le catpeur suivant pour lequel il
	// faut faire la mesure
	current_mesure = (current_mesure + 1) % 4;

	// Lancement de la mesure pour l'ultrason correspondant
	switch (current_mesure){
	case ULTRASONIC_INDEX_BACK:
		HAL_GPIO_WritePin(ultrasonic_sensors.port_trigger_back, ultrasonic_sensors.pin_trigger_back, GPIO_PIN_SET);
		mesure_step = ULTRASONIC_MESURE_WAITING;
		HAL_Delay(10);
		HAL_GPIO_WritePin(ultrasonic_sensors.port_trigger_back, ultrasonic_sensors.pin_trigger_back, GPIO_PIN_RESET);
		break;
	case ULTRASONIC_INDEX_BOTTOM:
		HAL_GPIO_WritePin(ultrasonic_sensors.port_trigger_bottom, ultrasonic_sensors.pin_trigger_bottom, GPIO_PIN_SET);
		mesure_step = ULTRASONIC_MESURE_WAITING;
		HAL_Delay(10);
		HAL_GPIO_WritePin(ultrasonic_sensors.port_trigger_bottom, ultrasonic_sensors.pin_trigger_bottom, GPIO_PIN_RESET);
		break;
	case ULTRASONIC_INDEX_LEFT:
		// TODO
			break;
	case ULTRASONIC_INDEX_RIGHT:
		// TODO
			break;
	default:
		break;
	}
}

// ========================== Interuptions ==========================


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// Interuption echo
	// On a reçus un retour, on en déduit la distance

	if(GPIO_Pin == ultrasonic_sensors.pin_echo_back && current_mesure == ULTRASONIC_INDEX_BACK) {
		// Front montant
		// On mesure le temps de la pulsation
		if (HAL_GPIO_ReadPin(ultrasonic_sensors.port_echo_back, ultrasonic_sensors.pin_echo_back) == GPIO_PIN_SET
				&& mesure_step == ULTRASONIC_MESURE_WAITING){
			__HAL_TIM_SET_COUNTER(ultrasonic_sensors.timer, 0);
			HAL_TIM_Base_Start_IT(ultrasonic_sensors.timer);
			mesure_step = ULTRASONIC_MESURE_RECEIVING;
		// Front dessandant
		// On déduit du temps de pulsation la distance
		}else if (HAL_GPIO_ReadPin(ultrasonic_sensors.port_echo_back, ultrasonic_sensors.pin_echo_back) == GPIO_PIN_RESET
				&& mesure_step == ULTRASONIC_MESURE_RECEIVING){
			//HAL_TIM_Base_Stop(ultrasonic_sensors.timer);
			ultrasonic_sensors.distance_back = __HAL_TIM_GET_COUNTER(ultrasonic_sensors.timer) * DISTANCE_COEFFICIENT;
			mesure_step = ULTRASONIC_MESURE_ENDED;
		}

	}else if(GPIO_Pin == ultrasonic_sensors.pin_echo_bottom && current_mesure == ULTRASONIC_INDEX_BOTTOM) {
		// Front montant
		if (HAL_GPIO_ReadPin(ultrasonic_sensors.port_echo_bottom, ultrasonic_sensors.pin_echo_bottom) == GPIO_PIN_SET
				&& mesure_step == ULTRASONIC_MESURE_WAITING){
			__HAL_TIM_SET_COUNTER(ultrasonic_sensors.timer, 0);
			HAL_TIM_Base_Start_IT(ultrasonic_sensors.timer);
			mesure_step = ULTRASONIC_MESURE_RECEIVING;
		// Front dessandant
		}else if (HAL_GPIO_ReadPin(ultrasonic_sensors.port_echo_bottom, ultrasonic_sensors.pin_echo_bottom) == GPIO_PIN_RESET
				&& mesure_step == ULTRASONIC_MESURE_RECEIVING){
			//HAL_TIM_Base_Stop(ultrasonic_sensors.timer);
			ultrasonic_sensors.distance_bottom = __HAL_TIM_GET_COUNTER(ultrasonic_sensors.timer) * DISTANCE_COEFFICIENT;
			mesure_step = ULTRASONIC_MESURE_ENDED;
		}

	}

	// TODO manque les deux untrasons gauche/droite
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	// Interuption Timer 4 overflow

	// On dépase la maveur max du compteur
	// -> Mesure de distance très éoigner
	// On annule la mesure pour pas bloquer les autres capteurs

	mesure_step = ULTRASONIC_MESURE_ENDED;
}
