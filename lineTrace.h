#pragma once
#include<Arduino.h>
#include"pin.h"
#include"constant.h"
#include"DCMotorControl.h"
#include"ultraSonicSensor.h"
#include"TCS34725.h"

const int limen = 0;
const int basicMotorPower = 0;
const double Kp = 0;
const double Ki = 0;
const double Kd = 0;

void turnToFindObstacle(ultraSonicSensor us,enum direction direction);
void pid();
enum phase judgePhase(ultraSonicSensor usF);
void rightangleBasedOnLine(enum direction direction);
void dodge_movement(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR);
void searchLine();
void passOverLine();
bool moveUntilLineFound(enum direction direction,int delayTime);
