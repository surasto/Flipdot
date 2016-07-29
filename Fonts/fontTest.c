///////////////////////////////////////////////////
//  Test der Fontdaten
//  CC-BY SA 2016 c-hack.de
///////////////////////////////////////////////////

#include <stdio.h>

#include "8x8basic.h"

char c = '?';

void printChar(char c) 
{   unsigned char x,y,w;
	
	for (y=0; y<8; y++)
    {   w=font8x8_basic[c][y];
        for (x=0; x<8; x++)
        {   if (w&1)
                printf("#");
            else
                printf(" ");
            w=w>>1;
        } 
        printf("\n");  
    }
}

int main(int argc, char *argv[])
{   int i;
    	
	if (argc>1) 
	  do {
		 c=argv[1][i]; 
		 if (c!='\0') printChar(c);
		 i++;
	  } while ((c!='\0') && (i<30));	 
}
