| minibug on 68008

MONITR	=	0xFFFF8362

ACIACS	=	0xFFFFD800
ACIADA	=	0xFFFFD801

	.globl	_putchar
	.p2align 1
_putchar:
	MOVE.L	4(%sp),%d0
	CMP.B	#'\n',%d0
	BNE	1f
	MOVE.B	#'\r',%d0
	MOVE.L	%d0,-(%sp)
	JSR	1f
	ADD.L	#4,%sp
1:      MOVE.B  ACIACS,%d0
	AND.B   #2,%d0
	BEQ     1b
	MOVE.L	4(%sp),%d0
	MOVE.B  %d0,ACIADA
	RTS

	.globl _getchar
	.p2align 1
_getchar:
1:	MOVE.B  ACIACS,%d0
	AND.B   #1,%d0
	BEQ     1b
	MOVE.B  ACIADA,%d0
	AND.B   #0x7F,%d0
	RTS

	.globl _kbhit
	.p2align 1
_kbhit:
	MOVE.B  ACIACS,%d0
	AND.L	#1,%d0
	rts

	.globl _exit
	.p2align 1
_exit:
	JMP	MONITR

	.end
