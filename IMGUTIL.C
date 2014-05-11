#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

#include "IMGUTIL.H"
#include "GRAPHICS.H"

int openPCX(IMAGE **ref, int loadPalette, char * path)
{
	FILE *input;
	PCX_Header header;
	IMAGE *loadedImage = (IMAGE *) malloc(sizeof(IMAGE));
	unsigned char *buffer;
	unsigned long fileLen;

	//PCX BUFFERS
	unsigned int paletteLocation;

	//COUNTERS
	int x, y = 0;
	int writeDataPtr = 0;
	unsigned char repeatByte;

	if ((input = fopen(path, "rb")) == NULL)
	{
		free(loadedImage);
		return 0;
	}

	fseek(input, 0, SEEK_END);
	fileLen = ftell(input);
	fseek(input, 0, SEEK_SET);

	buffer = (unsigned char *) malloc(fileLen+1);
	if (buffer == NULL)
	{
		printf("Could not make buffer\n");
		fclose(input);
		return 0;
	}
	fread(buffer, fileLen, 1, input);
	fclose(input);

	header.manufbyte = buffer[0];
	header.pcxversion = buffer[1];
	header.rlebyte = buffer[2];
	if (header.manufbyte != 10 || header.rlebyte != 1)
	{
		free(loadedImage);
		return -1;
	}

	header.xmax = ((buffer[9] << 8) | buffer[8]) + 1;

	header.ymax = ((buffer[11] << 8) | buffer[10]) + 1;

	loadedImage->width = header.xmax;
	loadedImage->height = header.ymax;

	loadedImage->pixels = (unsigned char *) malloc(header.xmax*header.ymax);
	loadedImage->palette = (unsigned char *) malloc(768);

	if (loadedImage->pixels == NULL || loadedImage->palette == NULL)
	{
		printf("Error allocating buffer\n");
		free(loadedImage);
		return 0;
	}

	if (loadPalette == 1)
	{
		x = 0;
		//LOAD PALETTE
		for (paletteLocation = fileLen - 768; paletteLocation < fileLen; paletteLocation++)
		{
			loadedImage->palette[x] = buffer[paletteLocation];
			x++;
		}
	}

	//LOAD DATA
	x = 128; //Start of data
	while (writeDataPtr < header.xmax * header.ymax)
	{
		//Encoded, count byte read
		if (buffer[x] >= 192)
		{
			repeatByte = buffer[x] - 192;
			x++;
			for (y = 0; y<repeatByte; y++) //Repeat countbyte
			{
				loadedImage->pixels[writeDataPtr] = buffer[x];
				writeDataPtr++;
			}
		}
		else
		{
			loadedImage->pixels[writeDataPtr] = buffer[x];
			writeDataPtr++;
		}
		x++;
	}

	free(buffer);

	*ref = loadedImage;

	return 1;
}

int openPAL(unsigned char **arr, char * path)
{
	FILE *input;
	unsigned char *buffer;
	unsigned long fileLen;
	unsigned char r = 1,g = 1,b;
	int offset;
	unsigned char *dataPtr;

	if ((input = fopen(path, "rb")) == NULL)
		return 0;


	fseek(input, 0, SEEK_END);
	fileLen = ftell(input) - 21;
	fseek(input, 28, SEEK_SET);

	buffer = (unsigned char *) malloc(fileLen+1);
	fread(buffer, fileLen, 1, input);
	fclose(input);

	dataPtr = buffer;

	while (sscanf(dataPtr, "%d %d %d\n%n", &r, &g, &b, &offset) == 3)
	{
	dataPtr += offset;
	printf("%d %d %d\r\n", r, g, b);
	}

	*arr = buffer;

	return 1;
}
