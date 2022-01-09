#include "Hexapod.h"
//*******************Hexapod class*****************************************
Hexapod::Hexapod(){
}
void Hexapod::Setup(){
	Serial.println("Creating Hexapod");
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
	//serial
	for(uint8_t leg_num=0;leg_num<6;leg_num++){
		for(uint8_t servo_num=0;servo_num<3;servo_num++){
			SetServoAngle(90,false,leg_num,servo_num);
		}
	}
	Serial.println("Hexapod created\n");
};
//*********************************************************************************************************************************************
void Hexapod::SetServoAngle(int angle,bool relative,uint8_t leg_num,uint8_t servo_num){
	//function
	_pulse[leg_num][servo_num]=_servo[leg_num][servo_num].SetServoAngle(angle,relative);
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
};
void Hexapod::MoveServo(uint8_t leg_num,uint8_t servo_num){
	//if(leg_num==R1){	
	_pwm[_servo[leg_num][servo_num].get_pwm_num()].setPWM(_servo[leg_num][servo_num].get_pwm_address(),0, _pulse[leg_num][servo_num]);
	//}
};
//*********************************************************************************************************************************************
void Hexapod::SetLegAngle(int angle[3],bool relative,uint8_t leg_num){
	//function
	for(int servo_num=0;servo_num<3;servo_num++){
		_pulse[leg_num][servo_num]=_servo[leg_num][servo_num].SetServoAngle(angle[servo_num],relative);
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
};
void Hexapod::SetLegPos(int pos[3],uint8_t leg_num, bool relative){
	float d2;
	if(leg_num==R1 || leg_num==R2 || leg_num==R3){
		
		d2=-D2;
	}
	else{
		d2=D2;
	}
	int x, y, z;
	if(relative){
		x=pos[0]+_pos[leg_num][0];
		y=pos[1]+_pos[leg_num][1];
		z=pos[2]+_pos[leg_num][2];
	}
	_pos[leg_num][0]=x;
	_pos[leg_num][1]=y;
	_pos[leg_num][2]=z;
	float t1=2*atan2((x - sqrt(- pow(d2,2) + pow(x,2) + pow(y,2))),d2 - y);
	//int t3=int(degrees(acos(((pow(x*cos(t1) + y*sin(t1)-a1),2) + pow(z,2)  - pow(a2,2) - pow(a3,2))/(2*a2*a3)))); //to naprawic
	float t3= PI +acos((pow(a2,2)/2 + pow(a3,2)/2 - pow(z,2)/2 - pow((x*cos(q1) - a1 + y*sin(q1)),2)/2)/(a2*a3));
	float t2 = atan2(z , x*cos(t1) + y*sin(t1) - a1)  -  atan2( a3*sin(t3) , a2+a3*cos(t3));
	//int t2=0;
	//q2=atan2(pz , px*cos(q1) + py*sin(q1) - a1)  -  atan2( a2*sin(q3) , a2+a3*cos(q3) )
	int angle[3];
	angle[q1]=int(degrees(t1))%360;
	angle[q2]=int(degrees(t2))%360;
	angle[q3]=int(degrees(t3))%360;
		if(angle[q1]<-180){
		angle[q1]=-(360+angle[q1]);
	}
	if(angle[q1]>180){
		angle[q1]=-(360-angle[q1]);
	}
	
	Serial.print("t = [");
		Serial.print(angle[q1]);
		Serial.print(", ");
		Serial.print(angle[q2]);
		Serial.print(", ");
		Serial.print(angle[q3]);
		Serial.println("]");
	angle[q1]=90-angle[q1];
	angle[q2]=90-angle[q2];
	angle[q3]=angle[q3]-180;
	

  //function
	for(int servo_num=0;servo_num<3;servo_num++){
		_pulse[leg_num][servo_num]=_servo[leg_num][servo_num].SetServoAngle(angle[servo_num],false);
	}
	//serial
		print_leg_num(leg_num);
			Serial.print(" moved to [");
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
};
void Hexapod::dir_kin(int angle[3], uint8_t leg_num){
	float d2;
	float t1;
	if(leg_num==R1 || leg_num==R2 || leg_num==R3){
		t1=radians(float((90-angle[0])%360));
		d2=-D2;
	}
	else{
		t1=radians(float((angle[0]-90)%360));
		d2=D2;
	}
	//float t1=radians(float((90-angle[0])%360));
	float t2=radians(float((90-angle[1])%360));
	float t3=radians(float((180+angle[2])%360));

	_pos[leg_num][0] =int(a1*cos(t1) - a3*(cos(t1)*sin(t2)*sin(t3) - cos(t1)*cos(t2)*cos(t3)) + d2*sin(t1) + a2*cos(t1)*cos(t2));
	_pos[leg_num][1] =int(a1*sin(t1) - d2*cos(t1) - a3*(sin(t1)*sin(t2)*sin(t3) - cos(t2)*cos(t3)*sin(t1)) + a2*cos(t2)*sin(t1));
	_pos[leg_num][2] =int(a3*sin(t2 + t3) + a2*sin(t2));
};
void Hexapod::MoveLeg(uint8_t leg_num){
	for(int servo_num=0;servo_num<3;servo_num++){
		MoveServo(leg_num,servo_num);
	}
};
//*********************************************************************************************************************************************
void Hexapod::SetHexapodAngle(int angle[6][3],bool relative){
	int angles_to_update_pos[3];
	//function
	 for(byte leg_num=0; leg_num <=5;leg_num++){
		 //if(if_leg_active(leg_num)){
		for(int servo_num=0;servo_num<3;servo_num++){
			_pulse[leg_num][servo_num]=_servo[leg_num][servo_num].SetServoAngle(angle[leg_num][servo_num],relative);
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
			MoveServo(leg_num,servo_num);
		}
	}
};
void Hexapod::MoveHexapod(){
for(uint8_t leg_num=0;leg_num<6;leg_num++){
	for(uint8_t servo_num=0;servo_num<3;servo_num++){
		MoveServo(leg_num,servo_num);
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