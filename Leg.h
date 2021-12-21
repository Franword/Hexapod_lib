#ifndef LEG_H
#define LEG_H
#include "Servo.h"
class Leg
{
  public:
  Leg();
  Leg(int, PWM*);
  void MoveLeg(int[3],bool);
  void MoveServo(int,bool,int);
  void info(bool);
  void SaveAnglesEEPROM();
  void MoveInit();
  private:
    Servo _Servo[3];
	byte _leg_num;
};
#endif