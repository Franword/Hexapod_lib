#ifndef PWM_H
#define PWM_H
#if (ARDUINO>=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Adafruit_PWMServoDriver.h"
#include "PWM_values.h"
#include "Addresses.h"
class PWM
{
	public:
	PWM();
	PWM(uint8_t);
	void SetPWM(int, int);
	
	private:
	Adafruit_PWMServoDriver _pwm;
	uint8_t _address;
};
#endif