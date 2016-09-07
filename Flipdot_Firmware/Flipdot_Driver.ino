///////////////// Flipdot Hack //////////////////////
//   
// Driver for Brose-Flipdot Display
// ATTENTION: DO NOT EXPERIMENT WITH THIS CODE 
// WITHOUT MEASURING SIGNALS AT THE DISPLAY
// #### DISPLAY CAN EASILY BY DESTROYED ######
//
// Arduino Pins:
//     Digital 0..5     Row#
//     Digital 8        Row SET
//     Digital 9        Row RESET
//     Digital 10..12   Panel#
//     Digital 13       Panel SELECT
//     Analog 0         FP2800 A0
//     Analog 1         FP2800 A1
//     Analog 2         FP2800 A2
//     Analog 3         FP2800 B0
//     Analog 4         FP2800 B1
//     Analog 5         FP2800 D
/////////////////////////////////////////////////////

#include "Flipdot.h"

//###################### Public Functions #############################################

void flipdotSetup() {
  
    // Alle benötigten Pins auf Output
    for (int i=3; i<14; i++) pinMode(i, OUTPUT);
    pinMode(A0,OUTPUT);
    pinMode(A1,OUTPUT);
    pinMode(A2,OUTPUT);
    pinMode(A3,OUTPUT);
    pinMode(A4,OUTPUT);
    pinMode(A5,OUTPUT);
      
    // Alles auf High setzen, so macht es der originale Mikrocontroller auch, wenn alles inaktiv ist
    for (int i=3; i<14; i++) digitalWrite(i, HIGH);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, HIGH);
    digitalWrite(A5, HIGH);

    i=0;
    j=0;
}

//===================================================
// Set or Reset one Pixel
// state = SET means yellow
// state = RESET means black
//===================================================
void pixel(int x, int y, int state) {
  int panelNr, colNr;
  if ((x<169) && (x>=0) && (y>=0) && (y<32)) {
      panelNr = x/28;   // integer division
      colNr = x%28;     // modulo division
      colSelect(colNr,state);
      rowSelect(y+1,state);

      writePanel(panelNr);
  }
}


//####################### Internal functions ########################################


//===================================================
// Diese Funktion setzt die Zeile 
// Sie muss immer vor der Spalte aufgerufen werden
// Parameter:  state = SET   Pixel wird gesetzt
//             state = RESET Pixel wird zurückgesetzt
//===================================================
void rowSelect(int row, int state) {
  row++;
  if (row>6) row++;
  if (row>14) row++;
  if (row>22) row++;
  digitalWrite(3, row & 4);   // Scrambled to make up for wiring
  digitalWrite(4, row & 8);
  digitalWrite(5, row & 16);
  digitalWrite(6, row & 1);
  digitalWrite(7, row & 2);
  if (state == SET) {
     digitalWrite(9, HIGH); // SET (immer zuerst nach HIGH)
     digitalWrite(8, LOW);  // Diese beiden Pins müssen immer komplementär sein - sonst raucht es
 } else if (state == RESET) {
    digitalWrite(8, HIGH); // Diese beiden Pins müssen immer komplementär sein - sonst raucht es
    digitalWrite(9, LOW);  // RESET
  } else {
    digitalWrite(8, HIGH); // OFF
    digitalWrite(9, HIGH); 
  }
}

//===================================================
// Diese Funktion setzt die Spalte 
// Parameter:  state = SET   Pixel wird gesetzt
//             state = RESET Pixel wird zurückgesetzt
//===================================================
void colSelect(int col, int state) {
  col++;
  if (col>7)  col++;  // Somehow codes 7,16,24 have to be skipped
  if (col>15) col++;
  if (col>23) col++;

  digitalWrite(A0, col & 1);
  digitalWrite(A1, col & 2);
  digitalWrite(A2, col & 4);
  digitalWrite(A3, col & 8);
  digitalWrite(A4, col & 16);

  digitalWrite(A5, state);

}

//===================================================
// Diese Funktion steuert ein Panel an
// Darf nur ganz kurz gepulst werden da sonst die 
// Dioden zu heiß werden 
// Parameter:  panel = 0...6 
//             Gibt die Panelnummer an. 
//===================================================
void writePanel(int panel) {

  if (panel >= 0) {
    digitalWrite(10, panel & 1);
    digitalWrite(11, panel & 2);
    digitalWrite(12, panel & 4);

    digitalWrite(13, LOW);   // Kurzer Puls, der das Panel enabled
    delay(10);
  } 
  digitalWrite(13, HIGH);  
}
