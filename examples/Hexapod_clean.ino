#include <Hexapod_lib.h>

Hexapod hexapod;
Gamepad pad;
String command;
int angle_rotz=0, dlugosc_kroku=50;
int ilosc_odcinkow=3, liczba_krokow=2;

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
      for(uint8_t leg_num=0;leg_num<6;leg_num++){
        for(uint8_t servo_num=0;servo_num<3;servo_num++){
          hexapod.SetServoAngle(90.0,false,leg_num,servo_num);
        }
      }
      hexapod.MoveHexapod();
    }
    else if (command.equals("walk")){
      hexapod.walk(angle_rotz,dlugosc_kroku,ilosc_odcinkow,liczba_krokow);
    }
    else if (command.equals("SetOffset")){
          hexapod.SetOffset();
    }
    else if(command.equals("current")){
      hexapod.info(true);
    }
    else if(command.equals("offset")){
      hexapod.info(false);
    }
    else if(command.equals("d+")){
      dlugosc_kroku+=10;
    }
    else if(command.equals("d-")){
      dlugosc_kroku-=10;
    }
    else if(command.equals("a+")){
      angle_rotz+=45;
    }
    else if(command.equals("a-")){
      angle_rotz-=45;
    }
    else if(command.equals("i+")){
      liczba_krokow+=1;
    }
    else if(command.equals("i-")){
      liczba_krokow-=1;
    }
    else if(command.equals("n+")){
      ilosc_odcinkow+=1;
    }
    else if(command.equals("n-")){
      ilosc_odcinkow-=1;
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
      Serial.println(")");
    }
  }
}