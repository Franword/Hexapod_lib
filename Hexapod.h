#ifndef HEXAPOD_H
#define HEXAPOD_H
//#include "Leg.h"
#include "Servo.h"
#include "Adafruit_PWMServoDriver.h"
#include "print.h"
#include "PWM_values.h"
#include "Addresses.h"
//#include <Kinematics.h>
class Hexapod
{
  public:
  Hexapod();
  void Setup();
  void MoveLeg(int[3],bool,uint8_t);
  void MoveServo(int,bool,uint8_t,uint8_t);
  void MoveHexapod(int[6][3],bool);
  void Move(uint8_t,uint8_t);
  void MoveL(uint8_t);
  void info(bool);
  void ReadOffset();
  void SetOffset();
  bool if_leg_active(uint8_t);
  void change_leg_pair();
  void inv_kin(int,int,int,uint8_t,bool);
  void dir_kin(int[3], uint8_t);
  private:
	//PWM _pwm[2];
  Adafruit_PWMServoDriver _pwm[2];
  Servo _servo[6][3];
  int _pos[6][3];
  bool _leg_pair;
  uint16_t _pulse[6][3];
  const int a2=80;
  const int a3=150;
  //Kinematics _kin;
};
#endif