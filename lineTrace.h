#pragma once
#include<Arduino.h>
#include"pin.h"
#include"constant.h"
#include"DCMotorControl.h"
#include"ultraSonicSensor.h"
#include"TCS34725.h"

const int limen = 300\

;
const int basicMotorPower = 80;
const double Kp = 0.25;
const double Ki = 0.05;
const double Kd = 0.1;

//引数にとった超音波センサが障害物を見つけるまで引数にとった方向へ旋回する関数
void turnToFindObstacle(ultraSonicSensor us,enum direction direction);
//pid制御でライントレースを行う関数
void pid();
//いま機体が交差点や障害物などどのような状況にあるのかを判定してphaseを返す関数
enum phase judgePhase(ultraSonicSensor usF);//直角に交差した線上で、次に中央のフォトリフレクタが黒い線を検知するまで指定した方向に旋回する関数
void rightangleBasedOnLine(enum direction direction);
//障害物があったときに回避動作を行う関数s
void dodge_movement(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR);
//黒い線を完全に見失ったとき、見つかるまで探索する関数
void searchLine();
//黒い線の上に乗った状況のとき、通り過ぎるまで前進する関数
void passOverLine();
//黒い線が見つかるかdelayTime秒経つまでdirection方向に旋回する関数
bool moveUntilLineFound(enum direction direction,int delayTime);
