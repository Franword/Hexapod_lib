#ifndef SERVO_H
#define SERVO_H
#include "PWM.h"
#include "Addresses.h"
class Servo
{
  public:
  Servo();
  Servo(int,int,PWM*);
  void MoveServo(int,bool);
  void info();
  private:
  int _angle;
  int _address;
  bool _inverse;
  PWM* _PWM_wsk;
};
#endif