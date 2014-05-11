#ifndef INC_DMA_H
#define INC_DMA_H

//DMA PORTS

#define DMA_CHAN0_ADDR 0x00
#define DMA_CHAN1_ADDR 0x02
#define DMA_CHAN2_ADDR 0x04
#define DMA_CHAN3_ADDR 0x06
#define DMA_CHAN4_ADDR 0xC0
#define DMA_CHAN5_ADDR 0xC4
#define DMA_CHAN6_ADDR 0xC8
#define DMA_CHAN7_ADDR 0xCC

#define DMA_CHAN0_COUNT 0x01
#define DMA_CHAN1_COUNT 0x03
#define DMA_CHAN2_COUNT 0x05
#define DMA_CHAN3_COUNT 0x07
#define DMA_CHAN4_COUNT 0xC2
#define DMA_CHAN5_COUNT 0xC6
#define DMA_CHAN6_COUNT 0xCA
#define DMA_CHAN7_COUNT 0xCE

#define DMA_CHAN0_PAGE 0x87
#define DMA_CHAN1_PAGE 0x83
#define DMA_CHAN2_PAGE 0x81
#define DMA_CHAN3_PAGE 0x81
#define DMA_CHAN4_PAGE 0x8F
#define DMA_CHAN5_PAGE 0x8B
#define DMA_CHAN6_PAGE 0x89
#define DMA_CHAN7_PAGE 0x8A

#define DMA_MODE_8BIT_PORT 0x0B
#define DMA_MODE_16BIT_PORT 0xD6

#define DMA_MASK_8BIT_PORT 0x0A
#define DMA_MASK_16BIT_PORT 0xD4

#define DMA_CLEARBYTE_8BIT_PORT 0x0C
#define DMA_CLEARBYTE_16BIT_PORT 0xD8

//DMA Definitions

#define DMA_8BIT 0x00
#define DMA_16BIT 0x01

#define DEMAND_MODE 0x00
#define SINGLE_MODE 0x40
#define BLOCK_MODE 0x80
#define CASCADE_MODE 0xC0

#define ADDRESS_INCREMENT 0x00
#define ADDRESS_DECREMENT 0x20

#define SINGLE_CYCLE_MODE 0x00
#define AUTO_INIT_MODE 0x10

#define VERIFY_TRANSFER 0x00
#define WRITE_TRANSFER 0x04
#define READ_TRANSFER 0x08

#define CHANNEL0 0x0
#define CHANNEL1 0x1
#define CHANNEL2 0x2
#define CHANNEL3 0x3

#define CHANNEL4 0x0
#define CHANNEL5 0x1
#define CHANNEL6 0x2
#define CHANNEL7 0x3


#define CLEAR_MASK_BIT 0x00
#define SET_MASK_BIT 0x04

//Prototypes
extern void setDataLength(unsigned int, unsigned char);
extern void setAddress(unsigned int, unsigned char);
extern void setPage(short, unsigned char);
extern void clearFlipFlop(unsigned char);
extern int writeControlByte(unsigned int, unsigned char);
extern int enableDMA(unsigned char, unsigned int);
extern int disableDMA(unsigned char, unsigned char);

#endif