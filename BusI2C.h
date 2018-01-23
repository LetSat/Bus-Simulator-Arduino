#include <Wire.h>

#ifndef BUSSIM_BUSI2C
#define BUSSIM_BUSI2C

// Address and code definitions
#define ADC_I2C_ADDR 0x1D

#define ONESHOT_REG 0x09

#define CFG_REG 0x00
#define CFG_INIT 0x88
#define CFG_START 0x09
#define ADV_CFG_CONTENT 0x01 // Mode 0, Ext Ref
#define ADV_CFG_REG 0x0B
#define CONV_RATE_REG 0x07
#define CONV_RATE_MODE 0x01 // Continuous mode

#define READ_MANU_REG  0x3E
#define READ_REVI_REG  0x3F

#define READ_3_3V_REG  0x20
#define READ_5H_V_REG  0x21
#define READ_12Q_V_REG 0x22
#define READ_TEMP_REG  0x23
#define READ_3_3A_REG  0x24
#define READ_5H_A_REG  0x25
#define READ_12Q_A_REG 0x26

class BusI2C {
private:
  TwoWire i2cPort;
  bool debug;
  int error;
public:
  BusI2C(TwoWire i2cPort, bool debug);
  void begin();

  void sendByte(uint8_t addr, uint8_t data);

  int errCode();


};

#endif //BUSSIM_BUSI2C
