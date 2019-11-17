#include<Arduino.h>
#include"pin.h"
#include"DCMotorControl.h"
#include"lineTrace.h"
#include"constant.h"

lineTrace::lineTrace(int limen,int basicMotorPower,double Kp,double Ki,double Kd){
	this->limen = limen;
	this->basicMotorPower = basicMotorPower;;
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
}

void lineTrace::pid(){
	int diff,propotial,integral,differential,Lpower,Rpower;
	char str[254];
	static int previous_diff = 0;
	static int previous_diff2 = 0;

	diff = analogRead(phtLr)-analogRead(phtRl);

	propotial = Kp*(diff-previous_diff);
	integral = Ki*diff;
	differential = Kd*((diff-previous_diff)-(previous_diff-previous_diff2));

	Lpower = basicMotorPower+(propotial+integral+differential);
	Rpower = basicMotorPower-(propotial+integral+differential);

	previous_diff2 = previous_diff;
	previous_diff = diff;

	sprintf(str,"power: %4d%4d",Lpower,Rpower);

	Serial.println(str);
	
	delay(5);
}
