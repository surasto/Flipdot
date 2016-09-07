///////////////// Flipdot Hack //////////////////////
//   
// Testsoftware zum dekodieren des Display busses
// 6-Jul-2016
//
// Pinbelegung:
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

#define SET 1
#define RESET 0
#define OFF -1
int i=0;
int j=0;

// Wert Binär Resorted Zeile
//        1
//      21684 
// 1    00001  OOIOO  3,            
// 2    00010  OIOOO  6           , 
// 3    00011  OIIOO  10, 
// 4    00100  IOOOO  13, 
// 5    00101  IOIOO  17, 
// 6    00110 ?
// 7    00111 ?, 
// 8    01000 ?, 
// 9    01001  OOIOI  4,             
// 10   01010  OIOOI  7,            
// 11   01011  OIIOI  11, 
// 12   01100  IOOOI  14
// 13   01101  IOIOI  17, 
// 14   01110 ? 
// 15   01111 ?, 
// 16   10000  OOOIO  1,            
// 17   10001  OOIIO  5,         
// 18   10010  OIOIO  8,           
// 19   10011  OIIIO  12, 
// 20   10100  IOOIO  15, 
// 21   10101 ?, 
// 22   10110 ?, 
// 23   10111 ?,
// 24   11000  OOOII  2,           3
// 25   11001 ? 
// 26   11010  OIOII  9, 
// 27   11011 ?, 
// 28   11100  IOOII  16, 
//const int rowtranslate[] = {

void setup() {
  
    Serial.begin(9600);
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
j=0;
i=0;
}

void loop() {
  
   writePanel(-1);
   //delay(500);

// ============== Alles Schwarz ============
/*  colSelect(i,SET);
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


//j=0;
   i++;

   if (i>31) {
      i=0;
      delay(1000);
      Serial.println(j);
      j++;
   }
   if (j>28) {
     j=0;
   }  

}

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
  digitalWrite(3, row & 4);  // was 1 
  digitalWrite(4, row & 8);  // was 2
  digitalWrite(5, row & 16); // was 4
  digitalWrite(6, row & 1);  // was 8
  digitalWrite(7, row & 2);  // was 16
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
  digitalWrite(A0, col & 1);
  digitalWrite(A1, col & 2);
  digitalWrite(A2, col & 4);
  digitalWrite(A3, col & 8);
  digitalWrite(A4, col & 16);

  digitalWrite(A5, state);

}

//===================================================
// Diese Funktion steuert ein Panel an
// Vermutlich darf sie dass nur ganz kurz tun ----- Muss ich noch cheeck 
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
