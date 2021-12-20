#ifndef GAMEPAD_H
#define GAMEPAD_H
#if (ARDUINO>=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include <SPI.h>
class Gamepad{
    public:
    Gamepad();
    void setup();
    unsigned char Get_PS2Dat(unsigned char *buf);
    unsigned char PS2_RWByte(unsigned char dat);
    void loop();
    private:
    const int slaveSelectPin = 10;
    unsigned char PS2buf[10];
    unsigned char i;
};
#endif