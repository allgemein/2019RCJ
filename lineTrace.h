#pragma once
#include<Arduino.h>
#include"pin.h"
#include"constant.h"
#include"DCMotorControl.h"

class lineTrace{
	private:
		int limen,basicMotorPower;
		double Kp,Ki,Kd;
	public:
		lineTrace(int limen,int basicMotorPower,double Kp,double Ki,double Kd);
		void pid();
		void onOff();
		enum phase judgePhase();
		void rightangle();
		void obstacle();
		void searchLine();
};
