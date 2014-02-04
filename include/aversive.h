/*  
 *  Copyright Droids Corporation, Microb Technology, Eirbot (2007)
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Revision : $Id: aversive.h,v 1.1.2.6 2009-05-18 12:19:51 zer0 Exp $
 *
 */

/**
 * here are some cute little macros, and other stuff, microcontroller
 * related ! 
 */


#ifndef _AVERSIVE_H_
#define _AVERSIVE_H_

#include <aversive/types.h>

#ifdef COMPILE_ON_ROBOT

#include "os_cpu.h"
#include "os_cfg.h"
#include "ucos_ii.h"
#include <system.h>
#include <io.h>
#include <sys/alt_irq.h>
#include <aversive/error.h>

#else /* Workaround to compile on X86. */

/** Reimplementation de IORD du NIOS2 pour compiler sur le PC */
#define IORD(adress, offset) (*((int32_t *)adress+offset))
/** Reimplementation de IOWR du NIOS2 pour compiler sur le PC */
#define IOWR(adress, offset, data) (*((int32_t *)adress+offset) = data)
#endif


/*
 *  a few "mathematical" macros : maximums and minimums
 */

/**
 *  signed maxmimum : both signs are tested
 */
#define S_MAX(to_saturate, value_max)    \
do {                                     \
   if (to_saturate > value_max)          \
     to_saturate = value_max;            \
   else if (to_saturate < -value_max)    \
     to_saturate = -value_max;           \
 } while(0)

/**
 *  unsigned maximum : result >0 is forced
 */
#define U_MAX(to_saturate, value_max)    \
do {                                     \
   if (to_saturate > value_max)          \
     to_saturate = value_max;            \
   else if (to_saturate < 0)             \
     to_saturate = 0;                    \
 } while(0)

/**
 *   simple maximum
 */
#define MAX(to_saturate, value_max)      \
do {                                     \
   if (to_saturate > value_max)          \
     to_saturate = value_max;            \
} while(0)

/**
 *  simple minimum
 */
#define MIN(to_saturate, value_min)      \
do {                                     \
   if (to_saturate < value_min)          \
     to_saturate = value_min;            \
} while(0)


/** @brief Computes the absolute value of a number 
 *
 *  While the abs() function in the libc works only with int type
 *  this macro works with every numerical type including floats
 *
 *  @note On float this is a bad idea, fabs() is faster. 
 */
#define ABS(val) ({					\
			__typeof(val) __val = (val);	\
			if (__val < 0)			\
				__val = - __val;	\
			__val;				\
		})

/* a few asm utilities */

#ifndef COMPILE_ON_ROBOT
/* On X86 */

#include <stdio.h>
#define reset() 

#define panic() do {printf("PANIC MOTHERFUCKER!!!\n"); }while(1)

#else
/* Si on est ici c'est qu'on compile pour le NIOS II. */
/** Resets the robot by jumping to the reset address.
 * @bug L'adresse de retour est hardcodee (0x04000000). pas bien...
 * @note Found on http://www.altera.com/support/kdb/solutions/rd05062005_584.html */
#define reset() do {                         \
    NIOS2_WRITE_STATUS(0);                   \
    NIOS2_WRITE_IENABLE(0);                  \
    ((void (*) (void)) 0x00000000) (); 		 \
    } while(0)

/** This define is called whenever the code hits a fatal crash. */
#define panic() do { \
    EMERG(0, "kernel panic"); \
} while(1)
   
#endif


/**
 *   little bit toggeling macro 
 *  
 *  change pin state
 *  usage :
 *  BIT_TOGGLE(PORTB,2) to make the pin 2 of PORTB toggle
 */
#define BIT_TOGGLE(port,bit) do {\
      if(bit_is_set(PIN(port),bit)) \
	cbi(port,bit); \
      else \
	sbi(port,bit); \
      } while(0)


/** booleans */
#define FALSE 0
#define TRUE 1
#define False FALSE
#define false FALSE
#define True TRUE
#define true TRUE

/** deprecated macros in libc, but they're almost used, so we implement them again ;) */
#ifndef cbi
#define cbi(sfr, bit) ( sfr &= ~ _BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) ( sfr |= _BV(bit))
#endif

#endif /* ifndef _AVERSIVE_H_ */

