#ifndef HEXAPOD_H
#define HEXAPOD_H
#include "Servo.h"
#include "Adafruit_PWMServoDriver.h"
#include "print.h"
#include "PWM_values.h"
#include "Addresses.h"
#include "ZDH_par.h"
class Hexapod
{
  public:
  Hexapod();
  void Setup();
  void SetLegAngle(float[3],bool,uint8_t);
  void SetServoAngle(float,bool,uint8_t,uint8_t);
  void SetHexapodAngle(float[6][3],bool);
  void MoveServo(uint8_t,uint8_t);
  void MoveLeg(uint8_t);
  void info(bool);
  void ReadOffset();
  void SetOffset();
  bool if_leg_active(uint8_t);
  void change_leg_pair();
  void SetLegPos(float[3],uint8_t,bool);
  void dir_kin(float[3], uint8_t);
  void MoveHexapod();
  void SetLegFromTrace(uint8_t, uint8_t);
  void trace(int16_t,uint16_t,uint8_t,int);
  void walk(int16_t,uint16_t,uint8_t,uint8_t, int,int);
  void step(uint8_t, int);
  void SetInit();
  private:
  Adafruit_PWMServoDriver _pwm[2];
  Servo _servo[6][3];
  float _pos[6][3];
  float _trace[30][3];
  bool _leg_pair;
  uint16_t _pulse[6][3];
  float _angle_rotz[6];
  int _ilosc_without_line;
  float _init_pos[3];
};
#endif

