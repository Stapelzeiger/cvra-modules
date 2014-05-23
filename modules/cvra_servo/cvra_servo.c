#include <platform.h>
#include <cvra_servo.h>

void cvra_servo_set(int channel, uint32_t value) {
    if(channel < 0 || channel >= CVRA_SERVO_NB_CHANNELS)
        return;

    IOWR(SERVOS_BASE, channel, value);
}

void cvra_servo_all_off(void)
{
    int i;
    for (i = 0; i < CVRA_SERVO_NB_CHANNELS; i++) {
        cvra_servo_set(i, 0);
    }
}
