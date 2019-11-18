#pragma once
#include "pin.h"
#include "ultraSonicSensor.h"
#include "linetrace.h"
#include "DCMotorControl.h"
#include "right_angle_turn_Right.h"
#include "dodge_movement.h"
///左に壁が見つかるまで左にまわるプログラム
ultraSonicSensor usL(trigL,echoL);

void turn_left() ;