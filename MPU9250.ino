 #include <Wire.h>

#define MPU9250_ADDRESS 0x68
#define PWR_MGMT_1 0x6b
#define INT_PIN_CFG 0x37

#define ACCEL_CONFIG 0x1c
#define ACCEL_FS_SEL_2G 0x00
#define ACCEL_FS_SEL_4G 0x08
#define ACCEL_FS_SEL_8G 0x10
#define ACCEL_FS_SEL_16G 0x18

#define GYRO_CONFIG 0x1b
#define GYRO_FS_SEL_250DPS 0x00
#define GYRO_FS_SEL_500DPS 0x08
#define GYRO_FS_SEL_1000DPS 0x10
#define GYRO_FS_SEL_2000DPS 0x18

#define AK8963_ADDRESS 0x0c
#define CNTL1 0x0a
#define CNTL1_MODE_SEL_8HZ 0x12
#define CNTL1_MODE_SEL_100HZ 0x16
#define STl 0x02


volatile float accRange;
volatile float gyroRange;

volatile uint8_t accGyroTempData[14];
volatile uint8_t magneticData[7];
volatile uint8_t STlBit;

volatile int16_t ax = 0;
volatile int16_t ay = 0;
volatile int16_t az = 0;

volatile int16_t axs = 0;
volatile int16_t ays = 0;
volatile int16_t azs = 0;

volatile int16_t gx = 0;
volatile int16_t gy = 0;
volatile int16_t gz = 0;

volatile int16_t gxs = 0;
volatile int16_t gys = 0;
volatile int16_t gzs = 0;

volatile int16_t tempMPU9250Raw = 0;

volatile int16_t mx = 0;
volatile int16_t my = 0;
volatile int16_t mz = 0;

volatile int16_t mxs = 0;
volatile int16_t mys = 0;
volatile int16_t mzs = 0;

volatile float accX =0;
volatile float accY =0;
volatile float accZ =0;

volatile float accXs =0;
volatile float accYs =0;
volatile float accZs =0;

volatile float gyroX =0;
volatile float gyroY =0;
volatile float gyroZ =0;

volatile float gyroXs =0;
volatile float gyroYs =0;
volatile float gyroZs =0;

volatile float tempMPU9250 = 0;

volatile float magX =0;
volatile float magY =0;
volatile float magZ =0;

volatile float magXs =0;
volatile float magYs =0;
volatile float magZs =0;


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

  i2cWireByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);
  i2cWireByte(MPU9250_ADDRESS, ACCEL_CONFIG, ACCEL_FS_SEL_16G);
  accRange = 16.0;
  i2cWireByte(MPU9250_ADDRESS, GYRO_CONFIG, GYRO_FS_SEL_2000DPS);
  gyroRange = 2000.0;
  i2cWireByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x02);
  i2cWireByte(AK8963_ADDRESS, CNTL1, CNTL1_MODE_SEL_100HZ);

  MPU9250set();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  MPU9250();

  Serial.print("ax: ");
  Serial.print(accX);
  Serial.print("\t");
  
  Serial.print("ay: ");
  Serial.print(accY);
  Serial.print("\t");
  
  Serial.print("az: ");
  Serial.print(accZ);
  Serial.print("\t");

  
  Serial.print("gx: ");
  Serial.print(gyroX);
  Serial.print("\t");
  
  Serial.print("gy: ");
  Serial.print(gyroY);
  Serial.print("\t");
  
  Serial.print("gz: ");
  Serial.print(gyroZ);
  Serial.print("\t");

  
  Serial.print("mx: ");
  Serial.print(magX);
  Serial.print("\t");
  
  Serial.print("my: ");
  Serial.print(magY);
  Serial.print("\t");
  
  Serial.print("mz: ");
  Serial.print(magZ);
  Serial.print("\t");

  Serial.print("temp: ");
  Serial.print(tempMPU9250);
  Serial.println("\t");
}


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