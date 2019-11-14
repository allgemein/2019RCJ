#pragma once
#include"DCMotorControl.h"

class lineTrace{
	private:
		int limen,basicMotorPower;
		double Kp,Ki,Kd;
		DCMotorControl motor;
	public:
		lineTrace(int basicMotorPower,int limen,double Kp,double Ki,double Kd);
		void pid();
		void onOff();
};

