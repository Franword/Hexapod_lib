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
  void info(bool);
  void SaveAnglesEEPROM();
  void MoveInit();
  bool if_leg_active(byte);
  void change_leg_pair();
  private:
	PWM _pwm[2];
	Leg _leg[6];
  //Servo _servo[6][3];
  bool _leg_pair;
};
#endif