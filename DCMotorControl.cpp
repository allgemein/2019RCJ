#include"pin.h"
#include<Arduino.h>
#include"DCMotorControl.h"

//モータを簡単に動かすための関数
void MOVE(int powerL, int powerR){

	//もし引数が想定範囲をオーバーしていたら255,-255に丸める
	if(powerL>255) powerL=255;
	if(powerL<-255) powerL=-255;
	if(powerR>255) powerR=255;
	if(powerR<-255)powerR=-255;

	//引数の正負に応じてモータ信号用ピンにPWM出力

	if(powerL>0){
		analogWrite(normalPinL,powerL);
		analogWrite(reversePinL,0);
	} 
	else{
		analogWrite(normalPinL,0);
		analogWrite(reversePinL,-powerL);
	}

	if(powerR>0){
		analogWrite(normalPinR,powerR);
		analogWrite(reversePinR,0);
	}
	else{
		analogWrite(normalPinR,0);
		analogWrite(reversePinR,-powerR);
	}
}
