#include<Arduino.h>
#include"pin.h"
#include"ultraSonicSensor.h"

ultraSonicSensor::ultraSonicSensor(int echoPin, int trigerPin){
	//インスタンスが作成されたらピン番号を定義しpinModeする
	echo = echoPin;
	triger = trigerPin;
	pinMode(echo,INPUT);
	pinMode(triger,OUTPUT);
}

double ultraSonicSensor::getDistance(){
	unsigned long duration = 0;
	double distance = 0;
	//trigピンにパルス出力
	digitalWrite(triger,LOW);
	delayMicroseconds(2);
	digitalWrite(triger,HIGH);
	delayMicroseconds(10);
	digitalWrite(triger,LOW);
	//反射した超音波がechoピンに検知されるまでの時間を計測
	duration=pulseIn(echo,HIGH);
	//計算して距離(cm)に変換
	distance=(duration*340*100)/2000000.0;
	return distance;
}
