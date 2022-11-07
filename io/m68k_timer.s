| MSM6242B RTC

REGS	=	0xFFFFD000

CD	=	13		|; 30-sec adjust, IRQ, BUSY, HOLD
CE	=	14		|; t1, t0, ITRPT/STND, MASK
CF	=	15		|; TEST, 24/12, STOP, REST

	.section .data
	.p2align 2
callback:	DC.L	0

	.section .text
	.p2align 2
isr:	MOVEM.L	%d0-%d1/%a0-%a1,-(%sp)
	MOVE.L	#REGS,%a0
	BTST.B	#2,CD(%a0)
	BEQ	1f		| not for us
	MOVE.B	#0,CD(%a0)	| clear interrupt
	MOVE.L	callback,%a0
	JSR	(%a0)
1:	MOVEM.L	(%sp)+,%d0-%d1/%a0-%a1
	RTE

	.globl	_timer_on
	.p2align 2
_timer_on:
	OR.W	#0x0700,%sr	| mask processor interrupts
	MOVE.L	4(%sp),%a0
	MOVE.L	%a0,callback
	LEA	isr,%a0
	MOVE.L	%a0,26*4	| L2 ISR
	MOVE.L	#REGS,%a0
|	MOVE.B	#4,CF(%a0)	| TEST=0, 24HOUR=1, STOP=0, REST=0
|	MOVE.B	#6,CE(%a0)	| enable one-second clock interrupts
	MOVE.B	#2,CE(%a0)	| enable 1/64 clock interrupts
	MOVE.B	#0,CD(%a0)	| clear clock interrupt
	AND.W	#0xf8ff,%sr	| unmask processor interrupts
	RTS

	.globl	_timer_off
	.p2align 2
_timer_off:
	OR.W	#0x0700,%sr	| mask processor interrupts
	MOVE.L	#REGS,%a0
	MOVE.B	#1,CE(%a0)	| TIMER=1/64, WAVE OUTPUT, MASK=1
	AND.W	#0xf8ff,%sr	| unmask processor interrupts
	RTS

	.globl	_yield
	.p2align 2
_yield:
	STOP	#0
	RTS
