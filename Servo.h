#ifndef SERVO_H
#define SERVO_H
#include "Addresses.h"
#include <EEPROM.h>
#include "PWM_values.h"
class Servo
{
  public:
  Servo();
  void Setup(uint8_t,uint8_t);
  uint16_t MoveServo(uint8_t,bool);
  void info(bool);
  void SetOffset();
  void  ReadOffset();
  bool get_pwm_num();
  uint8_t get_pwm_address();

  private:
  uint8_t _angle;
  int8_t _offset;
  uint8_t _address;
  bool _pwm_num;
  bool _inverse;
  uint8_t _id;
};
#endif