#include <platform.h>
#include <cvra_servo.h>

void cvra_servo_set(int channel, uint32_t value) {
    if(channel < 0 || channel >= 6)
        return;

    IOWR(SERVOS_BASE, channel, value);
}
