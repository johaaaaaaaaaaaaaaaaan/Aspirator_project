#include <stdbool.h>

#ifndef INC_LIMITSWITCH_H_
#define INC_LIMITSWITCH_H_

// Indices pour idnetifier les diférents capteur de fin de course
#define LIMIT_SWITCH_SCISSORS 1
#define LIMIT_SWITCH_SLIDE_IN 2
#define LIMIT_SWITCH_SLIDE_OUT 3

bool is_limit_switch_active(short index);
/*
 * Renvoi si le capteur indiqué est actif (true) ou non (false)
 */

#endif /* INC_LIMITSWITCH_H_ */
