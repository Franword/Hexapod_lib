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
	//function
	_pwm.setPWM(servo_address,0,angle);
	//serial
	Serial.print("PWM set, address- "); 
	Serial.print(servo_address);
	Serial.print(", angle- ");
	Serial.println(angle);
};