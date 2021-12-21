#include "PWM.h"
PWM::PWM(){};
PWM::PWM(uint8_t address){
	_address=address;
	_pwm= Adafruit_PWMServoDriver();
	_pwm.begin();
	_pwm.setOscillatorFrequency(OSCILATOR_FREQ);
	_pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
	delay(10);
	//serial
	/*Serial.print("PWM created, adress- ");
	Serial.println(_address,HEX);*/
};
void PWM::SetPWM(int servo_address,int angle) //do edytowania bo nie wiem co robi to 0 xDD
{
	int min;
	int max;
	if(_address==0x40){
		switch (servo_address)
		{
		case R1q1:
			min=SERVOMIN_R1q1;
			max=SERVOMAX_R1q1;
			break;
		case R1q2:
			min=SERVOMIN_R1q2;
			max=SERVOMAX_R1q2;
			break;
		case R1q3:
			min=SERVOMIN_R1q3;
			max=SERVOMAX_R1q3;
			break;
		case L1q1:
			min=SERVOMIN_L1q1;
			max=SERVOMAX_L1q1;
			break;
		case L1q2:
			min=SERVOMIN_L1q2;
			max=SERVOMAX_L1q2;
			break;
		case L1q3:
			min=SERVOMIN_L1q3;
			max=SERVOMAX_L1q3;
			break;
		case L2q1:
			min=SERVOMIN_L2q1;
			max=SERVOMAX_L2q1;
			break;
		case L2q2:
			min=SERVOMIN_L2q2;
			max=SERVOMAX_L2q2;
			break;
		case L2q3:
			min=SERVOMIN_L2q3;
			max=SERVOMAX_L2q3;
			break;
		}
	}
	else if(_address==0x41){
			switch (servo_address)
		{
		case R2q2:
			min=SERVOMIN_R2q2;
			max=SERVOMAX_R2q2;
			break;
		case R2q3:
			min=SERVOMIN_R2q3;
			max=SERVOMAX_R2q3;
			break;
		case R3q1:
			min=SERVOMIN_R3q1;
			max=SERVOMAX_R3q1;
			break;
		case R3q2:
			min=SERVOMIN_R3q2;
			max=SERVOMAX_R3q2;
			break;
		case R3q3:
			min=SERVOMIN_R3q3;
			max=SERVOMAX_R3q3;
			break;
		case L3q1:
			min=SERVOMIN_L3q1;
			max=SERVOMAX_L3q1;
			break;
		case L3q2:
			min=SERVOMIN_L3q2;
			max=SERVOMAX_L3q2;
			break;
		case L3q3:
			min=SERVOMIN_L3q3;
			max=SERVOMAX_L3q3;
			break;
		}
	}
	//function
	int pulse =map(angle, 0, 180, min,max);
	_pwm.setPWM(servo_address,0,pulse);
	//serial
	Serial.print("PWM set, address- "); 
	Serial.print(servo_address);
	Serial.print(", pulse- ");
	Serial.println(pulse);
};