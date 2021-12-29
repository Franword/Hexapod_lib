#include <Hexapod_lib.h>

Gamepad pad;
int angle=0;
int leg_angles[3]={0,10,-10};
int hexapod_angles[6][3]={{0,angle,-angle},{0,angle,-angle},{0,angle,-angle},{0,angle,-angle},{0,angle,-angle},{0,angle,-angle}};
int hexapod_angles_transport[6][3]={{90,20,90},{90,20,90},{90,20,90},{90,20,90},{90,20,90},{90,20,90}};
//int hexapod_angles_init[6][3]={{90,50,80},{90,50,80},{90,50,80},{90,50,80},{90,50,80},{90,50,80}};
static int hexapod_angles_init[6][3]={{90,90,90},{90,90,90},{90,90,90},{90,90,90},{90,90,90},{90,90,90}};

int walk_angles4[6][3]={{90,50,80},{90,38,73},{90,50,80},{90,38,73},{90,50,80},{90,38,73}};
int walk_angles2[6][3]={{85,44,69},{97,52,83},{86,56,90},{94,57,93},{83,49,79},{95,45,71}};
int walk_angles3[6][3]={{90,38,73},{90,50,80},{90,38,73},{90,50,80},{90,38,73},{90,50,80}};
int walk_angles1[6][3]={{94,57,93},{83,49,79},{95,45,71},{85,44,69},{97,52,83},{86,56,90}};

 void set_offset_by_hand(){
   EEPROM.update(0,128-15);
   EEPROM.update(1,128-13);
   EEPROM.update(2,128-13);
   
   EEPROM.update(3,128-12);
   EEPROM.update(4,128-13);
   EEPROM.update(5,128-13);

   EEPROM.update(6,128+0);
   EEPROM.update(7,128-24);
   EEPROM.update(8,128-15);

   EEPROM.update(9,128);
   EEPROM.update(10,128-6);
   EEPROM.update(11,128-6);

   EEPROM.update(12,128+8);
   EEPROM.update(13,128-5);
   EEPROM.update(14,128+3);

   EEPROM.update(15,128+25);
   EEPROM.update(16,128+15);
   EEPROM.update(17,128+8);
 };
String command;
int leg_num=R1;
int servo_num=q1;
bool isrelative=true;

Hexapod hexapod;
int number_of_moves=1;
uint8_t number_of_steps=1;
void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  hexapod.Setup();
  pad.setup();
  Serial.println("ready to go, type help if u want");
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
      Serial.print(angle,DEC);
      Serial.print(", number of moves = ");
      Serial.println(number_of_moves);
    }
    else if(command.equals("help")){
      Serial.println("move: init, MoveHexapod, MoveServo, MoveLeg");
      Serial.println("set type of move: relative, absolute");
      Serial.println("choose leg to move: R1, R2, R3, L1, L2, L3");
      Serial.println("choose q: q1, q2, q3");
      Serial.println("print info: info, help, current, calibrated");
      Serial.println("Save current angles to EEPROM : SaveAngles");
      Serial.println("change number of moves: -, +");
      Serial.println("change one move length: angle-, angle+, angle!");
    }
    else if(command.equals("offset")){
      hexapod.info(false);
    }
    else if(command.equals("current")){
      hexapod.info(true);
    }
     else if(command.equals("init")){
      hexapod.MoveHexapod(hexapod_angles_init,false);
     }
    else if(command.equals("MoveHexapod")){
      for(int i=0;i<6;i++){
        hexapod_angles[i][0]=0;
        hexapod_angles[i][1]=angle;
        hexapod_angles[i][2]=angle;
      };
      for(int i=0;i<number_of_moves;i++){
        hexapod.MoveHexapod(hexapod_angles,isrelative);
      }
    }
    else if(command.equals("transport")){
        hexapod.MoveHexapod(hexapod_angles_transport,false);
    }
    else if (command.equals("MoveLeg")){
      leg_angles[q1]=0;
      leg_angles[q2]=angle;
      leg_angles[q3]=angle;
      for(int i=0;i<number_of_moves;i++){
        hexapod.MoveLeg(leg_angles,isrelative,leg_num);
      }
    }
    else if (command.equals("MoveServo")){
       for(int i=0;i<number_of_moves;i++){
          hexapod.MoveServo(angle,isrelative,leg_num,servo_num);
       }
    }
    else if (command.equals("SetOffset")){
          hexapod.SetOffset(); 
          //set_offset_by_hand(); 
    }
    else if (command.equals("ReadOffset")){
          hexapod.ReadOffset();  
    }
    else if (command.equals("Walk1")){
          hexapod.MoveHexapod(walk_angles1,false);
    }
    else if (command.equals("Walk2")){
          hexapod.MoveHexapod(walk_angles2,false);
    }
    else if (command.equals("Walk3")){
          hexapod.MoveHexapod(walk_angles3,false);
    }
    else if (command.equals("Walk4")){
          hexapod.MoveHexapod(walk_angles4,false);
    }
    else if(command.equals("Walk")){
      hexapod.MoveHexapod(hexapod_angles_init,false);
      //walk init 1
      for(int i=0;i<6;i++){
        hexapod_angles[i][0]=angle/2;
        hexapod_angles[i][1]=0;
        hexapod_angles[i][2]=0;
      };
      for(int i=0;i<number_of_moves;i++){
        hexapod.MoveHexapod(hexapod_angles,true);
      }
      //delay(1000);
      //walk init 2
      hexapod.change_leg_pair();
      for(int i=0;i<6;i++){
        hexapod_angles[i][0]=-angle/2;
        hexapod_angles[i][1]=0;
        hexapod_angles[i][2]=0;
      };
      for(int i=0;i<number_of_moves;i++){
        hexapod.MoveHexapod(hexapod_angles,true);
      }
      delay(1000);
      for(uint8_t n=0;n<number_of_steps;n++){
      //step forward 1
      for(int i=0;i<6;i++){
        hexapod_angles[i][0]=angle/2;
        hexapod_angles[i][1]=angle/2;
        hexapod_angles[i][2]=angle/2;
      };
      for(int i=0;i<number_of_moves;i++){
        //hexapod_wsk->MoveHexapod(hexapod_angles,isrelative);
        hexapod.MoveHexapod(hexapod_angles,true);
      }
      delay(1000);
      //step backward
      hexapod.change_leg_pair();
      for(int i=0;i<6;i++){
        hexapod_angles[i][0]=-angle;
        hexapod_angles[i][1]=0;
        hexapod_angles[i][2]=0;
      };
      for(int i=0;i<number_of_moves;i++){
        hexapod.MoveHexapod(hexapod_angles,true);
      }
      delay(1000);
      //step forward 2
      hexapod.change_leg_pair();
      for(int i=0;i<6;i++){
        hexapod_angles[i][0]=angle/2;
        hexapod_angles[i][1]=-angle/2;
        hexapod_angles[i][2]=-angle/2;
      };
      for(int i=0;i<number_of_moves;i++){
        hexapod.MoveHexapod(hexapod_angles,true);
      }
      delay(1000);
      hexapod.change_leg_pair();
      }
      hexapod.MoveHexapod(hexapod_angles_init,false);
    }
    else if (command.equals("par")){
       hexapod.change_leg_pair();
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
    else if (command.equals("-")){
      number_of_moves=number_of_moves-1;
      Serial.print("number of moves = ");
      Serial.println(number_of_moves);
    }
    else if (command.equals("+")){
      number_of_moves=number_of_moves+1;
      Serial.print("number of moves = ");
      Serial.println(number_of_moves);
    }
    else if (command.equals("angle-")){
      angle-=10;
      Serial.print("angle = ");
      Serial.println(angle);
    }
    else if (command.equals("angle+")){
      angle+=10;
      Serial.print("angle = ");
      Serial.println(angle);
    }
    else if (command.equals("angle!")){
      angle=-angle;
      Serial.print("angle = ");
      Serial.println(angle);
    }
    else{
      Serial.println("incorrect command");
    }
  }
}