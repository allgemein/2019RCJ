#include"lineTrace.h"

void lineTrace::turnToFindObstacle(ultraSonicSensor us,enum direction direction){
	double Dis = us.getDistance();
	while(Dis > 13 || Dis < 7){
		switch(direction){
			case R:
				MOVE(50, -50);
				break;
			case L:
				MOVE(-50,50);
				break;
		}
		delay(5);
		Dis = us.getDistance();
	}
}

void lineTrace::dodge_movement(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR){

	turnToFindObstacle(usL,R);

	while(!(analogRead(phtRl)<limen && analogRead(phtLr)<limen)){
		double disL = usL.getDistance();
		if(disL<=13 && disL>=7){
			MOVE(50,50);
			delay(5);
		}else{
			turnToFindObstacle(usL,L);
		}
	}

	while(analogRead(phtRl)<limen && analogRead(phtLr)<limen){
		MOVE(50,50);
		delay(5);
	}

	rightangleBasedOnLine(R);

}

//コンストラクタの定義
lineTrace::lineTrace(int limen0,int basicMotorPower0,double Kp0,double Ki0,double Kd0):limen(limen0),basicMotorPower(basicMotorPower0),Kp(Kp0),Ki(Ki0),Kd(Kd0){
}

/*pid制御によるライントレース関数
 * ラインを挟んだ二つのフォトリフレクタの読み取り値同士の差が0であるときをラインが機体中央にあるときと想定し、差(diff)=0を目標値としてpid制御を行う*/

void lineTrace::pid(){
	int diff,propotial,integral,differential,Lpower,Rpower;
	char str[254];
	static int previous_diff = 0;
	static int previous_diff2 = 0;

	//左右のセンサ値の差を取る
	diff = analogRead(phtLr)-analogRead(phtRl);

	//目標値との偏差にゲインをかける(比例項)
	propotial = Kp*diff;
	//今回の偏差と前回の偏差との差にゲインをかける(積分項)
	integral = Ki*(diff-previous_diff);
	//今回の偏差-前回の偏差から前回の偏差-前々回の偏差を引き(変化がどのくらい急か?)、その値にゲインをかける(微分項)
	differential = Kd*((diff-previous_diff)-(previous_diff-previous_diff2));

	//上の三項をまとめた上で前進するために多少の値(basicMotorPower)を加える
	Lpower = basicMotorPower+(propotial+integral+differential);
	Rpower = basicMotorPower-(propotial+integral+differential);

	//上で計算した値をモータに出力
	MOVE(Lpower,Rpower);

	//今回の偏差を前回の偏差を格納する変数へ、前回の偏差を前々回の偏差を格納する変数へ、それぞれ移す
	previous_diff2 = previous_diff;
	previous_diff = diff;

	//出力値を表示
	sprintf(str,"power: %4d%4d",Lpower,Rpower);

	Serial.println(str);

	delay(5);
}

enum phase lineTrace::judgePhase(ultraSonicSensor usF){

	int valLl = analogRead(phtLl);
	int valLr = analogRead(phtLr);
	int valC = analogRead(phtC);
	int valRl = analogRead(phtRl);
	int valRr = analogRead(phtRr);
	double Dis = usF.getDistance();

	if((valLl<limen && valLr<limen)||(valRl<limen && valRr<limen)){

		direction greenPosition = checkGreen();

		if(greenPosition==R){
			return rightangleR;
		}else if(greenPosition==L){
			return rightangleL;
		}else if(greenPosition==bothSides){
			return rightangleR;
		}else{
			if(varC<limen){
				return passOver;
			}else{
				if(valRl<limen&&valRr<limen){
					return rightangleR;
				}else{
					return rightangleL;
			}
		}
	}

	}else if(dis<=13 && dis>=7){

		return obstacle;

	}else if(valLl>=limen && valLr>=limen && valC>=limen && valRl>=limen && valRr>=limen){

		return white;

	}else {

		return Trace;

	}
}
