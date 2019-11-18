#pragma once
#include<Arduino.h>
#include"pin.h"
#include"constant.h"
#include"DCMotorControl.h"

class lineTrace{
	private:
		int limen,basicMotorPower;
		double Kp,Ki,Kd;
		void turnToFindObstacle(ultraSonicSensor us,enum direction direction);

	public:
		lineTrace(int limen0,int basicMotorPower0,double Kp0,double Ki0,double Kd0);
		void pid();
		void onOff();
		enum phase judgePhase();
		void rightangleBasedOnLine(enum direction direction);
		void dodge_movement();
		void searchLine();
};
