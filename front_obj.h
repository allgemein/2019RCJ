#pragma once
#include "pin.h"
#include "ultraSonicSensor.h"
#include "linetrace.h"
#include "right_angle_turn_Right.h"
///正面に障害物が来たら止まるプログラム
ultraSonicSensor usF(echoF,trigerF); //前の値を返すコマンドを指定する

void find_front_obj() ;