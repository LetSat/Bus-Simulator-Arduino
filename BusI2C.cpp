#include "BusI2C.h"

BusI2C::BusI2C(TwoWire i2cPort, bool debug) : 
      i2cPort(i2cPort), 
      debug(debug),
      error(0) {
  
}

void BusI2C::sendByte(uint8_t addr, uint8_t data) {
  byte error;
  Wire1.beginTransmission(ADC_I2C_ADDR);
  Wire1.write(addr);
  Wire1.write(data);
  error = Wire1.endTransmission();
  if (error==4)
  {
    Serial.print("Unknown error at address 0x");
    Serial.println(ADC_I2C_ADDR,HEX);
  }
}

void BusI2C::begin() {
  Wire1.begin();
 
  if (debug) Serial.println("Resetting");
  sendByte(CFG_REG, CFG_INIT);
  if (debug) Serial.println("Enabling external reference");
  sendByte(ADV_CFG_REG, ADV_CFG_CONTENT);
  if (debug) Serial.println("Setting continuous mode");
  sendByte(CONV_RATE_REG, CONV_RATE_MODE);
  if (debug) Serial.println("Starting device");
  sendByte(CFG_REG, CFG_START);
}

int BusI2C::errCode() {
  return BusI2C::error;
}

