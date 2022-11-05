#ifndef _MACHINE_ENDIAN_H
#define _MACHINE_ENDIAN_H

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN    4321
#define __PDP_ENDIAN    3412

#ifndef __FLOAT_WORD_ORDER
# define __FLOAT_WORD_ORDER __BYTE_ORDER
#endif

#if defined(__m68k__)
#define _BYTE_ORDER _BIG_ENDIAN
#elif defined(__x86_64__)
#define __BYTE_ORDER __LITTLE_ENDIAN
#else
#error "_BYTE_ORDER not defined in <endian.h>."
#endif

#endif
