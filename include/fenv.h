#ifndef _FENV_H
#define _FENV_H

enum
  {
    FE_INVALID =
#define FE_INVALID	0x01
      FE_INVALID,
    __FE_DENORM = 0x02,
    FE_DIVBYZERO =
#define FE_DIVBYZERO	0x04
      FE_DIVBYZERO,
    FE_OVERFLOW =
#define FE_OVERFLOW	0x08
      FE_OVERFLOW,
    FE_UNDERFLOW =
#define FE_UNDERFLOW	0x10
      FE_UNDERFLOW,
    FE_INEXACT =
#define FE_INEXACT	0x20
      FE_INEXACT
  };

#define FE_ALL_EXCEPT \
	(FE_INEXACT | FE_DIVBYZERO | FE_UNDERFLOW | FE_OVERFLOW | FE_INVALID)

enum
  {
    FE_TONEAREST =
#define FE_TONEAREST	0
      FE_TONEAREST,
    FE_DOWNWARD =
#define FE_DOWNWARD	0x400
      FE_DOWNWARD,
    FE_UPWARD =
#define FE_UPWARD	0x800
      FE_UPWARD,
    FE_TOWARDZERO =
#define FE_TOWARDZERO	0xc00
      FE_TOWARDZERO
  };

typedef unsigned short int fexcept_t;

typedef struct
  {
    unsigned short int __control_word;
    unsigned short int __glibc_reserved1;
    unsigned short int __status_word;
    unsigned short int __reserved2;
    unsigned short int __tags;
    unsigned short int __reserved3;
    unsigned int __eip;
    unsigned short int __cs_selector;
    unsigned int __opcode:11;
    unsigned int __reserved4:5;
    unsigned int __data_offset;
    unsigned short int __data_selector;
    unsigned short int __reserved5;
  }
fenv_t;

#define FE_DFL_ENV	((const fenv_t *) -1)

typedef struct
  {
    unsigned short int __control_word;
    unsigned short int __reserved;
    unsigned int __mxcsr;
  }
femode_t;

#define FE_DFL_MODE	((const femode_t *) -1L)

extern int feclearexcept (int __excepts);
extern int fegetexceptflag (fexcept_t *__flagp, int __excepts);
extern int feraiseexcept (int __excepts);
extern int fesetexcept (int __excepts);
extern int fesetexceptflag (const fexcept_t *__flagp, int __excepts);
extern int fetestexcept (int __excepts);
extern int fetestexceptflag (const fexcept_t *__flagp, int __excepts);
extern int fegetround (void);
extern int fesetround (int __rounding_direction);
extern int fegetenv (fenv_t *__envp);
extern int feholdexcept (fenv_t *__envp);
extern int fesetenv (const fenv_t *__envp);
extern int feupdateenv (const fenv_t *__envp);
extern int fegetmode (femode_t *__modep);
extern int fesetmode (const femode_t *__modep);

#endif
