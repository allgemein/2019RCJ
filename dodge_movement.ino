#include "pin.h"
#include "getDistance.h"
#include "linetrace.h"
#include "DCMotorControl.h"
#include "turn_left.ino"
///障害物の右側を回りながら前進するプログラム
ultraSonicSensor usL(trigL,echoL);

void dodge_movement() {
  DisL = usL.getDistance();
  while(DisL <= 13 && DisL >= 7; ){//左に壁があれば前に進む
    move(50,50);
    if(){ //ライン見つけたら実行
      break;
    }
  }
  turn_left();
}
