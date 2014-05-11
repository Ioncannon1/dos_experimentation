#include <stdlib.h>
#include <mem.h>
#include <alloc.h>

#include "GRAPHICS.H"

byte far * VGA = (byte far *) 0xA0000000L;
byte far * backBuffer;

void setVideoMode(unsigned char m)
{
	//TELL BIOS TO SET VGA MODE 0x13
	asm{
	mov ah, 0x00
	mov al, m
	int 0x10
	};
}

void waitVBlank()
{
	while((inp(VGA_STATUS_REGISTER) & 8));
	while(!(inp(VGA_STATUS_REGISTER) & 8));
}

int createBackBuffer()
{
	backBuffer = (byte far *) farmalloc(320L*200L);
	if (backBuffer == NULL)
	{
		printf("NO MEMORY\n");
		return 0;
	}
	return 1;
}

void freeBackBuffer()
{
	farfree(backBuffer);
}

void flipBuffers()
{
	waitVBlank();

	asm{
		push ds
		les di, VGA
		lds si, backBuffer
		mov cx,(320*200)/2
		rep movsw
		pop ds
	}
      //	_fmemcpy(VGA, backBuffer, 64000L);
}

void setPalette(unsigned char * newPalette)
{
	int x, y = 0;
	//SET PALETTE MEMORY
	for (x = 0; x <= 255; x++)
	{
		outp(PALETTE_MASK, 0xFF); //Can access whole palette
		outp(PALETTE_REGISTER_WR, x); //Set index
		outp(PALETTE_DATA,newPalette[y]>>2); //Write R value
		outp(PALETTE_DATA,newPalette[y+1]>>2); //Write G value
		outp(PALETTE_DATA,newPalette[y+2]>>2); //Write B value

		y += 3;
	}
}

void setPaletteIndex(unsigned char index, unsigned int r, unsigned int g, unsigned int b)
{
	outp(PALETTE_MASK, 0xFF); //Can access whole palette
	outp(PALETTE_REGISTER_WR, index); //Set index
	outp(PALETTE_DATA,r); //Write R value
	outp(PALETTE_DATA,g); //Write G value
	outp(PALETTE_DATA,b); //Write B value
}

void drawPalette(byte far *VGA, int x, int y)
{
	int c, x1, y1, offsetX = x;
	for (c = 0; c < 256; c++)
	{
		for (y1 = y; y1 < y+5; y1++)
		{
			for (x1 = x; x1 < x+5; x1++)
				VGA[(VGA_WIDTH * y1) + x1] = c;

		}

		x+=5;
		if ((x-offsetX) % (5 * 16) == 0)
		{
			x = offsetX;
			y+=5;
		}

	}
}