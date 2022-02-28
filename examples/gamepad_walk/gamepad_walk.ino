#include <Hexapod_lib.h>

Hexapod hexapod;
Gamepad pad;
String command;
int angle_rotz=0, dlugosc_kroku=70, ilosc_odcinkow=25, liczba_krokow=1, delay_micros=13,moves_without_line=12;
float pos[3];
bool if_rotate_left=true;
int z=0, y=0, x=0;
int test;
//siema
void setup() {
Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  hexapod.Setup();
  pad.setup();
}

void loop() {
  pad.Get_PS2Dat(pad.PS2buf);
  if(pad.PS2buf[tab_arrows_start] == up && test == 1) 
  {
    test = 0;
    Serial.println("Walk");
    hexapod.walk(angle_rotz,dlugosc_kroku,ilosc_odcinkow,liczba_krokow, delay_micros,moves_without_line, true);
    delay(1000);
  }
   if(pad.PS2buf[tab_arrows_start] == left && test == 0) 
  {
    test = 1;
    Serial.println("Rotate");
    hexapod.walk(-90,dlugosc_kroku,ilosc_odcinkow,liczba_krokow, delay_micros,moves_without_line, false);
    delay(1000);
  }
}