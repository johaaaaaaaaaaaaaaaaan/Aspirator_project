#include "main.h"

#ifndef INC_MAINLOGIC_H_
#define INC_MAINLOGIC_H_

#include "Scissors.h"
#include "ServoMotor.h"
#include "Slide.h"
#include "LimitSwitch.h"

// Étapes de l'initialisation
typedef enum {
	INIT_1,
	INIT_2
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

void climb(float d);
/*
 * Exécute une étape de la montée de marche
 */

#endif /* INC_MAINLOGIC_H_ */
