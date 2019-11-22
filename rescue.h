#pragma once
#include <Arduino.h>
#include "pin.h"
#include "DCMotorControl.h"
#include "ultraSonicSensor.h"
#include <Servo.h>

const int machine_size = 7; //constで定数扱いにする 機体の大きさ（半径）

const int sec = 40000; //横断にかかりそうな秒数(ms)
const int change_line = 5000; //平行移動に使いそうな秒数(ms)

const int arm_servo_pin = 9; //アームの開閉に使うサーボのピン
const int lift_servo_pin = 10; //アームの昇降に使うサーボのピン

const int arm_open = 9; //アームが開いてる時のサーボの角度
const int arm_close = 9; //アームが閉じている時のサーボの角度

const int lift_up = 6; //アームが上がっている時のサーボの角度
const int lift_down = 6; //アームが下がっている時のサーボの角度

float DisL = 0;
float DisR = 0;

Servo arm_servo;

void localozation_wall(ultraSonicSensor usL);
void rescue_setup(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR);
void find_ball(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR);
void pic_up_ball();
void find_triangle_and_drop_ball ();
void rescue();
void move_to_wall(ultraSonicSensor usF);
