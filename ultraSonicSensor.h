#pragma once
#include"pin.h"

class ultraSonicSensor{
	private:
		int echo,triger;
	public:
		ultraSonicSensor(int echoPin, int trigerPin);
		double getDistance();
};
