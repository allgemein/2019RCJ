#pragma onece
#include"pin.h"

class ultraSonicSensor{
	private:
		int echo,triger;
	public:
		ultraSonicSensor(int echoPin, int trigerPin);
		float getDistance();
};
