#include"pin.h"
#include"setup.h"
#include"ultraSonicSensor.h"
#include"lineTrace.h"
#include"constant.h"

void setup(){
	Serial.begin(9600);
}
//超音波センサのインスタンス作成
ultraSonicSensor usR(echoR,trigR);
ultraSonicSensor usL(echoL,trigL);
ultraSonicSensor usF(echoF,trigF);
//ライントレース用のインスタンス作成
lineTrace tracer(500,150,0.05,0.02,0.02);

void loop(){
	//judgePhaseで判定した状況に応じて関数を実行
	switch (tracer.judgePhase()){
		case rescue:
			tracer.rescue();
			break;
		case rightangleR:
			tracer.rightangle();
			break;
		case rightangleL:
			tracer.rightangle();
			break;
		case obstacle:
			tracer.obstacle();
			break;
		case white:
			tracer.searchLine();
			break;
		default:
			tracer.pid();
			break;
	}
} 
