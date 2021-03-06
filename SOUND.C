#include <stdio.h>
#include <mem.h>
#include <alloc.h>
#include <dos.h>
#include "SOUND.H"

#define LoByte(x) (short) (x & 0x00FF)
#define HiByte(x) (short) ((x&0xFF00)>>8)

void interrupt SB_ISR();
void interrupt (*oldSB_ISR)();

int loadWAV(WAV_File ** ref, char * path)
{
	FILE * input;
	unsigned char * buffer;
	unsigned int fileLen;
	WAV_File * wav = (WAV_File *) malloc(sizeof(WAV_File));
	unsigned int dataStart, i;

	//Load file into buffer
	if ((input = fopen(path, "rb")) == NULL)
	{
		free(wav);
		return 0;
	}

	fseek(input, 0, SEEK_END);
	fileLen = ftell(input);
	fseek(input, 0, SEEK_SET);

	buffer = (unsigned char *) malloc(fileLen+1);

	fread(buffer, fileLen, 1, input);

	fclose(input);

	//Setup struct

	//Check for RIFF
	if (buffer[0] != 'R' && buffer[1] != 'I' && buffer[2] != 'F' && buffer[3] != 'F')
	{
		free(buffer);
		free(wav);
		return 0;
	}

	wav->numChannels = buffer[22];
	wav->sampleRate = ((buffer[27] << 32) | (buffer[26] << 16) | (buffer[25] << 8) | buffer[24]);
	wav->byteRate = ((buffer[31] << 32) | (buffer[30] << 16) | (buffer[29] << 8) | buffer[28]);
	wav->blockAlign = ((buffer[33] << 8) | buffer[32]);
	wav->bitsPerSample = ((buffer[35] << 8) | buffer[34]);

	//Check if data is on byte 40 or 44 (newer version?)
	if (buffer[36] == 'D' && buffer[37] == 'a' && buffer[38] == 't' && buffer[39] == 'a')
		dataStart = 40;
	else
		dataStart = 44;

	//Copy over the data
	wav->data = (unsigned char *) malloc(fileLen - 40);
	for (i = dataStart; i < fileLen; i++)
		wav->data[i - dataStart] = buffer[i];
	wav->dataSize = fileLen - 40;
	//Done!
	free(buffer);
	*ref = wav;
	return 1;
}

void playSound(unsigned char * data, int size)
{
	int i;
	int x;
	outp(0x226, 0x01);
	outp(0x226, 0x00);
	outp(0x22C, 0x1D);
	for (i = 0; i < size; i++)
	{
		outp(0x22C, 0x10);
		outp(0x22C, data[i]);
		for (x=0; x<80;x++){};
	}
	outp(0x22C, 0x3D);
}

void playSoundSingle(unsigned int size)
{
	unsigned short rate = 65536 - (256000000/11025);

	oldSB_ISR = getvect(0xF);
	setvect(0xF, SB_ISR);

	outp(0x226, 0x01);
	outp(0x226, 0x00);
	outp(0x22C, 0x1D);

	outp(0x22C, 0x40);
	outp(0x22C, HiByte(rate));

      //	outp(0x22C, 0x41);
      //	outp(0x22C, LoByte(rate));
      //	outp(0x22C, HiByte(rate));

	outp(0x22C, 0xC0);
	outp(0x22C, 0x00);

	outp(0x22C, LoByte(size));
	outp(0x22C, HiByte(size));
}

void playSoundAutoInit()
{
}

void interrupt SB_ISR()
{
	printf("HI");
	inp(0x22E);
	outp(0x20,0x20);
	oldSB_ISR();
}