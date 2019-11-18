#pragma once
#include "pin.h"
#include "ultraSonicSensor.h"
#include "linetrace.h"
#include "DCMotorControl.h"
#include "turn_left.h"
#include "set_read_angle.h"
///障害物の右側を回りながら前進するプログラム
ultraSonicSensor usL(trigL,echoL);

void dodge_movement() ;