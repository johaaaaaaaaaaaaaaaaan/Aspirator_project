#include "main.h"

#ifndef INC_SCISSORS_H_
#define INC_SCISSORS_H_


// Compteur pour le PWM
#define SCISSORS_PWM 11293 // 60%


typedef struct {
	uint32_t channel;
	TIM_HandleTypeDef *timer;
} ScissorsHandler;

// Contient toutes les donénes du ciseau
extern ScissorsHandler scissors;


void scissors_init();
/*
 * Initialisation des ciseaux
 */

void scissors_retract();
/*
 * Rentre le ciseaux (moteur reste a tourner)
 */
void scissors_extend();
/*
 * Etend le ciseaux (moteur reste a tourner)
 */
void scissors_stop();
/*
 * Stop le ciseaux (Aret moteur)
 */

#endif /* INC_SCISSORS_H_ */
