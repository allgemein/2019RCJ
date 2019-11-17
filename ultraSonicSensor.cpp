#include<Arduino.h>
#include"pin.h"
#include"ultraSonicSensor.h"

ultraSonicSensor::ultraSonicSensor(int echoPin, int trigerPin){
	echo = echoPin;
	triger = trigerPin;
	pinMode(echo,INPUT);
	pinMode(triger,OUTPUT);
}

double ultraSonicSensor::getDistance(){
	unsigned long duration = 0;
	double distance = 0;
	digitalWrite(triger,LOW);
	delayMicroseconds(2);
	digitalWrite(triger,HIGH);
	delayMicroseconds(10);
	digitalWrite(triger,LOW);
	duration=pulseIn(echo,HIGH);
	distance=(duration*340*100)/2000000.0;
	return distance;
}
