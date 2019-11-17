#include"pin.h"
#include"setup.h"
#include"ultraSonicSensor.h"
#include"lineTrace.h"
#include"constant.h"
void setup(){
	Serial.begin(9600);
}

ultraSonicSensor usR(echoR,trigR);
ultraSonicSensor usL(echoL,trigL);
ultraSonicSensor usF(echoF,trigF);
lineTrace tracer(500,150,0.05,0.02,0.02);

void loop(){
	switch (judgePhase()){
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

