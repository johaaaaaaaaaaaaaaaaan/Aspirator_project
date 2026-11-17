#include "MainLogic.h"
#include "Scissors.h"
#include "ServoMotor.h"
#include "Slide.h"
#include "LimitSwitch.h"

RobotState State = {CRABBING, CLIMB};

// ========== Variables internes à l'alignement ==========

#define INIT_ROTATE_TIME_MIN 10 // Durée minimale d'une rotation de correction (ms)

// Durée d'une rotation de correction (ms), divisée par 2 à chaque changement de sens
static float init_rotate_time = 100;

// La correction de trajectoire n'est faite qu'un appel sur 6
static int align_counter = 0;

// Sens de la dernière rotation de correction
static enum
{
    ROTATION_RIGHT,
    ROTATION_LEFT
} last_rotation = ROTATION_RIGHT;

bool init(float d_left, float d_front)
{
    switch (State.init)
    {
    case CRABBING: // 0 Approche du mur par la gauche
        if (d_left < 80)
        {
            robot_stop();
            State.init = ALIGN;
        }
        else
        {
            robot_left();
        }
        break;

    case ALIGN: // 1 Avance le long du mur jusqu'à la marche
        if (d_front < 50)
        {
            // Arrivé devant la marche
            robot_stop();
            return true;
        }

        if (align_counter == 5)
        {
            if (d_left < 40)
            {
                // Trop près du mur, on tourne à droite
                robot_stop();
                HAL_Delay(100);
                robot_right(); // TODO pas la bonne fonction : il faut une rotation à droite, pas un déplacement
                HAL_Delay(init_rotate_time);
                if (last_rotation == ROTATION_LEFT && init_rotate_time > INIT_ROTATE_TIME_MIN)
                {
                    init_rotate_time = init_rotate_time / 2;
                }
                last_rotation = ROTATION_RIGHT;
            }
            else if (d_left > 60)
            {
                // Trop loin du mur, on tourne à gauche
                robot_stop();
                HAL_Delay(100);
                robot_left(); // TODO pas la bonne fonction : il faut une rotation à gauche, pas un déplacement
                HAL_Delay(init_rotate_time);
                if (last_rotation == ROTATION_RIGHT && init_rotate_time > INIT_ROTATE_TIME_MIN)
                {
                    init_rotate_time = init_rotate_time / 2;
                }
                last_rotation = ROTATION_LEFT;
            }
        }

        // On repart tout droit (aussi après une correction)
        robot_forward();
        align_counter = (align_counter + 1) % 6;
        break;
    }
    return false;
}

bool climb(float d)
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
            State.climb = CLIMB; // Prêt pour la marche suivante
            return true;
        }
        else
        {
            slide_retract();
        }
        break;
    }
    return false;
}
