#include "main.h"

#ifndef INC_VACUUMMOTOR_H_
#define INC_VACUUMMOTOR_H_

// EN TEST
// TODO trouver la bonne valeur de compteur pour le PWM de l'aspi

// #define VACUUM_PWM 565 // 600us
// 752
// #define VACUUM_PWM 900
#define VACUUM_PWM 750
// 50Hz 750 -> Mesuré à 805us

// Fonctione en vrai : 1kHz -> 200us

typedef struct {
	uint32_t channel;
	TIM_HandleTypeDef *timer;
} VacuumMotorHandler;

// Contient toutes les donnés du moteur d'aspi
extern VacuumMotorHandler vacuum_motor;


void vacuum_motor_init();
/*
 * Init le moteur d'aspi
 */

void vacuum_motor_run();
/*
 * Met en marche l'aspiration
 */
void vacuum_motor_stop();
/*
 * Stop l'aspiration
 */

#endif /* INC_VACUUMMOTOR_H_ */
