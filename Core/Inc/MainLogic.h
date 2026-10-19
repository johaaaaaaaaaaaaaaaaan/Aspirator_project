#include "main.h"

#ifndef INC_MAINLOGIC_H_
#define INC_MAINLOGIC_H_

#include <stdbool.h>

// Étapes de l'initialisation
typedef enum {
	CRABBING,
	ALIGN,
} InitStep;

// Étapes de la montée de marche
typedef enum {
	CLIMB,
	SLIDE,
	CLIMB_B,
	SLIDE_B
} ClimbStep;

typedef struct {
	InitStep init;
	ClimbStep climb;
} RobotState;

// Contient l'état courant du robot
extern RobotState State;

bool climb(float d);
/*
 * Exécute une étape de la montée de marche
 * Renvoie true quand la marche est montée
 */

bool init(float d_left, float d_front);
/*
 * Exécute une étape de l'alignement avec le mur
 * Renvoie true quand le robot est arrivé devant la marche
 */

#endif /* INC_MAINLOGIC_H_ */
