#include "define.h"
#include"pin.h"
#include"prototype.h"
#include"MsTimer2.h"

void setup(){
	Serial.begin(9600);//シリアル通信を開始。速度は要求されないので9600でいいだろう
	digitalpins_pinMode();

	MsTimer2::set(250,debug_pht);

}

static int limen,limenC;

void loop(){

	//デバッグ用関数たち。使いたいときはwhileの条件式をtrue(=1)にすればよい

	while(0){
		Serial.println(judge_green3());
		delay(50);
	}
	while(0){
		debug_pht();
		delay(150);
	}
	while(0){
		debug_color();
		delay(100);
	}
	while(0){
		MOVE(255,-255);
		delay(3000);
		MOVE(-255,255);
		delay(3000);
		MOVE(255,0);
		delay(3000);
		MOVE(0,255);
		delay(3000);
	}
	while(0){
		Serial.print(digitalRead(bumperL));
		Serial.println(digitalRead(bumperR));
		delay(100);
	}


	int phase=judge_phase();//今何をするべきかを判断してphaseに値を代入する。下のswitchcase文の分岐に使う
	int array_limen[2];

	set_limen(array_limen);
	limen = array_limen[0]+50;
	limenC = array_limen[1]+50;

	//debug_pht();

	switch(phase){//judge_phaseで決定したフェーズに移行する
		/*case case_rescue:
		  rescue();
		  break;

		
		case case_crossing:
			crossing();
			break;
*/
		case case_white:
			Serial.println("white");
			white();
			break;

		case case_Rrightangle:
			rightangle(R_position);
			break;

		case case_Lrightangle:
			rightangle(L_position);
			break;

		//case case_obstacle:
		//	obstacle();
		//	break;


		default: 
			linetrace();
			break;

	}
}
