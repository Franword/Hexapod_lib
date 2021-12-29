#include "Servo.h"
#include <Arduino.h>
Servo::Servo(){};
void Servo::Setup(uint8_t leg_num,uint8_t servo_num)
{
	switch (leg_num) {
		case R1:
			_pwm_num=false;
			_inverse=false;
			//Serial.print ("R1 ");
			if (servo_num==q1){
				_address=R1q1;}
			if (servo_num==q2){
				_address=R1q2;}
			if (servo_num==q3){
				_address=R1q3;}
		break;
		case R2:
			_pwm_num=true;
			_inverse=false;
			//Serial.print ("R2 ");
			if (servo_num==q1){
				_address=R2q1;}
			if (servo_num==q2){
				_address=R2q2;}
			if (servo_num==q3){
				_address=R2q3;}
		break;
		case R3:
			_pwm_num=true;
			_inverse=false;
			//Serial.print ("R3 ");
			if (servo_num==q1){
				_address=R3q1;}
			if (servo_num==q2){
				_address=R3q2;}
			if (servo_num==q3){
				_address=R3q3;}
		break;
		case L1:
			_pwm_num=false;
			_inverse=true;
			//Serial.print ("L1 ");
			if (servo_num==q1){
				_address=L1q1;}
			if (servo_num==q2){
				_address=L1q2;}
			if (servo_num==q3){
				_address=L1q3;}
		break;
		case L2:
			_pwm_num=false;
			_inverse=true;
			//Serial.print ("L2 ");
			if (servo_num==q1){
				_address=L2q1;}
			if (servo_num==q2){
				_address=L2q2;}
			if (servo_num==q3){
				_address=L2q3;}
		break;
		case L3:
			_pwm_num=true;
			_inverse=true;
			//Serial.print ("L3 ");
			if (servo_num==q1){
				_address=L3q1;}
			if (servo_num==q2){
				_address=L3q2;}
			if (servo_num==q3){
				_address=L3q3;}
	}
	_id=3*leg_num+servo_num;

	ReadOffset();
	MoveServo(90,false);
};
uint16_t Servo::MoveServo(uint8_t angle,bool relative)
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
			angle=180-angle-_offset;
		}
		else{
			angle=angle+_offset;
		}
	}
	if(angle<0){
		angle=0;
		Serial.println("ERROR: out of range");
	}
	if(angle>180){
		angle=180;
		Serial.println("ERROR: out of range");
	}
	_angle=angle;
	return map(angle, 0, 180, SERVOMIN,SERVOMAX);
	//Serial.println(_pulse);
};
void Servo::info(bool if_current){
	if(if_current){
		if(_inverse){
			Serial.print(180-(_angle+_offset));
		}
		else{
			Serial.print(_angle-_offset);
		}
	}
	else{
		Serial.print(_offset);
	}
};
void Servo::SetOffset(){
	if(_inverse){ //inversing againg to set values using inversing xD
		EEPROM.update(_id,128+(180-_angle)-90);
	}
	else{
		EEPROM.update(_id,128+_angle-90);
	}
};
void Servo::ReadOffset(){
	//return _pulse=MoveServo(EEPROM.read(_id),false);
	_offset =EEPROM.read(_id)-128;
	Serial.print(_offset);
};
bool Servo::get_pwm_num(){
	return _pwm_num;
};
uint8_t  Servo::get_pwm_address(){
	return _address;
};