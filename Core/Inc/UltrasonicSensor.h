#include "main.h"

#ifndef INC_ULTRASONICSENSOR_H_
#define INC_ULTRASONICSENSOR_H_

#define DISTANCE_COEFFICIENT 0.17f // coef qui convertit les ticks du timer en mm

typedef struct {
	TIM_HandleTypeDef *timer;

	GPIO_TypeDef *port_trigger_back;
	uint16_t pin_trigger_back;
	GPIO_TypeDef *port_echo_back;
	uint16_t pin_echo_back;
	uint32_t distance_back;

	GPIO_TypeDef *port_trigger_bottom;
	uint16_t pin_trigger_bottom;
	GPIO_TypeDef *port_echo_bottom;
	uint16_t pin_echo_bottom;
	uint32_t distance_bottom;


	uint32_t distance_left;
	uint32_t distance_right;
} UltrasonicSensorsHandler;

// Contient toutes les données des capteurs ultrasons
extern UltrasonicSensorsHandler ultrasonic_sensors;


void ultrasonic_sensor_init();
/*
 * Initialise les ultrasons
 */

void ultrasonic_sensor_mesure_all();
/*
 * Effectue toutes les mesures des 4 capteurs
 */

void ultrasonic_sensor_next_mesure();
/*
 * Effectue à chaque exécution la mesure du capteur suivant
 */

#endif /* INC_ULTRASONICSENSOR_H_ */
