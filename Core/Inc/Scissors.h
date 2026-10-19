#include "main.h"

#ifndef INC_SCISSORS_H_
#define INC_SCISSORS_H_


// Compteur pour le PWM
#define SCISSORS_PWM 11293 // 60%


typedef struct {
	uint32_t channel;
	TIM_HandleTypeDef *timer;
} ScissorsHandler;

// Contient toutes les données des ciseaux
extern ScissorsHandler scissors;


void scissors_init();
/*
 * Initialisation des ciseaux
 */

void scissors_retract();
/*
 * Rentre les ciseaux (le moteur continue à tourner)
 */
void scissors_extend();
/*
 * Étend les ciseaux (le moteur continue à tourner)
 */
void scissors_stop();
/*
 * Stoppe les ciseaux (arrêt moteur)
 */

#endif /* INC_SCISSORS_H_ */
