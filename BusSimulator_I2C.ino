#include "Temperature.h"
#include "BusI2C.h"


#include <Wire.h>

BusI2C i2cPort(Wire1, true);
 
void setup() {
  Serial.begin(115200);
  Serial.println("\nI2C ADC");
  i2cPort.begin();
  if (i2cPort.errCode()) {
    // TODO TODO
    Serial.println("\nInitialization error");
  }
  
}

byte singleByteRead(byte addr) {
  byte error;
  Wire1.beginTransmission(ADC_I2C_ADDR);
  Wire1.write(addr);
  error = Wire1.endTransmission();
  if (error==4)
  {
    Serial.print("Unknown error at address 0x");
    Serial.println(ADC_I2C_ADDR,HEX);
  }

  int bytesRead = Wire1.requestFrom(ADC_I2C_ADDR, 1);
  uint8_t out = Wire1.read();
  
  return out;
}

int doubleByteRead(byte addr) {
  byte error;
  Wire1.beginTransmission(ADC_I2C_ADDR);
  Wire1.write(addr);
  error = Wire1.endTransmission();
  if (error==4)
  {
    Serial.print("Unknown error at address 0x");
    Serial.println(ADC_I2C_ADDR,HEX);
  }

  int bytesRead = Wire1.requestFrom(ADC_I2C_ADDR, 2);
  uint8_t out1 = Wire1.read();
  uint8_t out2 = Wire1.read();
  
  return ((uint16_t)out1<<4) | (out2 >> 4);
}

float read3v3() {
  return doubleByteRead(READ_3_3V_REG)/4096.*5;
}

float read5v() {
  return doubleByteRead(READ_5H_V_REG)/4096.*10.;
}

float read12v() {
  return doubleByteRead(READ_12Q_V_REG)/4096.*20.;
}

float readTemp() {
  uint16_t val = doubleByteRead(READ_TEMP_REG);
  val >>= 2;
  return Temperature::conv10bitTemp(val);
}

void loop() {

  Serial.println("Begin test...");

  i2cPort.sendByte(ONESHOT_REG, 0);
  Serial.println(read3v3());
  Serial.println(read5v());
  Serial.println(read12v());
  Serial.println(doubleByteRead(READ_TEMP_REG), HEX);
  Serial.println(readTemp());
  Serial.println(doubleByteRead(READ_3_3A_REG), HEX);
  Serial.println(doubleByteRead(READ_5H_A_REG), HEX);
  Serial.println(doubleByteRead(READ_12Q_A_REG), HEX);
 
  delay(100);           // wait 5 seconds for next scan
}

