/*#include"MPU9250.h"

void MPU9250set(){
  i2cRead(MPU9250_ADDRESS, 0x3b, 14, accGyroTempData);

  i2cRead(AK8963_ADDRESS, STl, 1, &STlBit);

  if((STlBit & 0x01)){
    i2cRead(AK8963_ADDRESS, 0x03, 7, magneticData);
  }
  
  axs = (accGyroTempData[0] <<8) | accGyroTempData[1];
  axs = (accGyroTempData[2] <<8) | accGyroTempData[3];
  axs = (accGyroTempData[4] <<8) | accGyroTempData[5];
  gxs = (accGyroTempData[8] <<8) | accGyroTempData[9];
  gys = (accGyroTempData[10] <<8) | accGyroTempData[11];
  gzs = (accGyroTempData[12] <<8) | accGyroTempData[13];

  tempMPU9250Raw = (accGyroTempData[6] <<8) | accGyroTempData[7];

  mxs = (magneticData[3] << 8) | magneticData[2];
  mys = (magneticData[1] << 8) | magneticData[0];
  mzs = -((magneticData[5] << 8) | magneticData[4]);

  accXs = axs * accRange / 32768.0;
  accYs = ays * accRange / 32768.0;
  accZs = azs * accRange / 32768.0;
  
  gyroXs = gxs * gyroRange / 32768.0;
  gyroYs = gys * gyroRange / 32768.0;
  gyroZs = gzs * gyroRange / 32768.0;

  tempMPU9250 = ((tempMPU9250Raw - 0.0) / 333.87) + 21.0f;

  magXs = mxs / 32768.0f * 4800.0f;
  magYs = mys / 32768.0f * 4800.0f;
  magZs = mzs / 32768.0f * 4800.0f;
}

void MPU9250(){
  i2cRead(MPU9250_ADDRESS, 0x3b, 14, accGyroTempData);

  i2cRead(AK8963_ADDRESS, STl, 1, &STlBit);

  if((STlBit & 0x01)){
    i2cRead(AK8963_ADDRESS, 0x03, 7, magneticData);
  }
  
  ax = (accGyroTempData[0] <<8) | accGyroTempData[1];
  ax = (accGyroTempData[2] <<8) | accGyroTempData[3];
  ax = (accGyroTempData[4] <<8) | accGyroTempData[5];
  gx = (accGyroTempData[8] <<8) | accGyroTempData[9];
  gy = (accGyroTempData[10] <<8) | accGyroTempData[11];
  gz = (accGyroTempData[12] <<8) | accGyroTempData[13];

  tempMPU9250Raw = (accGyroTempData[6] <<8) | accGyroTempData[7];

  mx = (magneticData[3] << 8) | magneticData[2];
  my = (magneticData[1] << 8) | magneticData[0];
  mz = -((magneticData[5] << 8) | magneticData[4]);

  accX = ax * accRange / 32768.0 - accXs;
  accY = ay * accRange / 32768.0 - accYs;
  accZ = az * accRange / 32768.0 - accZs;
  
  gyroX = gx * gyroRange / 32768.0 - gyroXs;
  gyroY = gy * gyroRange / 32768.0 - gyroYs;
  gyroZ = gz * gyroRange / 32768.0 - gyroZs;

  tempMPU9250 = ((tempMPU9250Raw - 0.0) / 333.87) + 21.0f;

  magX = mx / 32768.0f * 4800.0f - magXs;
  magY = my / 32768.0f * 4800.0f - magYs;
  magZ = mz / 32768.0f * 4800.0f - magZs;
}

void i2cRead(uint8_t Address, uint8_t Register, uint8_t NBytes, volatile uint8_t*Data){
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  Wire.requestFrom(Address, NBytes);
  uint8_t index = 0;
  while (Wire.available()) {
    Data[index++] = Wire.read();
  }
}

void i2cWireByte(uint8_t Address, uint8_t Register, volatile uint8_t Data){
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}
*/
