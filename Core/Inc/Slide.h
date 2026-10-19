#include "main.h"

#ifndef INC_SLIDE_H_
#define INC_SLIDE_H_

// Compteur pour les différentes valeurs de PWM

// #define SLIDE_PWM 3765 // 20%
// #define SLIDE_PWM 11293 // 60%
// #define SLIDE_PWM 15057 // 80%
#define SLIDE_PWM 18822 // 100%


typedef struct {
	uint32_t channel;
	TIM_HandleTypeDef *timer;
} SlideHandler;

// Contient toutes les données de la glissière
extern SlideHandler slide;


void slide_init();
/*
 * Initialise la glissière
 */

void slide_retract();
/*
 * Rentre la glissière (moteur reste en marche)
 */
void slide_extend();
/*
 * Étend la glissière (moteur reste en marche)
 */
void slide_stop();
/*
 * Stoppe la glissière (moteur éteint)
 */

#endif /* INC_SLIDE_H_ */
