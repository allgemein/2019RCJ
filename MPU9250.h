#pragma once
/*
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

void MPU9250set();
void MPU9250();
void i2cRead(uint8_t Address, uint8_t Register, uint8_t NBytes, volatile uint8_t*Data);
void i2cWireByte(uint8_t Address, uint8_t Register, volatile uint8_t Data);
*/
