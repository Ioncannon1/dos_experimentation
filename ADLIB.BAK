#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <mem.h>
#include "TIMER.H"

unsigned int adlibSize = 0;
unsigned int adlibDelay = 0;
unsigned char * adlibData;
unsigned int currentIndex = 0;

void interrupt musicISR();
void interrupt (*oldTimerISR)();

extern void playIMF(unsigned char *, int, int);
extern void alOut(unsigned char, unsigned char);
extern int loadIMF(unsigned char**, char*);

int loadIMF(unsigned char** ref, char* path)
{
	FILE *input;
	unsigned char *buffer, *data;
	unsigned int fileLen;
	int x, i = 0;
	if ((input = fopen(path, "rb")) == NULL)
	{
		return 0;
	}

	fseek(input, 0, SEEK_END);
	fileLen = ftell(input);
	fseek(input, 0, SEEK_SET);

	buffer = (unsigned char *) malloc(fileLen+1);

	fread(buffer, fileLen, 1, input);

	fclose(input);

	//Check if TYPE-1 else TYPE 0
	if (buffer[0] != 0 && buffer[1] != 0)
	{
		fileLen = ((buffer[1] << 8) | buffer[0]);
		i = 2;
	}

	data = (unsigned char *) malloc(fileLen);

	for (x = 0; x < fileLen; x++)
		data[x] = buffer[x+i];

	*ref = data;

	return fileLen;
}

void playIMF(unsigned char* data, int size, int freq)
{
	currentIndex = 0;
	setTimerFreq(freq);
	adlibData = data;
	adlibSize = size;
}

void setTimerISR()
{
		oldTimerISR = getvect(ISR_TIMER);
		setvect(ISR_TIMER, musicISR);
}

void unsetTimerISR()
{
	setvect(ISR_TIMER, oldTimerISR);
}

void interrupt musicISR()
{
	if (adlibSize <= currentIndex)
		currentIndex = 0;
	if (adlibDelay > 0)
			adlibDelay--;
	else
	{
		unsigned int delay1;
		unsigned char freq;
		alOut(adlibData[currentIndex], adlibData[currentIndex+1]);
		adlibDelay = ((adlibData[currentIndex+3] << 8) | (adlibData[currentIndex+2]));
		currentIndex +=4;
	}
	oldTimerISR();
}

//Borrowed from John Carmack's Wolfenstein 3D code
//Simple write to the Adlib port but does all the write delay stuff because Adlib is weird
void alOut(unsigned char n, unsigned char b)
{
asm	pushf
asm	cli

asm	mov	dx,0x388
asm	mov	al,[n]
asm	out	dx,al
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	inc	dx
asm	mov	al,[b]
asm	out	dx,al

asm	popf

asm	dec	dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx

asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx

asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx

asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
asm	in	al,dx
}
