#ifndef SERVO_H
#define SERVO_H
#include "PWM.h"
#include "Addresses.h"
#include <EEPROM.h>
class Servo
{
  public:
  Servo();
  Servo(int,int,PWM*);
  void MoveServo(int,bool);
  void info(bool);
  void SaveAnglesEEPROM();
  void MoveInit();
  private:
  byte _angle;
  byte _address;
  bool _inverse;
  PWM* _PWM_wsk;
  byte _id;
};
#endif