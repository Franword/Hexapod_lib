#include <Hexapod_lib.h>

Gamepad pad;
int angle=0;
int leg_angles[3]={0,10,-10};
int hexapod_angles[6][3]={{0,angle,-angle},{0,angle,-angle},{0,angle,-angle},{0,angle,-angle},{0,angle,-angle},{0,angle,-angle}};
int hexapod_angles_init[6][3]={{90,90,90},{90,90,90},{90,90,90},{90,90,90},{90,90,90},{90,90,90}};
//uint8_t walk_angles[6][3]={{94,77,98},{80,60,59},{95,77,71},{83,61,54},{97,107,105},{85,60,65}};
/* modified
{{{97,62,91},{80,60,59},{101,61,55},{83,61,54},{104,90,94},{85,60,65}},
{{94,77,98},{80,60,59},{95,77,71},{83,61,54},{97,107,105},{85,60,65}},
{{73,63,50},{104,21,41},{81,62,70},{97,27,50},{69,60,58},{101,12,27}},
{{73,63,50},{117,62,71},{81,62,70},{102,66,84},{69,60,58},{116,61,53}},
{{73,63,50},{104,92,92},{81,62,70},{97,93,98},{69,60,58},{101,94,84}},
{{94,42,53},{80,60,59},{95,40,44},{83,61,54},{97,41,49},{85,60,65}},
{{97,62,71},{80,60,59},{101,61,55},{83,61,54},{104,60,64},{85,60,65}}};
*/
/*
{{{97,62,71},{80,60,59},{101,61,55},{83,61,54},{104,60,64},{85,60,65}},
{{94,77,78},{80,60,59},{95,77,71},{83,61,54},{97,77,75},{85,60,65}},
{{73,63,50},{104,21,41},{81,62,70},{97,27,50},{69,60,58},{101,12,27}},
{{73,63,50},{117,62,71},{81,62,70},{102,66,84},{69,60,58},{116,61,53}},
{{73,63,50},{104,92,92},{81,62,70},{97,93,98},{69,60,58},{101,94,84}},
{{94,42,53},{80,60,59},{95,40,44},{83,61,54},{97,41,49},{85,60,65}},
{{97,62,71},{80,60,59},{101,61,55},{83,61,54},{104,60,64},{85,60,65}}};
*/
String command;
int leg_num=R1;
int servo_num=q1;
bool isrelative=true;
//Hexapod* hexapod_wsk;
Hexapod hexapod;
int number_of_moves=1;
uint8_t number_of_steps=1;
void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //hexapod_wsk = new Hexapod();
  hexapod.Setup();
  pad.setup();
  Serial.println("ready to go, type help if u want");
  /*for(int leg_num=0; leg_num <=5;leg_num++){
    for(int q=0; q <=2;q++){
    hexapod_angles[leg_num][q]=0;
    //Serial.print(hexapod_angles[leg_num][q]);
    }
  }*/
  //hexapod_wsk->MoveInit();
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
    else if(command.equals("calibrated")){
      //hexapod_wsk->info(false);
      hexapod.info(false);
    }
    else if(command.equals("current")){
      //hexapod_wsk->info(true);
      hexapod.info(true);
    }
     else if(command.equals("init")){
      //hexapod_wsk->MoveInit();
      hexapod.MoveInit();
     }
     else if(command.equals("init2")){
      //hexapod_wsk->MoveHexapod(hexapod_angles_init,false);
      hexapod.MoveHexapod(hexapod_angles_init,false);
     }
    else if(command.equals("MoveHexapod")){
      for(int i=0;i<6;i++){
        hexapod_angles[i][0]=0;
        hexapod_angles[i][1]=angle;
        hexapod_angles[i][2]=angle;
      };
      for(int i=0;i<number_of_moves;i++){
        //hexapod_wsk->MoveHexapod(hexapod_angles,isrelative);
        hexapod.MoveHexapod(hexapod_angles,isrelative);
      }
    }
    else if (command.equals("MoveLeg")){
      leg_angles[q1]=0;
      leg_angles[q2]=angle;
      leg_angles[q3]=angle;
      for(int i=0;i<number_of_moves;i++){
        //hexapod_wsk->MoveLeg(leg_angles,isrelative,leg_num);
        hexapod.MoveLeg(leg_angles,isrelative,leg_num);
      }
    }
    else if (command.equals("MoveServo")){
       for(int i=0;i<number_of_moves;i++){
          //hexapod_wsk->MoveServo(angle,isrelative,leg_num,servo_num);
          hexapod.MoveServo(angle,isrelative,leg_num,servo_num);
       }
    }
    else if(command.equals("Walk")){
      hexapod.MoveInit();
      //walk init 1
      for(int i=0;i<6;i++){
        hexapod_angles[i][0]=angle/2;
        hexapod_angles[i][1]=0;
        hexapod_angles[i][2]=0;
      };
      for(int i=0;i<number_of_moves;i++){
        //hexapod_wsk->MoveHexapod(hexapod_angles,isrelative);
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
        //hexapod_wsk->MoveHexapod(hexapod_angles,isrelative);
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
        //hexapod_wsk->MoveHexapod(hexapod_angles,isrelative);
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
        //hexapod_wsk->MoveHexapod(hexapod_angles,isrelative);
        hexapod.MoveHexapod(hexapod_angles,true);
      }
      delay(1000);
      hexapod.change_leg_pair();
      }
      hexapod.MoveInit();
    }
    else if (command.equals("par")){
       //hexapod_wsk->change_leg_pair();
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
    else if (command.equals("SaveAngles")){
      //hexapod_wsk->SaveAnglesEEPROM();
      hexapod.SaveAnglesEEPROM();
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