| minibug on 68008

MONITR	=	0xFFFF8362

ACIACS	=	0xFFFFD800
ACIADA	=	0xFFFFD801

	.text
	.globl	putch
	.globl	_putchar
	.p2align 1
putch:
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

	.globl getch
	.globl _getchar
	.p2align 1
getch:
_getchar:
1:	MOVE.B  ACIACS,%d0
	AND.B   #1,%d0
	BEQ     1b
	MOVE.B  ACIADA,%d0
;	AND.B   #0x7F,%d0
;	CMP.B	#'\r',%d0
;	BNE	2f
;	MOVE.B	#'\n',%d0
2:	RTS

	.globl getche
	.p2align 1
getche:
	JSR	getch
	MOVE.L	%d0,-(%sp)
	JSR	putch
	MOVE.L	(%sp)+,%d0
	RTS

	.globl kbhit
	.globl _kbhit
	.p2align 1
kbhit:
_kbhit:
	MOVE.B  ACIACS,%d0
	AND.L	#1,%d0
	rts

	.globl _exit
	.p2align 1
_exit:
	JMP	MONITR

	.end
