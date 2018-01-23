#include <stdint.h>

#ifndef BUSSIM_TEMPERATURE
#define BUSSIM_TEMPERATURE

class Temperature {
public:
  static const uint8_t temptable[1024];
  static float conv10bitTemp(uint16_t val);
};

#endif // BUSSIM_TEMPERATURE
