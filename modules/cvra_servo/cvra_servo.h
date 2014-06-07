#ifndef _CVRA_SERVO_H
#define _CVRA_SERVO_H

#include <aversive.h>

#define CVRA_SERVO_NB_CHANNELS      8

/** Sets the servo pulse width in steps of 100ns.
 * @todo Can we set pulse time > 20ms ? What happens then ? */
void cvra_servo_set(int channel, uint32_t value);
void cvra_servo_all_off(void);



#endif
