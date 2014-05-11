#ifndef INC_SOUND_H
#define INC_SOUND_H

typedef struct{
	unsigned int numChannels;
	unsigned int sampleRate;
	unsigned int byteRate;
	unsigned int blockAlign;
	unsigned int bitsPerSample;
	unsigned char *data;
	int dataSize;
}WAV_File;

extern int loadWAV(WAV_File**, char*);
extern void playSound(unsigned char *, int);
extern void playSoundSingle(unsigned int size);
#endif