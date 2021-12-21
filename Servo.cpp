#include "Servo.h"
Servo::Servo(){};
Servo::Servo(int leg_num,int servo_num, PWM* PWM_wsk)
{
	//Serial.print("Servo ");
	_PWM_wsk=PWM_wsk;
	switch (leg_num) {
		case R1:
			//Serial.print ("R1 ");
			if (servo_num==q1){
				_address=R1q1;}
			if (servo_num==q2){
				_address=R1q2;}
			if (servo_num==q3){
				_address=R1q3;}
		break;
		case R2:
			//Serial.print ("R2 ");
			if (servo_num==q1){
				_address=R2q1;}
			if (servo_num==q2){
				_address=R2q2;}
			if (servo_num==q3){
				_address=R2q3;}
		break;
		case R3:
			//Serial.print ("R3 ");
			if (servo_num==q1){
				_address=R3q1;}
			if (servo_num==q2){
				_address=R3q2;}
			if (servo_num==q3){
				_address=R3q3;}
		break;
		case L1:
			//Serial.print ("L1 ");
			if (servo_num==q1){
				_address=L1q1;}
			if (servo_num==q2){
				_address=L1q2;}
			if (servo_num==q3){
				_address=L1q3;}
		break;
		case L2:
			//Serial.print ("L2 ");
			if (servo_num==q1){
				_address=L2q1;}
			if (servo_num==q2){
				_address=L2q2;}
			if (servo_num==q3){
				_address=L2q3;}
		break;
		case L3:
			//Serial.print ("L3 ");
			if (servo_num==q1){
				_address=L3q1;}
			if (servo_num==q2){
				_address=L3q2;}
			if (servo_num==q3){
				_address=L3q3;}
	}
	if(leg_num==L1 || leg_num==L2 ||leg_num==L3){
		_inverse=true;
	}
	else{
		_inverse=false;
	}
	_id=3*leg_num+servo_num;
	//serial
	/*Serial.print(" q");
	Serial.print(servo_num,DEC);
	Serial.print(" created");
	Serial.print(", adress- ");
	Serial.print(_address,DEC);
	Serial.print(", inverse- ");
	Serial.println(_inverse,DEC);*/
};
void Servo::MoveServo(int angle,bool relative)
{
	//Serial.println("\nServo::MoveServo");
	if(relative){
		if(_inverse){
			angle=_angle-angle;
		}
		else{
			angle=_angle+angle;
		}
	}
	else{
		if(_inverse){
			angle=180-angle;
		}
	}
	_PWM_wsk->SetPWM(_address, angle);
	_angle=angle;
	//serial
	/*Serial.print("Servo moved, angle- ");
	Serial.print(angle);
	Serial.print(", relative- ");
	Serial.print(relative);
	Serial.print(", inverse- ");
	Serial.print(_inverse);*/
};
void Servo::info(bool if_current){
	if(if_current){
	Serial.print(_angle);
	}
	else{
		Serial.print(EEPROM.read(_id));
	}
}
void Servo::SaveAnglesEEPROM(){
	if(_inverse){ //inversing againg to set values using inversing xD
		EEPROM.update(_id,180-_angle);
	}
	else{
		EEPROM.update(_id,_angle);
	}
	
};
void Servo::MoveInit(){
	MoveServo(EEPROM.read(_id),false);
};