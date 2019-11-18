#include "pin.h"
#include "getDistance.h"
#include "linetrace.h"
#include "DCMotorControl.h"
#include "dodge_movement.ino"
///右回りにだいたい90°になるまで回転させるプログラム
ultraSonicSensor usL(echoL,trigerL);

void turn_right_angle() {
  DisL = usL.getDistance();
  while(DisL > 13 || DisL < 7){
  move(50, -50);
  }
  dodge_movement();
}