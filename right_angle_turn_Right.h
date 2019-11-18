#pragma once
#include "pin.h"
#include "ultraSonicSensor.h"
#include "linetrace.h"
#include "DCMotorControl.h"
#include "dodge_movement.h"
///右回りにだいたい90°になるまで回転させるプログラム
ultraSonicSensor usL(echoL,trigerL);

void turn_right_angle() ;