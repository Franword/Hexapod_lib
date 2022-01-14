#include <Hexapod_lib.h>

Hexapod hexapod;
Gamepad pad;
String command;
int angle_rotz=0, dlugosc_kroku=70, ilosc_odcinkow=25, liczba_krokow=1, delay_micros=13,moves_without_line=12;
float pos[3];
bool if_rotate_left=true;
int z=0, y=0, x=0;
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
  if(Serial.available()){
    command=Serial.readStringUntil('\n');
    command.trim();
    if(command.equals("init")){
      Serial.println(command);
      hexapod.SetInit();
      hexapod.MoveHexapod();
    }
    else if (command.equals("walk")){
      hexapod.walk(angle_rotz,dlugosc_kroku,ilosc_odcinkow,liczba_krokow, delay_micros,moves_without_line, true);
    }
    else if (command.equals("rotate")){
      if(if_rotate_left){
        hexapod.walk(-90,dlugosc_kroku,ilosc_odcinkow,liczba_krokow, delay_micros,moves_without_line, false);
      }
      else{
        hexapod.walk(90,dlugosc_kroku,ilosc_odcinkow,liczba_krokow, delay_micros,moves_without_line, false);
      }
      
    }
    else if (command.equals("SetOffset")){
      Serial.println(command);
      hexapod.SetOffset();
    }
    else if (command.equals("h")){
      Serial.println(command);
      pos[0]=float(x);
      pos[1]=float(y);
      pos[2]=float(z);
      for(uint8_t i=0;i<10;i+=2){
          for(uint8_t leg_num=0;leg_num<6;leg_num++){
          hexapod.SetLegPos(pos,leg_num,true);  
      }
      hexapod.MoveHexapod();
      }
    }
    else if(command.equals("current")){
      hexapod.info(true);
    }
    else if(command.equals("offset")){
      hexapod.info(false);
    }
    else if(command.equals("d+")){
      Serial.println(command);
      dlugosc_kroku++;
    }
    else if(command.equals("d-")){
      Serial.println(command);
      dlugosc_kroku--;
    }
    else if(command.equals("a+")){
      Serial.println(command);
      angle_rotz+=45;
    }
    else if(command.equals("a-")){
      Serial.println(command);
      angle_rotz-=45;
    }
    else if(command.equals("i+")){
      Serial.println(command);
      liczba_krokow+=1;
    }
    else if(command.equals("i-")){
      Serial.println(command);
      liczba_krokow-=1;
    }
    else if(command.equals("n+")){
      Serial.println(command);
      ilosc_odcinkow+=1;
    }
    else if(command.equals("n-")){
      Serial.println(command);
      ilosc_odcinkow-=1;
    }
    else if(command.equals("p+")){
      Serial.println(command);
      moves_without_line++;
    }
    else if(command.equals("p-")){
      Serial.println(command);
      moves_without_line--;
    }
    else if(command.equals("t+")){
      Serial.println(command);
      delay_micros+=1;
    }
    else if(command.equals("t-")){
      Serial.println(command);
      delay_micros-=1;
    }
    else if (command.equals("z")){
      if(z>=1){
        z=-1;
      }
      else{
        z+=1;
      }
      Serial.print("z=");
      Serial.println(z);
    }
    else if (command.equals("y")){
      if(y>=1){
        y=-1;
      }
      else{
        y+=1;
      }
      Serial.print("y=");
      Serial.println(y);
    }
    else if (command.equals("x")){
      if(x>=1){
        x=-1;
      }
      else{
        x+=1;
      }
      Serial.print("x=");
      Serial.println(x);
    }
    else if (command.equals("r")){
      if_rotate_left=!if_rotate_left;
      Serial.print("r=");
      Serial.println(if_rotate_left);
    }
    else{
      Serial.print("walk(a=");
      Serial.print(angle_rotz);
      Serial.print(", d=");
      Serial.print(dlugosc_kroku);
      Serial.print(", n=");
      Serial.print(ilosc_odcinkow);
      Serial.print(", i=");
      Serial.print(liczba_krokow);
      Serial.print(", t=");
      Serial.print(delay_micros);
      Serial.print(", p=");
      Serial.print(moves_without_line);
      Serial.print(") r=");
      Serial.println(if_rotate_left);
    }
  }
}