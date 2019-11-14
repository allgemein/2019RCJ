#pragma once
#include<Arduino.h>
#include"pin.h"

class DCMotorControl{
	private:
		int normalPinL,reversePinL,normalPinR,reversePinR;
	public:
		DCMotorControl(int normalPinL,int reversePinL, int normalPinR, int reversePinR);
		void move(int powerL, int powerR);
};
