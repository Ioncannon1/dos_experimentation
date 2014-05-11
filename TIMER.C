#include "TIMER.H"

void setTimerFreq(unsigned int freq)
{
	unsigned int f = 1193180 / freq;
	asm {
		mov dx, [f]
		mov al, 0xB6
		out TIMER_CONTROL_PORT, al
		mov ax, dx
		out TIMER0_PORT, al
		xchg ah, al
		out TIMER0_PORT, al
	}
}