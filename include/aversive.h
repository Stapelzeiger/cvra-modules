/**
 * here are some cute little macros, and other stuff, microcontroller
 * related ! 
 */


#ifndef _AVERSIVE_H_
#define _AVERSIVE_H_

#include <stdint.h>
#include <inttypes.h>

 /** @brief Computes the absolute value of a number 
 *
 *  While the abs() function in the libc works only with int type
 *  this macro works with every numerical type including floats
 *
 *  @note On float this is a bad idea, fabs() is faster. 
 */
#define ABS(val) ({                 \
            __typeof(val) __val = (val);    \
            if (__val < 0)          \
                __val = - __val;    \
            __val;              \
        })


#endif /* ifndef _AVERSIVE_H_ */

