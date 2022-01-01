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
  void SetLegAngle(int[3],bool,uint8_t);
  void SetServoAngle(int,bool,uint8_t,uint8_t);
  void SetHexapodAngle(int[6][3],bool);
  void MoveServo(uint8_t,uint8_t);
  void MoveLeg(uint8_t);
  void info(bool);
  void ReadOffset();
  void SetOffset();
  bool if_leg_active(uint8_t);
  void change_leg_pair();
  void SetLegPos(int[3],uint8_t,bool);
  void dir_kin(int[3], uint8_t);
  void MoveHexapod();
  void SetHexapodPos(int[6][3],bool);
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