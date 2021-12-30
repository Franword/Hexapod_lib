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
	_kin=Kinematics(80, 150);
	//serial
	Serial.println("Hexapod created\n");
};
void Hexapod::MoveServo(int angle,bool relative,uint8_t leg_num,uint8_t servo_num){
	//function
	_pulse[leg_num][servo_num]=_servo[leg_num][servo_num].MoveServo(angle,relative);
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
		for(int servo_num=0;servo_num<3;servo_num++){
		Move(leg_num,servo_num);
		}
};
void Hexapod::MoveHexapod(int angle[6][3],bool relative){
	//function
	 for(byte leg_num=0; leg_num <=5;leg_num++){
		 //if(if_leg_active(leg_num)){
		for(int servo_num=0;servo_num<3;servo_num++){
			_pulse[leg_num][servo_num]=_servo[leg_num][servo_num].MoveServo(angle[leg_num][servo_num],relative);
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
		Serial.print(" [");
		for(int servo_num=0;servo_num<3;servo_num++){
			_servo[leg_num][servo_num].info(if_current);
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
	//if(!(leg_num==R3 && servo_num ==q3)){
	if(leg_num==R1){	
	_pwm[_servo[leg_num][servo_num].get_pwm_num()].setPWM(_servo[leg_num][servo_num].get_pwm_address(),0, _pulse[leg_num][servo_num]);
	}
};
void Hexapod::inv_kin(int x, int y, int z,uint8_t leg_num){
	_kin.moveToPosition(x,y,z);
	Angle a;
	int angle[3];
	a = _kin.getAngles();
	_kin.printAngles();
  if(leg_num==0 || leg_num==1 ||leg_num ==2){
    angle[0]=90+int(a.theta3);
  }
  else{
    angle[0]=90-int(a.theta3);
  }
  angle[1]=90-int(a.theta1);
  angle[2]=180+int(a.theta2);

  MoveLeg(angle,false,leg_num);
};