#include<Arduino.h>
#include"pin.h"
#include"getDistance.h"

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
	dur=pulseIn(echo,HIGH);
	distance=(duration*340*100)/2000000;
	return distance;
}
