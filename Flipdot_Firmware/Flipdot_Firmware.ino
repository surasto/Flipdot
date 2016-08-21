////////////////////////////////////////////////////////////////////////////
// Flipdot_Firmware
// CC-BY-SA-NC    8/2016 C-Hack (Ralf@Surasto.de)
//
// Hauptprogramm für Arduino
// Arduino wartet auf Befehle über die serielle Schnittstelle und steuert 
// entsprechend die Flipdot-Anzeige
//
// Datenfomat:
//    <Byte 1>                Befehl
//    <Byte 2> + <Byte 3>     16 bit x-Koordinate
//    <Byte 4>                 8 bit y-Koordinate
//    <Byte 5...n>            Textstring  (Ende mit 0x00)
//
//    Befehle:
//      0x01   Print String SMALL
//      0x02   Print String MEDIUM
//      0x03   Print String LARGE
//      0x04   Clear Screen Yellow
//      0x05   Clear Screen Black
////////////////////////////////////////////////////////////////////////////


#define SET 1
#define RESET 0
#define OFF -1

int i,j;

void setup() {
  
  Serial.begin(9600);
  flipdotSetup();

}

void loop() {
  
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

