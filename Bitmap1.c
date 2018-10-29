//************************************************************************
// Bitmap.C
//************************************************************************
#include <avr/pgmspace.h>
#include "Bitmap1.h"
#include "ks0108.h"
//##########################################################
void LoadBitmap1(unsigned char *bitmap1)
{
uint16_t i, j,by;
for(i=0; i<64; i+=8)

		for(j=0; j<128; j++)
		{
			by=pgm_read_byte(bitmap1++);
			ks0108GotoXY(j, i);
			ks0108WriteData(by);
		}

}
