| minibug on 68008

MONITR	=	0xFFFF8362

ACIACS	=	0xFFFFD800
ACIADA	=	0xFFFFD801

	.globl	_putchar
	.p2align 1
_putchar:
	MOVE.L	%d0,-(%sp)
	CMP.B	#'\n',%d0
	BNE	1f
	MOVE.B	#'\r',%d0
	JSR	_putchar
	MOVE.L	4(%sp),%d0
1:      MOVE.B  ACIACS,%d0
	AND.B   #2,%d0
	BEQ     1b
	MOVE.L	(%sp)+,%d0
	MOVE.B  %d0,ACIADA
	RTS

	.globl _getchar
	.p2align 1
_getchar:
	MOVE.B  ACIACS,%d0
	AND.B   #1,%d0
	BEQ     1b
	MOVE.B  ACIADA,%d0
	AND.B   #0x7F,%d0
	RTS

	.globl _kbhit
	.p2align 1
_kbhit:
	move.b  ACIACS,%d0
	and.l	#1,%d0
	rts

	.globl _exit
	.p2align 1
_exit:
	jmp	MONITR

	.end
