#include<Arduino.h>
#include"pin.h"
#include"setup.h"

void pinModeAll(){
	pinMode(trigR,OUTPUT);//超音波センサ用のデジタルピンのpinMode
	pinMode(trigL,OUTPUT);
	pinMode(echoR,INPUT);
	pinMode(echoL,INPUT);
}
