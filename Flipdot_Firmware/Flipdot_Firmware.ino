////////////////////////////////////////////////////////////////////////////
// Flipdot_Firmware
// CC-BY-SA-NC    8/2016 C-Hack (Ralf@Surasto.de)
//
// This main program runs on the Arduino and waits for commands via the RS232 
// For simplicity the commands are handed over as an ascii string so that
// they can be easily created by scripts
//
// Command format
//   <Command>,<Color>,<x>,<y>,<....string....>\
//
//   Commands:
//     C  Clear Screen
//     Q  Quick Clear (changes only those pixels which have to be flipped)
//     S  Print in small font
//     M  Print in medium Font
//     L  Print in large Font
//     H  Draw a horizontal line
//     P  Set a pixel
//   Color:
//     B  Black
//     Y  Yellow
//   X,Y:
//     Required for all Print commands
//     Only Y is required for the horizontal line command "H"
//   String:
//     Contains the characters to be printed 
//   "\": 
//     The command lines is terminated by the "\" character
//     It gets evaluated after reception of that character
//             
////////////////////////////////////////////////////////////////////////////

#include "Flipdot.h"

int i,j;
int inByte;
int commandLine[100];
int commandLength=0;

void setup() {
  
  Serial.begin(9600);
  flipdotSetup();

}

void loop() {
  int c, color;
  int cmd, cmdPtr;
  int xVal, yVal;
  String xStr,yStr;
  String outputString;
  
  if (Serial.available() > 0) {
    c = Serial.read();
    if (commandLength<100) commandLine[commandLength++] = c;
    else {
      commandLength = 0;
      Serial.print("?");
    }
    
    // ==== If command string is complete... =======
    if (c=='\\') {
      cmd = commandLine[0];
      if (commandLine[2] == 'B') color = 0; else color = 1;
      cmdPtr=4;
      xStr = ""; yStr = "";
      while ((cmdPtr<=commandLength) && (commandLine[cmdPtr]!=',')) {
        xStr +=  (char)commandLine[cmdPtr];
        cmdPtr++;
        xVal = xStr.toInt();
      }
      cmdPtr++;
      while ((cmdPtr<=commandLength) && (commandLine[cmdPtr]!=',')) {
        yStr += (char)commandLine[cmdPtr];
        cmdPtr++;
        yVal = yStr.toInt();
      }
      cmdPtr++;
      while (cmdPtr<=commandLength) {
        outputString += (char)commandLine[cmdPtr];
        cmdPtr++;
      }
    }
    commandLength = 0;    // Reset command mode

    // ======= Debug only ===========
    Serial.println(cmd);
    Serial.println(color);
    Serial.println(xVal);
    Serial.println(yVal);
    Serial.println(outputString);
    
    // ======= Execute the respective command ========
    switch (cmd) {
      case 'C':  clearAll(color); break;
      case 'Q':  quickClear(color); break;
    }
  }
}


//===========================
// For debugging only
//===========================
void panelTest() {
  
   writePanel(-1);
   //delay(500);

// ============== Alles Schwarz ============
/*   colSelect(i,SET);
   rowSelect(j,SET);
   writePanel(0);
//   delay(10);
   colSelect(i,OFF);
   rowSelect(j,OFF);
*/

// ========== Alles Gelb ==============
   colSelect(i,RESET);
   rowSelect(j,RESET);
   writePanel(0);
//   delay(10);
   colSelect(i,OFF);
   rowSelect(j,OFF);

   i++;
   if (i>31) {
      i=0;
      j++;
   }
   if (j>31) j=0;
  
}

//===================================
// For debugging and testing only
//===================================
void printTest() {   
  int i,j;
      
    clearFrameBuffer(OFF);
    i = printString(2,1,YELLOW,SMALL,"Test mit Space ! & $");
    i = printString(2,15,YELLOW,LARGE,"Noch ein Test \x81");
 //   i = printString(2,18,ON,"Passt das noch ?");
//    i=printChar(10,2,ON,'A');
    printFrameBuffer();

}
