#include"pin.h"
#include"setup.h"
#include"ultraSonicSensor.h"
#include"lineTrace.h"
#include"constant.h"
#include"MPU9250.h"
#include"rescue.h"
#include"TCS34725.h"

void debug_pht(){//フォトリフレクタの読み取り値をシリアルモニタに表示する関数
	char str[124];

	int valLl = analogRead(phtLl);
	int valLr = analogRead(phtLr);
	int valC = analogRead(phtC);
	int valRl = analogRead(phtRl);
	int valRr = analogRead(phtRr);

	sprintf(str,"  pht: %4d%4d%4d%4d%4d",valLl,valLr,valC,valRl,valRr);
	Serial.println(str);

}

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
	setUpServo();

}

//超音波センサのインスタンス作成
ultraSonicSensor usR(echoR,trigR);
ultraSonicSensor usL(echoL,trigL);
ultraSonicSensor usF(echoF,trigF);

void loop(){
	//judgePhaseで判定した状況に応じて関数を実行
	switch (judgePhase(usF)){
		//case startRescue:
		//	rescue();
		//	break;
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
		//case obstacle:
		//	Serial.println("obstacle");
		//	dodge_movement(usR,usF,usL);
		//	break;
		case white:
			Serial.println("white");
			searchLine();
			break;
		default:
			Serial.println("lineTrace");
			pid();
			break;
	}
	//debug_pht();
} 
