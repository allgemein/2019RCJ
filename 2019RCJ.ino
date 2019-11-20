#include"pin.h"
#include"setup.h"
#include"ultraSonicSensor.h"
#include"lineTrace.h"
#include"constant.h"
#include"MPU9250.h"
#include"rescue.h"
#include"TCS34725.h"

void setup(){
	Serial.begin(9600);
	/*
	Wire.begin();
	i2cWireByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);
	i2cWireByte(MPU9250_ADDRESS, ACCEL_CONFIG, ACCEL_FS_SEL_16G);
	accRange = 16.0;
	i2cWireByte(MPU9250_ADDRESS, GYRO_CONFIG, GYRO_FS_SEL_2000DPS);
	gyroRange = 2000.0;
	i2cWireByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x02);
	i2cWireByte(AK8963_ADDRESS, CNTL1, CNTL1_MODE_SEL_100HZ);

	MPU9250set();
	*/
}

//超音波センサのインスタンス作成
ultraSonicSensor usR(echoR,trigR);
ultraSonicSensor usL(echoL,trigL);
ultraSonicSensor usF(echoF,trigF);

void loop(){
	//judgePhaseで判定した状況に応じて関数を実行
	switch (judgePhase(usF)){
		case startRescue:
			rescue();
			break;
		case rightangleR:
			Serial.println("rightangleR");
			rightangleBasedOnLine(R);
			break;
		case rightangleL:
			Serial.println("rightangleL");
			rightangleBasedOnLine(L);
			break;
		case passOver:
			Serial.println("passOver");
			passOverLine();
			break;
		case obstacle:
			Serial.println("obstacle");
			dodge_movement(usR,usF,usL);
			break;
		case white:
			Serial.println("white");
			searchLine();
			break;
		default:
			Serial.println("lineTrace");
			pid();
			break;
	}
} 
