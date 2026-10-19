#include "UltrasonicSensor.h"

UltrasonicSensorsHandler ultrasonic_sensors;

// Indices des ultrasons
#define ULTRASONIC_INDEX_BACK 0
#define ULTRASONIC_INDEX_BOTTOM 1
#define ULTRASONIC_INDEX_LEFT 2
#define ULTRASONIC_INDEX_RIGHT 3
// Dernière mesure effectuée ou en cours
short current_mesure = ULTRASONIC_INDEX_RIGHT;

// États possibles des mesures
#define ULTRASONIC_MESURE_WAITING 0
#define ULTRASONIC_MESURE_RECEIVING 1
#define ULTRASONIC_MESURE_ENDED 2
// État de la mesure en cours
short mesure_step = ULTRASONIC_MESURE_ENDED;

void ultrasonic_sensor_init(){
	// __next_mesure();
}

void ultrasonic_sensor_mesure_all(){
	while (mesure_step != ULTRASONIC_MESURE_ENDED){
		// Attendre la fin des autres mesures
	}
	current_mesure = ULTRASONIC_INDEX_RIGHT; // On met le compteur au max
	// On fait la mesure (donc pour le premier capteur car le compteur est au max)
	ultrasonic_sensor_next_mesure();

	// On attend d'avoir fait tous les capteurs
	while (current_mesure != ULTRASONIC_INDEX_RIGHT){
		ultrasonic_sensor_next_mesure();
	}
}


void ultrasonic_sensor_next_mesure(){

	// Ne fait rien si une mesure est déjà en cours
	if (mesure_step != ULTRASONIC_MESURE_ENDED){
		return;
	}

	// On trouve le capteur suivant pour lequel il
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

// ========================== Interruptions ==========================


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// Interruption echo
	// On a reçu un retour, on en déduit la distance

	if(GPIO_Pin == ultrasonic_sensors.pin_echo_back && current_mesure == ULTRASONIC_INDEX_BACK) {
		// Front montant
		// On mesure le temps de la pulsation
		if (HAL_GPIO_ReadPin(ultrasonic_sensors.port_echo_back, ultrasonic_sensors.pin_echo_back) == GPIO_PIN_SET
				&& mesure_step == ULTRASONIC_MESURE_WAITING){
			__HAL_TIM_SET_COUNTER(ultrasonic_sensors.timer, 0);
			HAL_TIM_Base_Start_IT(ultrasonic_sensors.timer);
			mesure_step = ULTRASONIC_MESURE_RECEIVING;
		// Front descendant
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
		// Front descendant
		}else if (HAL_GPIO_ReadPin(ultrasonic_sensors.port_echo_bottom, ultrasonic_sensors.pin_echo_bottom) == GPIO_PIN_RESET
				&& mesure_step == ULTRASONIC_MESURE_RECEIVING){
			//HAL_TIM_Base_Stop(ultrasonic_sensors.timer);
			ultrasonic_sensors.distance_bottom = __HAL_TIM_GET_COUNTER(ultrasonic_sensors.timer) * DISTANCE_COEFFICIENT;
			mesure_step = ULTRASONIC_MESURE_ENDED;
		}

	}

	// TODO manquent les deux ultrasons gauche/droite
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	// Interruption Timer 4 overflow

	// On dépasse la valeur max du compteur
	// -> Mesure de distance très éloignée
	// On annule la mesure pour ne pas bloquer les autres capteurs

	mesure_step = ULTRASONIC_MESURE_ENDED;
}
