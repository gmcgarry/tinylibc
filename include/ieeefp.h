/*	$NetBSD: ieeefp.h,v 1.9 2011/03/27 05:13:15 mrg Exp $	*/

/* 
 * Written by J.T. Conklin, Apr 6, 1995
 * Public domain.
 */

#ifndef _IEEEFP_H
#define _IEEEFP_H

#include <sys/cdefs.h>
#include <machine/ieeefp.h>

typedef fp_rnd fp_rnd_t;
typedef fp_except fp_except_t;

fp_rnd_t	fpgetround(void);
fp_rnd_t	fpsetround(fp_rnd_t);
fp_except_t	fpgetmask(void);
fp_except_t	fpsetmask(fp_except_t);
fp_except_t	fpgetsticky(void);
fp_except_t	fpsetsticky(fp_except_t);
fp_except_t	fpresetsticky(fp_except_t);

#endif
