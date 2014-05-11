#ifndef INC_GRAPHICS_H
#define INC_GRAPHICS_H

//////////
//VGA DEFS
//////////
#define VGA_WIDTH 320
#define VGA_HEIGHT 200
#define PALETTE_MASK 0x3C6
#define PALETTE_REGISTER_RD 0x3C7
#define PALETTE_REGISTER_WR 0x3C8
#define PALETTE_DATA 0x3C9
#define VGA_STATUS_REGISTER 0X3DA


#define VIDEOMODE_DOS 0x03
#define VIDEOMODE_VGA 0x13

//////////////////
//VGA DECLARATIONS
//////////////////

typedef unsigned char byte;


////////////
//PROTOTYPES
////////////
extern void setVideoMode(unsigned char mode);
extern void waitVBlank(void);
extern int createBackBuffer();
extern void freeBackBuffer();
extern void flipBuffers();
extern void setPalette(unsigned char * newPalette);
extern void setPaletteIndex(unsigned char index, unsigned int r, unsigned int g, unsigned int b);

extern byte far * VGA;
extern byte far * backBuffer;
#endif