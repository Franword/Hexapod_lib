#include "print.h"
void print_servo_num(int servo_num){
	switch (servo_num){
		case q1:
		Serial.print("q1");
		break;
		case q2:
		Serial.print("q2");
		break;
		case q3:
		Serial.print("q3");
		break;
	}
}
void print_leg_num(int leg_num){
	switch (leg_num){
		case R1:
		Serial.print("R1");
		break;
		case R2:
		Serial.print("R2");
		break;
		case R3:
		Serial.print("R3");
		break;
		case L1:
		Serial.print("L1");
		break;
		case L2:
		Serial.print("L2");
		break;
		case L3:
		Serial.print("L3");
		break;
	}
}