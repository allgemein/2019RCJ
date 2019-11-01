#include "define.h"
#include"pin.h"
#include"prototype.h"

void MOVE(int Lpower,int Rpower){//モータ出力を都合よく行うための関数

	if(Lpower>255) Lpower=255;
	if(Lpower<-255) Lpower=-255;
	if(Rpower>255) Rpower=255;
	if(Rpower<-255)Rpower=-255;

	if(Lpower>0){
		analogWrite(motorL1,Lpower);
		analogWrite(motorL2,0);
	}
	else{
		analogWrite(motorL1,0);
		analogWrite(motorL2,-Lpower);
	}

	if(Rpower>0){
		analogWrite(motorR1,Rpower);
		analogWrite(motorR2,0);
	}
	else{
		analogWrite(motorR1,0);
		analogWrite(motorR2,-Rpower);
	}

}

void brake(){//モータのブレーキ関数。慣性で回り続けるのが気になるときに
	analogWrite(motorL1,255);
	analogWrite(motorL2,255);
	analogWrite(motorR1,255);
	analogWrite(motorR2,255);
	delay(50);
}

void rightangle(int position){//直角処理関数。turnとの違いは十字路が想定されないこと
//	if(analogRead(phtC)<limen){
//		crossing();
	
//	}else{

		while(analogRead(phtC)>limenC){//中央のフォトリフレクタが黒になるまで

			if(position==R_position){//右に回り続ける
				MOVE(255,-255);
			}else{//左に回り続ける
				MOVE(-255,255);
			}

			delay(5);
			Serial.println("rightangle");

//		}
	}
}
void turn(int position){//交差点処理で用いる直角・Uターン関数
	int power=255;

	switch(position){//十字路の先を読み取ることによる誤作動を避けるためにいずれの場合も適切な方向に一定時間回転する:w
		case R_position:
			MOVE(power,-power);
			delay(250);
			break;

		case L_position:
			power=-power;
			MOVE(power,-power);
			delay(250);
			break;

		case Uturn:
			MOVE(power,-power);
			delay(250);

			while(analogRead(phtC)>limenC){//Uターンの際には二度黒い線を通過することが想定されるので、先に一度直角処理を行っておく
				MOVE(power,-power);
				delay(5);
			}	
			break;

		default://万一想定外の値が入った際に動かないようpowerに0を代入する
			power=0;
			break;
	}

	while(analogRead(phtC)>limenC){//中央のフォトリフレクタが黒になるまで回転を続ける
		MOVE(power,-power);
		delay(5);
	}
}

void obstacle(){
	Serial.println("obstacle");
	brake();
	MOVE(255,-255);
	delay(rightangletime);
	MOVE(255,255);
	delay(500);
	MOVE(-255,255);
	delay(rightangletime);
	MOVE(255,255);
	delay(750);
	MOVE(-255,255);
	delay(rightangletime);
	MOVE(255,255);
	delay(750);
	turn(R_position);
}
