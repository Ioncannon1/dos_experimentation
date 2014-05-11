#ifndef INC_IMGUTIL_H
#define INC_IMGUTIL_H
//PCX HEADER
typedef struct {
unsigned int manufbyte;
unsigned int pcxversion;
unsigned int rlebyte;
unsigned int bits_perpixel;
unsigned int xmin, ymin, xmax, ymax;

} PCX_Header;

typedef struct {
unsigned char * pixels;
unsigned char * palette;
unsigned int width, height;
}IMAGE;

extern int loadPCXImage(IMAGE **image, int loadPalette, char * path);
#endif INC_IMGUTIL_H