#include "Hexapod.h"
//*******************Hexapod class*****************************************
Hexapod::Hexapod(){
}
void Hexapod::Setup(){
	Serial.println("Creating Hexapod");
	//_pwm[0] = PWM(0x40);
	//_pwm[1] = PWM(0x41);
	for(uint8_t leg_num=0;leg_num<6;leg_num++){
		for(uint8_t servo_num=0;servo_num<3;servo_num++)
		{
			if(leg_num==R1 ||leg_num==L1 ||leg_num==L2){
				_servo[leg_num][servo_num].Setup(leg_num,servo_num);
			}
			else{
				_servo[leg_num][servo_num].Setup(leg_num,servo_num);
			}
		}
	_pwm[0]=Adafruit_PWMServoDriver();
	_pwm[0].begin();
	_pwm[0].setOscillatorFrequency(OSCILATOR_FREQ);
	_pwm[0].setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

	_pwm[1]=Adafruit_PWMServoDriver(0x41); 
	_pwm[1].begin();
	_pwm[1].setOscillatorFrequency(OSCILATOR_FREQ);
	_pwm[1].setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
	}
	_leg_pair=true;
	//_kin=Kinematics(80, 150);
	//serial
	for(uint8_t leg_num=0;leg_num<6;leg_num++){
		for(uint8_t servo_num=0;servo_num<3;servo_num++){
			MoveServo(90,false,leg_num,servo_num);
		}
	}
	Serial.println("Hexapod created\n");
};
void Hexapod::MoveServo(int angle,bool relative,uint8_t leg_num,uint8_t servo_num){
	//function
	_pulse[leg_num][servo_num]=_servo[leg_num][servo_num].MoveServo(angle,relative);
	//update pos
	int angles_to_update_pos[3];
	angles_to_update_pos[0]=_servo[leg_num][q1].get_angle();
	angles_to_update_pos[1]=_servo[leg_num][q2].get_angle();
	angles_to_update_pos[2]= _servo[leg_num][q3].get_angle();
	dir_kin(angles_to_update_pos, leg_num);
	//serial
		print_leg_num(leg_num);
		print_servo_num(servo_num);
		if(relative){
			Serial.print(" moved by [");
		}
		else{
			Serial.print(" moved to [");
		}
		Serial.print(angle);
		Serial.println("]");
		Move(leg_num,servo_num);
};
void Hexapod::MoveLeg(int angle[3],bool relative,uint8_t leg_num){
	//function
	for(int servo_num=0;servo_num<3;servo_num++){
		_pulse[leg_num][servo_num]=_servo[leg_num][servo_num].MoveServo(angle[servo_num],relative);
	}
	//update pos
	int angles_to_update_pos[3];
	angles_to_update_pos[0]=_servo[leg_num][q1].get_angle();
	angles_to_update_pos[1]=_servo[leg_num][q2].get_angle();
	angles_to_update_pos[2]= _servo[leg_num][q3].get_angle();
	dir_kin(angles_to_update_pos, leg_num);
	//serial
		print_leg_num(leg_num);
		if(relative){
			Serial.print(" moved by [");
		}
		else{
			Serial.print(" moved to [");
		}
		Serial.print(angle[q1]);
		Serial.print(", ");
		Serial.print(angle[q2]);
		Serial.print(", ");
		Serial.print(angle[q3]);
		Serial.print("]	pos = [");
		for(int i=0;i<3;i++){
			Serial.print(_pos[leg_num][i]);
			Serial.print(" ");
		}
		Serial.println("]");
		//for(int servo_num=0;servo_num<3;servo_num++){
		//Move(leg_num,servo_num);
		//}
};
void Hexapod::MoveHexapod(int angle[6][3],bool relative){
	int angles_to_update_pos[3];
	//function
	 for(byte leg_num=0; leg_num <=5;leg_num++){
		 //if(if_leg_active(leg_num)){
		for(int servo_num=0;servo_num<3;servo_num++){
			_pulse[leg_num][servo_num]=_servo[leg_num][servo_num].MoveServo(angle[leg_num][servo_num],relative);
			//update pos
			angles_to_update_pos[0]=_servo[leg_num][q1].get_angle();
			angles_to_update_pos[1]=_servo[leg_num][q2].get_angle();
			angles_to_update_pos[2]= _servo[leg_num][q3].get_angle();
			dir_kin(angles_to_update_pos, leg_num);
		}
		
		//serial
		print_leg_num(leg_num);
		if(relative){
			Serial.print(" moved by [");
		}
		else{
			Serial.print(" moved to [");
		}
		Serial.print(angle[leg_num][q1]);
		Serial.print(", ");
		Serial.print(angle[leg_num][q2]);
		Serial.print(", ");
		Serial.print(angle[leg_num][q3]);
		Serial.print("]	pos = [");
		for(int i=0;i<3;i++){
			Serial.print(_pos[leg_num][i]);
			Serial.print(" ");
		}
		Serial.println("]");
		//}
	};
	for(int leg_num=0; leg_num <=5;leg_num++){
		for(int servo_num=0;servo_num<3;servo_num++)
		{
			Move(leg_num,servo_num);
		}
	}
};
void Hexapod::info(bool if_current){
	for(int leg_num=0; leg_num <=5;leg_num++){
		print_leg_num(leg_num);
		Serial.print("	q = [");
		for(int servo_num=0;servo_num<3;servo_num++){
			_servo[leg_num][servo_num].info(if_current);
			Serial.print(" ");
		}
		Serial.print("]	pos = [");
		for(int i=0;i<3;i++){
			Serial.print(_pos[leg_num][i]);
			Serial.print(" ");
		}
		Serial.println("]");
	}
};
void Hexapod::SetOffset(){
	for(int leg_num=0; leg_num <=5;leg_num++){
		for(int servo_num=0;servo_num<3;servo_num++){
			_servo[leg_num][servo_num].SetOffset();
		}
	}
	Serial.println("offset values have been saved to EEPROM");
};
void Hexapod::ReadOffset(){
	for(int leg_num=0; leg_num <=5;leg_num++){
		print_leg_num(leg_num);
		Serial.print(" [");
		for(int servo_num=0;servo_num<3;servo_num++){
			_servo[leg_num][servo_num].ReadOffset();
			Serial.print(" ");
		}
		Serial.println("]");
	}
	Serial.println("offset values have beend read from EEPROM");
};
bool Hexapod::if_leg_active(uint8_t leg_num){
	if(_leg_pair){
		if(leg_num == R1 || leg_num == L2 || leg_num == R3){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if(leg_num == L1 || leg_num == R2 || leg_num == L3){
			return true;
		}
		else{
			return false;
		}
	}
};
void Hexapod::change_leg_pair(){
	_leg_pair=!_leg_pair;
};
void Hexapod::Move(uint8_t leg_num,uint8_t servo_num){
	//if(leg_num==R1){	
	_pwm[_servo[leg_num][servo_num].get_pwm_num()].setPWM(_servo[leg_num][servo_num].get_pwm_address(),0, _pulse[leg_num][servo_num]);
	//}
};
void Hexapod::MoveL(uint8_t leg_num){
	for(int servo_num=0;servo_num<3;servo_num++){
		Move(leg_num,servo_num);
	}
};
void Hexapod::inv_kin(int x, int y, int z,uint8_t leg_num, bool relative){
	if(relative){
		x+=_pos[leg_num][0];
		y+=_pos[leg_num][1];
		z+=_pos[leg_num][2];
	}
	_pos[leg_num][0]=x;
	_pos[leg_num][1]=y;
	_pos[leg_num][2]=z;
	float a2=80;
	float a3=150;
	float xPrime = sqrt(pow(x, 2) + pow(y, 2));
	float theta1 = degrees(atan(y/x));
  	float theta3 = -degrees(acos((pow(xPrime, 2) + pow(z, 2) - pow(a2, 2) - pow(a3, 2))/(2 * a2 * a3)));
  	float theta2 = degrees(atan(z/xPrime) - atan((a3 * sin(radians(theta3)))/(a2 + a3 * cos(radians(theta3)))));
	int angle[3];
  if(leg_num==0 || leg_num==1 ||leg_num ==2){
    angle[0]=90+int(theta1);
  }
  else{
    angle[0]=90-int(theta1);
  }
  angle[1]=90-int(theta2);
  angle[2]=180+int(theta3);
  MoveLeg(angle,false,leg_num);
};

void Hexapod::dir_kin(int angle[3], uint8_t leg_num){
	float theta1;
	 if(leg_num==0 || leg_num==1 ||leg_num ==2){
    	theta1=float(angle[0]-90);
  	}
  	else{
    	theta1=float(90-angle[0]);
  	}
	float theta2=float(90-angle[1]);
  	float theta3=float(angle[2]-180);

	float xPrime = a2 * cos(radians(theta2)) + a3 * cos(radians(theta2) + radians(theta3));
	_pos[leg_num][0] = int(xPrime * cos(radians(theta1)));
	_pos[leg_num][1] = int(xPrime * sin(radians(theta1)));
	_pos[leg_num][2] = int(a2 * sin(radians(theta2)) + a3 * sin(radians(theta2) + radians(theta3)));
};