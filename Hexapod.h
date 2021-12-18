#ifndef HEXAPOD_H
#define HEXAPOD_H
#include "Leg.h"
#include "print.h"
class Hexapod
{
  public:
  Hexapod();
  void MoveLeg(int[3],bool,int);
  void MoveServo(int,bool,int,int);
  void MoveHexapod(int[6][3],bool);
  private:
	
    PWM _pwm[2];
	Leg _leg[6];
};
#endif