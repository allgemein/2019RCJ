#pragma once
#include<Arduino.h>
#include"pin.h"
#include"constant.h"
#include"DCMotorControl.h"
#include"ultraSonicSensor.h"

class lineTrace{
	private:
		int limen,basicMotorPower;
		double Kp,Ki,Kd;
		void turnToFindObstacle(ultraSonicSensor us,enum direction direction);
		void crossing();

	public:
		lineTrace(int limen0,int basicMotorPower0,double Kp0,double Ki0,double Kd0);
		void pid();
		enum phase judgePhase(ultraSonicSensor usF);
		void rightangleBasedOnLine(enum direction direction);
		void dodge_movement(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR);
		void searchLine();
};
