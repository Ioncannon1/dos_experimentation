#include <stdio.h>
#include <mem.h>

#include "IMGUTIL.H"
#include "SPRITE.H"
#include "GRAPHICS.H"

int loadSprite(SPRITE **reference, IMAGE *image, int numFrames, unsigned int frameWidth)
{
	SPRITE *sprite = (SPRITE*) malloc(sizeof(SPRITE));
	sprite->numFrames = numFrames;
	sprite->frameWidth = frameWidth;
	sprite->x = 0;
	sprite->y = 0;
	sprite->image = image;

	//Total frames size can't be > image size
	if (numFrames * frameWidth < image->width)
	{
		free(sprite);
			return 0;
	}

	*reference = sprite;
	return 1;
}

void drawSprite(byte far *buffer, SPRITE *sprite, long delta)
{
	unsigned int currentFrame = delta;
	unsigned int x, y;
	unsigned int sx, ex, sy, ey; //Screen coords
	unsigned int csx, cex, csy, cey; //Img clip coords

	printf("X:%d\n", sprite->x);

	//Check if totally clipped
	if (sprite->x + sprite->frameWidth < 0 || sprite->x > VGA_WIDTH ||
	sprite->y + sprite->image->height < 0 || sprite->y > VGA_HEIGHT)
		return;

	//CLIP LEFT
	if (sprite->x < 0)
	{
		sx = 0;
		csx = -sprite->x;
	}
	else
	{
		sx = sprite->x;
		csx = 0;
	}

	//CLIP RIGHT
	if (sprite->x + sprite->frameWidth > VGA_WIDTH)
	{
		ex = VGA_WIDTH;
		cex = VGA_WIDTH - sprite->x;
	}
	else
	{
		ex = sprite->x + sprite->frameWidth;
		cex = sprite->frameWidth;
	}

	//CLIP TOP
	if (sprite->y < 0)
	{
		sy = 0;
		csy = -sprite->y;
	}
	else
	{
		sy = sprite->y;
		csy = 0;
	}

	//CLIP BOTTOM
	if (sprite->y + sprite->image->height > VGA_HEIGHT)
	{
		ey = VGA_HEIGHT;
		cey = VGA_HEIGHT - sprite->y;
	}
	else
	{
		ey = sprite->y + sprite->image->height;
		cey = sprite->image->height;
	}

	//DRAW
	for (y = csy; y < cey; y++)
	{
		for (x = csx; x < cex; x++)
		{
			buffer[(VGA_WIDTH * (sy + y-csy)) + sx + x-csx] = sprite->image->pixels[sprite->image->width * y + x];
		}
	}
}