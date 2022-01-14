#include <Hexapod_lib.h>

Hexapod hexapod;
Gamepad pad;
String command;
int angle_rotz=0, dlugosc_kroku=50;
//int ilosc_odcinkow=25, liczba_krokow=2, delay_micros=13;
int ilosc_odcinkow=28, liczba_krokow=2, delay_micros=50, percent_of_moves_without_line=50;
float pos[3];
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
      //float pos[3]={100.0,0.0,-100.0};
      for(uint8_t leg_num=0;leg_num<6;leg_num++){
        for(uint8_t servo_num=0;servo_num<3;servo_num++){
          hexapod.SetServoAngle(90.0,false,leg_num,servo_num);
        }
      }
      hexapod.MoveHexapod();
    }
    else if (command.equals("walk")){
      hexapod.walk(angle_rotz,dlugosc_kroku,ilosc_odcinkow,liczba_krokow, delay_micros,percent_of_moves_without_line);
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
      dlugosc_kroku+=10;
    }
    else if(command.equals("d-")){
      Serial.println(command);
      dlugosc_kroku-=10;
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
      percent_of_moves_without_line+=5;
    }
    else if(command.equals("p-")){
      Serial.println(command);
      percent_of_moves_without_line-=5;
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
      Serial.print(percent_of_moves_without_line);
      Serial.println(")");
    }
  }
}