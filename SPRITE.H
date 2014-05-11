#ifndef INC_SPRITE_H
#define INC_SPRITE_H

#include "IMGUTIL.H"
#include "GRAPHICS.H"

typedef struct{
	signed int x, y;
	IMAGE *image;
	unsigned int numFrames, frameWidth;
}SPRITE;

extern int loadSprite(SPRITE **reference, IMAGE *image, int numFrames, unsigned int frameWidth);
extern void drawSprite(byte far *VGA, SPRITE *sprite, long delta);
#endif