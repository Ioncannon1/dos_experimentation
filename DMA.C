#include <dos.h>

#include "DMA.H"

void getPageOffset(unsigned char * ptr, unsigned int * page, unsigned int * offset)
{
	unsigned int segment, off, tmp;
	long tmp2;

	segment = FP_SEG(ptr);
	off = FP_OFF(ptr);

	*page = (segment&0xF000) >> 12;
	tmp = (segment&0x0FFF) << 4;
	tmp2 = off + tmp;
	if (tmp2 > 0xFFFF)
		page++;
	*offset = (unsigned int) tmp2;
}

void setDataLength(unsigned int length, unsigned char channel)
{
	outp(channel, length & 0xFF);
	outp(channel, (length & 0xFF00) >> 8);
}

void setAddress(unsigned int address, unsigned char channel)
{
	outp(channel, address & 0xFF);
	outp(channel, (address & 0xFF00) >> 8);
}

void setPage(short page, unsigned char channel)
{
	outp(channel, page);
}

int writeControlByte(unsigned int mask, unsigned char bittype)
{
	if (bittype == DMA_8BIT)
		outp(DMA_MODE_8BIT_PORT, mask);
	else if (bittype == DMA_16BIT)
		outp(DMA_MODE_16BIT_PORT, mask);
	else
		return 0;
	return 1;
}

void clearFlipFlop(unsigned char bittype)
{
	if (bittype == DMA_CLEARBYTE_8BIT_PORT || bittype == DMA_CLEARBYTE_16BIT_PORT)
	outp(bittype, 0xFF);
}

int enableDMA(unsigned char channel, unsigned int bittype)
{
	unsigned int mask = 0;
	mask |= CLEAR_MASK_BIT | channel;

	if (bittype == DMA_8BIT)
		outp(DMA_MASK_8BIT_PORT, mask);
	else if (bittype == DMA_16BIT)
		outp(DMA_MASK_16BIT_PORT, mask);
	else
		return 0;

	return 1;
}

int disableDMA(unsigned char channel, unsigned char bittype)
{
	unsigned int mask = 0;
	mask |= SET_MASK_BIT | channel;

	if (bittype == DMA_8BIT)
		outp(DMA_MASK_8BIT_PORT, mask);
	else if (bittype == DMA_16BIT)
		outp(DMA_MASK_16BIT_PORT, mask);
	else
		return 0;

	return 1;
}