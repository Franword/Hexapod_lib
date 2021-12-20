#include "Hexapod.h"
//*******************Hexapod class*****************************************
Hexapod::Hexapod(){
	Serial.println("Creating Hexapod");
	_pwm[0] = PWM(0x40);
	_pwm[1] = PWM(0x41);
	_leg[R1]=Leg(R1,&_pwm[0]);
	_leg[R2]=Leg(R2,&_pwm[1]);
	_leg[R3]=Leg(R3,&_pwm[1]);
	_leg[L1]=Leg(L1,&_pwm[0]);
	_leg[L2]=Leg(L2,&_pwm[0]);
	_leg[L3]=Leg(L3,&_pwm[1]);
	//serial
	Serial.println("Hexapod created\n");
};
void Hexapod::MoveServo(int angle,bool relative,int leg_num,int servo_num){
	//function
	_leg[leg_num].MoveServo(angle,relative,servo_num);
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
};
void Hexapod::MoveLeg(int angle[3],bool relative,int leg_num){
	//function
	_leg[leg_num].MoveLeg(angle,relative);
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
		Serial.println("]");
};
void Hexapod::MoveHexapod(int angle[6][3],bool relative){
	//function
	 for(int leg_num=0; leg_num <=5;leg_num++){
		int temp[3]={angle[leg_num][q1],angle[leg_num][q2],angle[leg_num][q3]};
		_leg[leg_num].MoveLeg(temp,relative);
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
		Serial.println("]");
	};
};
void Hexapod::info(bool if_current){
	for(int leg_num=0; leg_num <=5;leg_num++){
		_leg[leg_num].info(if_current);
	}
};
void Hexapod::SaveAnglesEEPROM(){
	for(int leg_num=0; leg_num <=5;leg_num++){
		_leg[leg_num].SaveAnglesEEPROM();
	}
};
void Hexapod::MoveInit(){
	for(int leg_num=0; leg_num <=5;leg_num++){
		_leg[leg_num].MoveInit();
	}
};
