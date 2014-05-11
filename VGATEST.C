#include <conio.h>
#include <stdio.h>
#include <mem.h>
#include <dos.h>

#include "GRAPHICS.H"
#include "IMGUTIL.H"
#include "SPRITE.H"
#include "INPUT.H"
#include "TIMER.H"
#include "PCSPKR.H"
#include "SOUND.H"
#include "DMA.H"

#define LoByte(x) (short) (x & 0x00FF)
#define HiByte(x) (short) ((x&0xFF00)>>8)

int down = 0;

main(int argc, char *argv[])
{
	SPRITE *caco;
	IMAGE *image;
	int x,y,s;

	unsigned char * imf;
	unsigned int xm, ym, bm;
	unsigned int page, offset;
	unsigned char * dmatmp;

	WAV_File * wav;
	int size;

	loadWAV(&wav, ".\\snd.wav");

	size = wav->dataSize;

      //	dmatmp = (unsigned char *) malloc(size);

      //	memcpy(dmatmp, wav->data, size);

	getPageOffset(wav->data, &page, &offset);

	disableDMA(CHANNEL1, DMA_8BIT);
	clearFlipFlop(DMA_CLEARBYTE_8BIT_PORT);
	writeControlByte(DEMAND_MODE | ADDRESS_INCREMENT | SINGLE_CYCLE_MODE | READ_TRANSFER, DMA_8BIT);
	setPage(page, DMA_CHAN1_PAGE);
	setAddress(offset, DMA_CHAN1_ADDR);
	setDataLength(wav->dataSize+1, DMA_CHAN1_COUNT);
	enableDMA(CHANNEL1, DMA_8BIT);

       //	playSoundSingle(size);
      //	playSound(wav->data, wav->dataSize);

	printf("Num mouse buttons: %d\n", resetMouse());
	setMouseXBounds(0, 320);
	setMouseYBounds(0, 200);

	x = loadIMF(&imf, ".\\sob.imf");
	if (x == -1)
		return 0;
	setTimerISR();
	playIMF(imf, x,  700);

	if (openPCX(&image, 1, ".\\CACO_A.PCX") != 1)
	{
		printf("Cannot open file\n");
		return 0;
	}

	if (createBackBuffer() == 0)
		return 0;

	loadSprite(&caco, image, 4, 70);

	setVideoMode(VIDEOMODE_VGA);
	setPalette(image->palette);

	x = 176;
	y = 0;
	s = 0;

	//Done once to init vars
	getMouseState(&xm, &ym, &bm);

	while((getJoystickButtons() & JOYA_BUTTON1) != JOYA_BUTTON1 && bm != 1)
	{
		y++;

		if (s)
			x++;
		else
			x--;
		_fmemset(backBuffer, x, 64000L);
		caco->y--;
		drawSprite(backBuffer, caco, y);
		getMouseState(&xm, &ym, &bm);

		if (bm != 2)
			down = 0;

		if (!down && bm == 2)
		{
		  down = 1;
		//memcpy(dmatmp, wav->data, size);

       //	getPageOffset(dmatmp, &page, &offset);

	disableDMA(CHANNEL1, DMA_8BIT);
	clearFlipFlop(DMA_CLEARBYTE_8BIT_PORT);
	writeControlByte(DEMAND_MODE | ADDRESS_INCREMENT | SINGLE_CYCLE_MODE | READ_TRANSFER, DMA_8BIT);
	setPage(page, DMA_CHAN1_PAGE);
	setAddress(offset, DMA_CHAN1_ADDR);
	setDataLength(wav->dataSize+1, DMA_CHAN1_COUNT);
	enableDMA(CHANNEL1, DMA_8BIT);
			playSoundSingle(size);
		 }
		backBuffer[(ym * 320) + xm] = 3;

		if (y >= 4)
			y = 0;

		if (s)
		{
			if ( x>=191)
				s = !s;
		}
		else
		{
			if ( x <= 175)
				s = !s;
		}

		flipBuffers();
	}
	setVideoMode(VIDEOMODE_DOS);
	unsetTimerISR();
	free(imf);
	freeBackBuffer();
	free(image);
	free(caco);

	return 0;
}