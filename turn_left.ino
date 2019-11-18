#include "pin.h"
#include "getDistance.h"
#include "linetrace.h"
#include "DCMotorControl.h"
#include "right_angle_turn_Right.ino"
#include "dodge_movement"
///左に壁が見つかるまで左にまわるプログラム
ultraSonicSensor usL(trigL,echoL);

void turn_left() {
  DisL = usL.getDistance();
  while(DisL > 13 || DisL < 7; ){//左に壁なければ左旋回
    move(-50,50);
  }
  dodge_movement();
}