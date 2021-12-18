#include <Hexapod_lib.h>

int angle=10;
int leg_angles[3]={0,10,-10};
int hexapod_angles[6][3]={{10,20,30},{20,30,40},{40,50,60},{50,60,70},{60,70,80},{70,80,90}};
int hexapod_angles_init[6][3]={{SERVOMAX/2,SERVOMAX/3,SERVOMAX/3},{SERVOMAX/2,SERVOMAX/3,SERVOMAX/3},{SERVOMAX/2,SERVOMAX/3,SERVOMAX/3},
{SERVOMAX/2,SERVOMAX/3,SERVOMAX/3},{SERVOMAX/2,SERVOMAX/3,SERVOMAX/3},{SERVOMAX/2,SERVOMAX/3,SERVOMAX/3}};
String command;
int leg_num=R1;
int servo_num=q1;
bool isrelative=true;
Hexapod* hexapod_wsk;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  hexapod_wsk = new Hexapod();
  Serial.println("ready to go, type help if u want");
  /*for(int leg_num=0; leg_num <=5;leg_num++){
    for(int q=0; q <=2;q++){
    hexapod_angles[leg_num][q]=0;
    //Serial.print(hexapod_angles[leg_num][q]);
    }
  }*/
}
void loop() {
  if(Serial.available()){
    command = Serial.readStringUntil('\n');
    command.trim();
     if (command.equals("info")){
      print_leg_num(leg_num);
      Serial.print(leg_num,DEC);
      Serial.print(", servo_num= ");
      print_servo_num(servo_num);
      if(isrelative){
        Serial.print(", relative");
      }
      else{
        Serial.print(", absolute");
      }
      Serial.print(", angle= ");
      Serial.println(angle,DEC);
    }
    else if(command.equals("help")){
      Serial.println("type:init, MoveHexapod, MoveServo, MoveLeg,relative, absolute\nR1, R2, R3, L1, L2, L3, q1, q2, q3, help");
    }
     else if(command.equals("init")){
      hexapod_wsk->MoveHexapod(hexapod_angles_init,false);
     }
    else if(command.equals("MoveHexapod")){
      hexapod_wsk->MoveHexapod(hexapod_angles,isrelative);
    }
    else if (command.equals("MoveLeg")){
      hexapod_wsk->MoveLeg(leg_angles,isrelative,leg_num);
    }
    else if (command.equals("MoveServo")){
      hexapod_wsk->MoveServo(angle,isrelative,leg_num,servo_num);
    }
    else if (command.equals("R1")){
      leg_num=R1;
      Serial.println("leg_num = R1");
    }
    else if (command.equals("R2")){
      leg_num=R2;
      Serial.println("leg_num = R2");
    }
    else if (command.equals("R3")){
      leg_num=R3;
      Serial.println("leg_num = R3");
    }
    else if (command.equals("L1")){
      leg_num=L1;
      Serial.println("leg_num = L1");
    }
    else if (command.equals("L2")){
      leg_num=L2;
      Serial.println("leg_num = L2");
    }
    else if (command.equals("L3")){
      leg_num=L3;
      Serial.println("leg_num = L3");
    }
    else if (command.equals("q1")){
      servo_num=q1;
      Serial.println("servo_num = q1");
    }
    else if (command.equals("q2")){
      servo_num=q2;
      Serial.println("servo_num = q2");
    }
    else if (command.equals("q3")){
      servo_num=q3;
      Serial.println("servo_num = q3");
    }
    else if (command.equals("relative")){
      isrelative=true;
      Serial.println("move set to relative");
    }  
    else if (command.equals("absolute")){
      isrelative=false;
      Serial.println("move set to absolute");
    }     
    else{
      Serial.println("incorrect command");
    }
  }
}
