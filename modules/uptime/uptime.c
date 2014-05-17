#include <uptime.h>

#ifdef __unix__
static timestamp_t uptime_value = 0;

void uptime_set(timestamp_t time)
{
    uptime_value = time;
}

#endif

#ifdef COMPILE_ON_ROBOT
#include <system.h>
#include <io.h>
timestamp_t uptime_get(void) {
    return (IORD(TIMECOUNTER_BASE, 0));
}
#else
timestamp_t uptime_get(void) {
    return uptime_value;
}
#endif


