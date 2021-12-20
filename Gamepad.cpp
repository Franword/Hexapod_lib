#include "Gamepad.h"
Gamepad::Gamepad(){};
void Gamepad::setup(){

  Serial.println("Gamepad inization...");  
  pinMode(slaveSelectPin,OUTPUT);
  digitalWrite(slaveSelectPin,HIGH);
  
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);                //LSBFIRST or MSBFIRST
  SPI.setDataMode(SPI_MODE3);               //CPOL=1 CPHA=1
  SPI.setClockDivider(SPI_CLOCK_DIV64);  //
  delay(20);
  Serial.println("Gamepad inizatin finished.");
};
unsigned char Gamepad::Get_PS2Dat(unsigned char *buf)
{
  unsigned char i;
  digitalWrite(slaveSelectPin,LOW);
  delayMicroseconds(15);
  buf[0]=PS2_RWByte(0x01);delayMicroseconds(15); 
  buf[1]=PS2_RWByte(0x42);delayMicroseconds(15); 
  buf[2]=PS2_RWByte(0x00);delayMicroseconds(15); 
  buf[3]=PS2_RWByte(0x00);delayMicroseconds(15); 
  buf[4]=PS2_RWByte(0x00);delayMicroseconds(15); 
  buf[5]=PS2_RWByte(0x00);delayMicroseconds(15); 
  buf[6]=PS2_RWByte(0x00);delayMicroseconds(15); 
  buf[7]=PS2_RWByte(0x00);delayMicroseconds(15); 
  buf[8]=PS2_RWByte(0x00);delayMicroseconds(15); 
  digitalWrite(slaveSelectPin,HIGH);
  if((buf[0]==0xff)&&(buf[1]==0x41)&&(buf[2]==0x5a))  
  return 1;
  if((buf[0]==0xff)&&(buf[1]==0x73)&&(buf[2]==0x5a))
  return 2;
  return 0;
};
unsigned char Gamepad::PS2_RWByte(unsigned char dat)
{
  SPI.transfer(dat);   
  //while(!(SPSR&0x80));
  return(SPDR);      
};
void Gamepad::loop(){
    if(Get_PS2Dat(PS2buf))
  for(i=0;i<9;i++)
  {
    Serial.print(PS2buf[i]);
  }
  Serial.println();
  delay(250);
};