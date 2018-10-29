//************************************************************************
// Bitmap.C
//************************************************************************
#include <avr/pgmspace.h>
#include "Bitmap2.h"
#include "ks0108.h"
//##########################################################
void LoadBitmap2(unsigned char *bitmap2)
{
uint16_t i, j,by;
for(i=0; i<64; i+=8)

		for(j=0; j<128; j++)
		{
			by=pgm_read_byte(bitmap2++);
			ks0108GotoXY(j, i);
			ks0108WriteData(by);
		}

}
