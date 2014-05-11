#include "PCSPKR.H"
#include "TIMER.H"

void startPcSpkr(unsigned int freq)
{
	unsigned int f = 1193180 / freq;
	asm {
		mov dx, [f]
		mov al, 0xB6
		out TIMER_CONTROL_PORT, al
		mov ax, dx
		out TIMER2_PORT, al
		xchg ah, al
		out TIMER2_PORT, al

		xor al, al
		in al, PCSPKR_PORT
		or al, 3
		out PCSPKR_PORT, al
	}
}

void changePcSpkrFreq(unsigned int freq)
{
}

void stopPcSpkr()
{
	asm{
	    xor al, al
	    in al, 0x61
	    and al, 0xFC
	    out 0x61, al
	}
}