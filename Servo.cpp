#include "Servo.h"
#include <Arduino.h>
Servo::Servo(){};
void Servo::Setup(uint8_t leg_num,uint8_t servo_num)
{
	//_offset=0;
	//converts leg number and servo number to pwm address and pwm number
	//Serial.print("Servo ");
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
	MoveInit();
	//serial
	/*Serial.print(" q");
	Serial.print(servo_num,DEC);
	Serial.print(" created");
	Serial.print(", adress- ");
	Serial.print(_address,DEC);
	Serial.print(", inverse- ");
	Serial.println(_inverse,DEC);*/
};
int Servo::MoveServo(uint8_t angle,bool relative)
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
	//_PWM_wsk->SetPWM(_address, angle);
	/*_angle=angle;
	Serial.print("angle ");
	Serial.print(angle);
	Serial.print(" ---> pulse ");*/
	_angle=angle;
	_pulse=map(angle, 0, 180, SERVOMIN,SERVOMAX);
	//Serial.println(_pulse);
	return _pulse;

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
		if(_inverse){
			Serial.print(180-(_angle+_offset));
		}
		else{
			Serial.print(_angle-_offset);
		}
	}
	else{
		Serial.print(EEPROM.read(_id));
	}
};
void Servo::SaveAnglesEEPROM(){
	if(_inverse){ //inversing againg to set values using inversing xD
		EEPROM.update(_id,180-_angle);
	}
	else{
		EEPROM.update(_id,_angle);
	}
};
void Servo::SetOffset(){
	if(_inverse){ //inversing againg to set values using inversing xD
		EEPROM.update(18+_id,180-_angle);
	}
	else{
		EEPROM.update(18+_id,_angle);
	}
};
int Servo::MoveInit(){
	//return _pulse=MoveServo(EEPROM.read(_id),false);
	_offset = EEPROM.read(18+_id)-90;

	if(_inverse){
			_angle=90-_offset;
		}
		else{
			_angle=90+_offset;
		}
	 return _pulse=map(_angle, 0, 180, SERVOMIN,SERVOMAX);
};
bool Servo::get_pwm_num(){
	return _pwm_num;
};
uint8_t  Servo::get_pwm_address(){
	return _address;
};