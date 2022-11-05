#ifndef _STDINT_H
#define _STDINT_H

#include <stddef.h>

/* int8_t is always a char, on all ACK platforms. */

typedef signed char     int8_t;
typedef unsigned char   uint8_t;
#define INT8_MAX        127
#define INT8_MIN        (-128)
#define UINT8_MAX       255

/* int16_t is always a short, on all ACK platforms. */

typedef signed short    int16_t;
typedef unsigned short  uint16_t;
#define INT16_MAX       32767
#define INT16_MIN       (-32768)
#define UINT16_MAX      65535

/* int32_t is either a int or a long. */

typedef signed int      int32_t;
typedef unsigned int    uint32_t;
#define INT32_MAX       2147483647
#define INT32_MIN       (-2147483648)
#define UINT32_MAX      4294967295U

typedef signed long long    int64_t;
typedef unsigned long long  uint64_t;
#define INT64_MAX       9223372036854775807LL
#define INT64_MIN       (-9223372036854775808LL)
#define UINT64_MAX      18446744073709551615ULL

typedef int64_t         intmax_t;
typedef uint64_t        uintmax_t;

/* Pointers can be either 16 or 32 bits. */

typedef int32_t         intptr_t;
typedef uint32_t        uintptr_t;
#ifndef __ptrdiff_t_defined
typedef int32_t         ptrdiff_t;
#endif
#ifndef __size_t_defined
typedef uint32_t        size_t;
#endif
typedef int32_t         ssize_t;
#define INTPTR_MAX      2147483647
#define INTPTR_MIN      (-2147483647)
#define UINTPTR_MAX     4294967295

/* Now those have been defined, these are always the same. */

#define PTRDIFF_MAX     INTPTR_MAX
#define PTRDIFF_MIN     INTPTR_MIN
#define SIZE_MAX        UINTPTR_MAX

#endif
