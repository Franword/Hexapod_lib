#include "Leg.h"
Leg::Leg(){};
Leg::Leg(int leg_num,PWM* PWM_wsk){
	//Serial.println("Creating Leg");
	_leg_num=leg_num;
	
	_Servo[q1]=Servo(leg_num,q1,PWM_wsk);
	_Servo[q2]=Servo(leg_num,q2,PWM_wsk);
	_Servo[q3]=Servo(leg_num,q3,PWM_wsk);
	//serial
	/*Serial.print("Leg number ");
	Serial.print(leg_num,DEC);
	Serial.println(" created\n");*/
};
void Leg::MoveLeg(int angle[3],bool relative){
	//Serial.println("\nLeg::MoveLeg");
	_Servo[q1].MoveServo(angle[q1],relative);
	_Servo[q2].MoveServo(angle[q2],relative);
	_Servo[q3].MoveServo(angle[q3],relative);
};
void Leg::MoveServo(int angle,bool relative, int servo_num){
	_Servo[servo_num].MoveServo(angle,relative);
};