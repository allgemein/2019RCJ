#include"pin.h"
#include<Arduino.h>
#include"DCMotorControl.h"

DCMotorControl::DCMotorControl(int normalPinL,int reversePinL, int normalPinR, int reversePinR){
	this->normalPinL = normalPinL;
	this->reversePinL = reversePinL;
	this->normalPinR = normalPinR;
	this->reversePinR = reversePinR;
}


void DCMotorControl::move(int powerL, int powerR){

	if(powerL>255) powerL=255;
	if(powerL<-255) powerL=-255;
	if(powerR>255) powerR=255;
	if(powerR<-255)powerR=-255;

	if(powerL>0){
		analogWrite(normalPinL,powerL);
		analogWrite(reversePinL,0);
	} 
	else{
		analogWrite(normalPinL,0);
		analogWrite(reversePinL,-powerL);
	}

	if(powerR>0){
		analogWrite(normalPinR,powerR);
		analogWrite(reversePinR,0);
	}
	else{
		analogWrite(normalPinR,0);
		analogWrite(reversePinR,-powerR);
	}
}
