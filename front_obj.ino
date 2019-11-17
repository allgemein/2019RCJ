#include "pin.h"
#include "getDistance.h"
#include "linetrace.h"
///正面に障害物が来たら止まるプログラム
ultraSonicSensor usF(echoF,trigerF); //前の値を返すコマンドを指定する

void find_front_obj() {
  DisF = usF.getDistance();
  if(DisF <= 13 && DisF >= 7){
    turn_right_angle();
  }
}