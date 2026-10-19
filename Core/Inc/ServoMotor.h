#include "main.h"

#ifndef INC_SERVOMOTOR_H_
#define INC_SERVOMOTOR_H_

/*
   * Clock à 48MHz
   * Prescaler Timer 50
   * Valeur max timer 18822
   *
   * ->
   * 1882 : 2000 us
   * 1412 : 1500 us
   * 941 : 1000 us
   *
   */

// Compteur en fonction des valeurs de PWM
#define SERVOMOTOR_PWM_CLOCKWISE 1882         // 2000 us
#define SERVOMOTOR_PWM_COUNTER_CLOCKWISE 941  // 1000 us
#define SERVOMOTOR_PWM_STOP 1412              // 1500 us


typedef struct {
	uint32_t channel_fl;
	uint32_t channel_fr;
	uint32_t channel_bl;
	uint32_t channel_br;
	TIM_HandleTypeDef *timer_fl;
	TIM_HandleTypeDef *timer_fr;
	TIM_HandleTypeDef *timer_bl;
	TIM_HandleTypeDef *timer_br;
} ServoMotorsHandler;

// Contient toutes les données des servos
extern ServoMotorsHandler servomotors;

void servomotor_init();
/*
 * Initialise les servos
 */

void robot_forward();
/*
 * Déplace le robot vers l'avant, vers la marche (moteurs restent actifs)
 */
void robot_backward();
/*
 * Déplace le robot vers l'arrière, s'éloigne de la marche (moteurs restent actifs)
 */
void robot_left();
/*
 * Déplace le robot vers la gauche (moteurs restent actifs)
 */
void robot_right();
/*
 * Déplace le robot vers la droite (moteurs restent actifs)
 */

void robot_stop();
/*
 * Arrête le mouvement du robot (moteurs éteints)
 */

#endif /* INC_SERVOMOTOR_H_ */
