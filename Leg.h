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
  private:
    Servo _Servo[3];
	int _leg_num;
};
#endif