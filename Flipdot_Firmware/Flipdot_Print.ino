/////////////////////////////////////////////////////////////////
//  Testenvironment and base for displaying Fonts on the 
//  Flipdot display. Here the content of the display is printed
//  to stdout.
//  CC-BY SA NC 2016 c-hack.de    ralf@surasto.de
/////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "font6x8.h"
#include "font8x8.h"
#include "font8x12.h"

//================== Constants ===============================
#define X_SIZE 168    // 128 column
#define Y_SIZE 4      // 28 rows (represented by 4 bytes)
#define Y_PIXELS 28   // True Y-Size if the display
#define OFF 0
#define ON 1
#define SMALL 0
#define MEDIUM 1
#define LARGE 2

//================ global Variables ==========================
// frameBuffer stores the content of the Flipdotmatrix
// Each pixel is one bit (I.e only an eigth of storage is required 
unsigned char frameBuffer[X_SIZE][Y_SIZE];    

// bufferTouched records changes of the Framebuffer
// This way only changed pixels have to be physically flipped
unsigned char bufferTouched[X_SIZE][Y_SIZE];    
 

//===========================================
// clearFrameBuffer(int color)
// Sets all bits to 
//     Yellow if color = ON
//     Black if color  = OFF
//=========================================== 
void clearFrameBuffer(int color) {
	int x,y;
    for (x=0; x<X_SIZE; x++)
       for (y=0; y<Y_SIZE; y++) {
		   if (color == ON) frameBuffer[x][y]=0xFF; else frameBuffer[x][y]=0x00;
		   bufferTouched[x][y]=0xFF;    // All bits got touched
	   }
} 

//===========================================
// touchBuffer()
// Sets all bits to changed
//=========================================== 
void touchBuffer() {
	int x,y;
    for (x=0; x<X_SIZE; x++)
       for (y=0; y<Y_SIZE; y++) {
		   bufferTouched[x][y]=0xFF;    // All bits got touched
	   }
} 

//===========================================
// untouchBuffer()
// Sets all bits to changed
//=========================================== 
void untouchBuffer() {
	int x,y;
    for (x=0; x<X_SIZE; x++)
       for (y=0; y<Y_SIZE; y++) {
		   bufferTouched[x][y]=0x00;    // All bits are set to untouched
	   }
} 


//===========================================
// setFrameBuffer(int x, int y, int value)
// Set one Pixel at x,y-Position
// value can be ON or OFF
//=========================================== 
void setFrameBuffer(int x, int y, int value) {
    unsigned char w, wNot, oldByte;
    int yByteNo, yBitNo;
    
    w=1;
    if ((y < 8 * Y_SIZE)&&(x < X_SIZE)&&(x>=0)&&(y>=0)) {
		yByteNo = y/8;    // integer division to select the byte
		yBitNo = y%8;     // module division (residual) to select the bit in that byte
    	w = w<<yBitNo;
    	oldByte = frameBuffer[x][yByteNo];
    	if (value == ON) { 
	       frameBuffer[x][yByteNo] = frameBuffer[x][yByteNo]|w;  // Logical OR adds one bit to the existing byte
	    } else {
		   wNot = 0xFF - w;	
	       frameBuffer[x][yByteNo] = frameBuffer[x][yByteNo]&wNot;  // Logical AND set one bit to zero in the existing byte
	    }
	    if (frameBuffer[x][yByteNo] != oldByte) bufferTouched[x][yByteNo] = bufferTouched[x][yByteNo]|w;   // mark bit as changed 
	}
}


//============================================
// printChar8x8(int xOffs, int yOffs, char c) 
// xOffs = position of the left side of the character
// yOffs = position of the top of the character
// color = ON means yellow, OFF means black
// c = ASCII Character
// returns new x position
//============================================
int printChar6x8(int xOffs, int yOffs, int color, unsigned char c) {
	unsigned char x,y,w;
	
	for (y=0; y<8; y++) {   
		w=font6x8[c][y];
        for (x=0; x<8; x++) {   
			if (w&1) setFrameBuffer(x+xOffs,y+yOffs,color);
            w=w>>1;
        } 
    }
    return(xOffs+7);
}

int printChar8x8(int xOffs, int yOffs, int color, unsigned char c) {
	unsigned char x,y,w;
	
	for (y=0; y<8; y++) {   
		w=font8x8[c][y];
        for (x=0; x<8; x++) {   
			if (w&1) setFrameBuffer(x+xOffs,y+yOffs,color);
            w=w>>1;
        } 
    }
    return(xOffs+8);
}


int printChar8x12(int xOffs, int yOffs, int color, unsigned char c) {
	unsigned int x,y,w;
	
	for (y=0; y<12; y++) {   
		w=font8x12[c][y];
        for (x=0; x<12; x++) {   
			if (w&1) setFrameBuffer(x+xOffs,y+yOffs,color);
            w=w>>1;
        } 
    }
    return(xOffs+9);
}


//============================================
// printString(int xOffs, int yOffs, char s) 
// xOffs = position of the left side of the string
// yOffs = position of the top of the string
// color = ON means yellow, OFF means black
// s = string
//============================================
int printString(int xOffs, int yOffs, int color, int size, const char *s) {
	int i,x,y;
	
	i=0;
	x=xOffs;
	y=yOffs;
	while ((s[i] !='\0')&&(i<200)) {
		switch(size) {
		  case SMALL: x = printChar6x8(x, y, color, s[i]); break;
		  case MEDIUM: x = printChar8x8(x, y, color, s[i]); break;
		  case LARGE: x = printChar8x12(x, y, color, s[i]); break;
		  default: x = printChar6x8(x, y, color, s[i]);
	    }
		i++;
	}
	return(x);
}

//============================================
// DEBUG ONLY
// printFrameBuffer is only used to see the 
// content on the screen for debug
//============================================
void printFrameBuffer() {
	int x,y,bitNo,maxBits;
	unsigned char w;
	
	maxBits=8;
    for (y=0; y<Y_SIZE; y++) {
	   w = 1;   // most right bit set
	   if (y == Y_SIZE-1) {
		   maxBits = 8 - Y_SIZE*8 % Y_PIXELS;
	   } 
	   for (bitNo=0; bitNo<maxBits; bitNo++) {
		   for (x=0; x<X_SIZE; x++) {
			   if (frameBuffer[x][y] & w) printf("#"); else printf(".");
		   }  
		   w = w<<1; 
		   printf("\n");
	   }
    }
}

//============================================
// DEBUG ONLY
// printBufferTouched is only used to see the 
// content on the screen for debug
//============================================
void printBufferTouched() {
	int x,y,bitNo;
	unsigned char w;
	
    for (y=0; y<Y_SIZE; y++) {
	   w = 1;   // Highest bit set
	   for (bitNo=0; bitNo<8; bitNo++) {
		   for (x=0; x<X_SIZE; x++) {
			   if (bufferTouched[x][y] & w) printf("C"); else printf(".");
		   }  
		   w = w<<1; 
		   printf("\n");
	   }
    }
}		

	
//############################# Main ###############################	
int main(int argc, char *argv[]) {   
	int i,j;
    	
    clearFrameBuffer(OFF);
    untouchBuffer();
    i = printString(2,1,ON,SMALL,"Test mit Space ! & $");
    i = printString(2,15,ON,LARGE,"Noch ein Test \x81");
 //   i = printString(2,18,ON,"Passt das noch ?");
//    i=printChar(10,2,ON,'A');
    printFrameBuffer();
//    printBufferTouched();
	
}
