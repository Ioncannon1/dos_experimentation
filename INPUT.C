#include "INPUT.H"

unsigned int getJoystickPosition(unsigned char mode)
{
	unsigned char m = mode;
	asm{
		pushf
		cli
		xor al, al
		xor cx, cx
		mov dx, JOYSTICK_PORT
		out dx , al
	}
	counter:
	asm{
		in al, dx;
		test al, [m]
		loopne counter
		sti
		xor ax, ax
		sub ax, cx
		popf
	}
}

unsigned char getJoystickButtons()
{
	asm{
		pushf
		mov dx, JOYSTICK_PORT
		out dx , al
		in al, dx;
		neg al
		popf
	}
}

unsigned char resetMouse()
{
	asm {
	mov ax, 0x00
	int 0x33
	cmp ax, 0xFFFF
	jne done
	mov al, bl
	}
	return;
	done:
	asm mov al, 0x00;
}

void setMouseXBounds(unsigned int x1, unsigned int x2)
{
	asm {
	mov ax, 0x7
	mov cx, [x1]
	mov dx, [x2]
	int 0x33
	}
}

void setMouseYBounds(unsigned int y1, unsigned int y2)
{
	asm {
	mov ax, 0x08
	mov cx, [y1]
	mov dx, [y2]
	int 0x33
	}
}

void getMouseState(unsigned int * x, unsigned int * y, unsigned char * b)
{
	int * a;
	asm{
	mov ax, 0x03
	int 0x33

	mov di, [bp+6]
	mov ax, [bp+8]
	mov es, ax
	mov es, ax
	mov es:[di], cx

	mov di, [bp+10]
	mov ax, [bp+12]
	mov es, ax
	mov es, ax
	mov es:[di], dx

	mov di, [bp+14]
	mov ax, [bp+16]
	mov es, ax
	mov es, ax
	mov es:[di], bx
	}
}

unsigned char getModKeys()
{
	asm{
	mov ah, 0x02
	int 0x16
	}
}

unsigned char getKeyCode()
{
	 asm{
		mov ah, 0x01
		int 0x16
		jz notrdy
		mov ah, 0x00
		int 0x16
		jmp done
	 }

	 notrdy:
	 asm xor ax, ax
	 done:
}