#pragma once
#include<Arduino.h>
#include"pin.h"
#include"DCMotorControl.h"
#include"ultraSonicSensor.h"
#include<Servo.h>

const int machine_size = 7; //constで定数扱いにする 機体の大きさ（半径）
const int sec = 40;
const int change_line = 5;

void localozation_wall(ultraSonicSensor usL);
void rescue_setup(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR);
void find_ball(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR);
void pic_up_ball();
void find_triangle_and_drop_ball ();
void rescue();
void move_to_wall(ultraSonicSensor usF);
