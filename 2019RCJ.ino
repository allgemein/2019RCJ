#include"pin.h"
#include"setup.h"
#include"DCMotorControl.h"

void setup(){
	Serial.begin(9600);
	pinModeAll();
}

DCMotorControl mymotor(motorL1,motorL2,motorR1,motorR2);

void loop(){
	mymotor.move(255,255);
	} 

















