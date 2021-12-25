#ifndef SERVO_H
#define SERVO_H
#include "Addresses.h"
#include <EEPROM.h>
#include "PWM_values.h"
class Servo
{
  public:
  Servo();
  Servo(uint8_t,uint8_t);
  int MoveServo(uint8_t,bool);
  void info(bool);
  void SaveAnglesEEPROM();
  int MoveInit();
  bool get_pwm_num();
  uint8_t get_pwm_address();
  private:
  uint8_t _angle;
  uint8_t _address;
  uint16_t _pulse;
  bool _pwm_num;
  bool _inverse;
  uint8_t _id;
};
#endif