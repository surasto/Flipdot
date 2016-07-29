#include "6x8_horizontal_LSB_1.h"

void writechar(unsigned char c)
{   unsigned char x,y,w;
    for (y=0; y<8; y++)
    {   w=font[c][y];
        for (x=0; x<6; x++)
        {   if (w&1)
                setpixel(x,y);
            else
                clrpixel(x,y);
            w=w>>1;
        }   
    }
}
