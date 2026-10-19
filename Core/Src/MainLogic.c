#include "MainLogic.h"

RobotState State = { INIT_1, CLIMB };

void climb(float d)
{
    switch (State.climb)
    { 
        
    case CLIMB: // 0 Monter
        // Étend les ciseaux tant qu'on n'est pas en haut de la marche
        if (d <= 100)
        {
            scissors_extend();
        }
        else
        {
            HAL_Delay(3000); // Petit délai, le temps que les roues soient au-dessus de la marche
            scissors_stop();
            State.climb = SLIDE;
        }
        break;

    case SLIDE: // 1 Translater
        // Glissière au max
        if (is_limit_switch_active(LIMIT_SWITCH_SLIDE_OUT))
        {
            slide_stop();
            robot_stop();
            State.climb = CLIMB_B;
        }
        else
        {
            slide_extend();
            robot_forward();
        }
        break;

    case CLIMB_B: // 2 Ranger ciseaux
        // Rétraction ciseaux au max
        if (is_limit_switch_active(LIMIT_SWITCH_SCISSORS))
        {
            scissors_stop();
            State.climb = SLIDE_B;
        }
        else
        {
            scissors_retract();
        }
        break;

    case SLIDE_B: // 3 Ranger glissière
        // Rétraction glissière au max
        if (is_limit_switch_active(LIMIT_SWITCH_SLIDE_IN))
        {
            slide_extend();
            HAL_Delay(500); // petite sécu pour ne pas rester contre le capteur
            slide_stop();
            State.init = INIT_2;
        }
        else
        {
            slide_retract();
        }
        break;
    }
    // 4 Ne rien faire, robot sur la marche
    // Plus tard, on fera l'aspiration et le rebouclage à l'état 0
}