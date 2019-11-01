#include"define.h"
#include"pin.h"
#include"prototype.h"

void crossing(){//交差点処理関数

	int num_green = 0;	

	MOVE(100,100);
	delay(1000);

	if(analogRead(phtLl)<limen && (analogRead(phtLr)<limen || phtRl<limen) && analogRead(phtRr)<limen){

		while(analogRead(phtLl)<limen && (analogRead(phtLr)<limen || phtRl<limen) && analogRead(phtRr)<limen){
			MOVE(255,255);
			delay(10);
		}

	}else{
		MOVE(-150,-150);
		delay(1500);

		while(1){
			num_green = judge_green3();
			if(analogRead(phtLl)<limen && (analogRead(phtLr)<limen || phtRl<limen) && analogRead(phtRr)<limen) break;
			if(num_green!=0) break;
			linetrace();
		}

		if(num_green==R_position){
			turn(R_position);
		}//右のみ緑の場合右折

		else if(num_green==L_position){
			turn(L_position);
		}//左のみ緑の場合左折

		else if(num_green==2){
			turn(Uturn);
		}//左右ともに緑の場合Uターン

		else{
			MOVE(150,150);
			delay(1000);
		}
	}
}
