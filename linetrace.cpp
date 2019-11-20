#include"lineTrace.h"

//超音波センサのオブジェクトと旋回の方向を引数に取った関数。その超音波センサが適切な値を読み取るまで指定した方向へ旋回し続ける
void turnToFindObstacle(ultraSonicSensor us,enum direction direction){
	//超音波センサの値を取って距離を初期化
	double dis = us.getDistance();
	//超音波センサの値が一定範囲内でないあいだずっと
	while(dis > 13 || dis < 7){
		//directionに応じた方向に旋回する
		switch(direction){
			case R:
				MOVE(50, -50);
				break;
			case L:
				MOVE(-50,50);
				break;
			default:
				break;
		}
		delay(5);
		//距離を更新
		dis = us.getDistance();
	}
}

//障害物回避関数.超音波センサのオブジェクトを引数にとる
void dodge_movement(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR){

	//左側に障害物が見つかるまで右へ旋回
	turnToFindObstacle(usL,R);

	//左右内側のセンサのどちらも黒を読んでいないとき
	while(analogRead(phtRl)>=limen && analogRead(phtLr)>=limen){
		//左のセンサで計測した距離を取得
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

void rightangleBasedOnLine(enum direction direction){
	switch(direction){
		case R:
			MOVE(100,-100);
			break;
		case L:
			MOVE(-100,100);
			break;
		default:
			break;
	}

	delay(200);

	while(analogRead(phtC)>=limen){
		switch(direction){
			case R:
				MOVE(100,-100);
				break;
			case L:
				MOVE(-100,100);
				break;
			default:
				break;

		}

		delay(5);

	}
}

	/*pid制御によるライントレース関数
	 * ラインを挟んだ二つのフォトリフレクタの読み取り値同士の差が0であるときをラインが機体中央にあるときと想定し、差(diff)=0を目標値としてpid制御を行う*/

	void pid(){
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

enum phase judgePhase(ultraSonicSensor usF){

	//フォトリフレクタと超音波センサの測定値を格納しておく変数
	int valLl = analogRead(phtLl);
	int valLr = analogRead(phtLr);
	int valC = analogRead(phtC);
	int valRl = analogRead(phtRl);
	int valRr = analogRead(phtRr);
	double dis = usF.getDistance();

	//どちらか方側のフォトリフレクタ二つが黒なら
	if((valLl<limen && valLr<limen)||(valRl<limen && valRr<limen)){

		//緑色の位置を取得
		direction greenPosition = checkGreen();

		//右側だけに緑があれば右に曲がる関数へ
		if(greenPosition==R){
			return rightangleR;
			//左側だけに緑があれば左に曲がる関数へ
		}else if(greenPosition==L){
			return rightangleL;
			//両側に緑があればUターンする関数へ
		}else if(greenPosition==bothSides){
			return rightangleR;
			//緑がないなら
		}else{
			//中央のフォトリフレクタが黒、すなわち線が正面にも続いているなら
			if(valC<limen){
				//交差点を通り過ぎる関数へ
				return passOver;
				//中央ののフォトリフレクタが白、すなわちただの直角なら
			}else{
				//右側が黒のとき
				if(valRl<limen&&valRr<limen){
					//右に曲がる関数へ
					return rightangleR;
					//左側が黒のとき
				}else{
					//左に曲がる関数へ
					return rightangleL;
				}
			}
		}

		//正面の超音波センサの取得した距離が一定値以内なら障害物を回避する関数へ
	}else if(dis<=13 && dis>=7){

		return obstacle;

		//すべてのフォトリフレクタが白なら線を探索する関数へ
	}else if(valLl>=limen && valLr>=limen && valC>=limen && valRl>=limen && valRr>=limen){

		return white;

		//上のどれにも当てはまらない場合ライントレースをする関数へ
	}else {

		return Trace;

	}
}

void searchLine(){

	//黒い線を見つけるか100ms経過するまで前進する。黒い線を見つけたら関数の処理を終了
	if(moveUntilLineFound(F,500)) return;

	while(1){

	//黒い線を見つけるか100ms経過するまで右へ旋回する。黒い線を見つけたら関数の処理を終了
		if(moveUntilLineFound(R,100)) return;
	//黒い線を見つけるか200ms経過するまで左へ旋回する。黒い線を見つけたら関数の処理を終了 
		if(moveUntilLineFound(L,200)) return;
	//黒い線を見つけるか100ms経過するまで前進する。黒い線を見つけたら関数の処理を終了
		if(moveUntilLineFound(F,100)) return;
	}
}

void passOverLine(){
	//中央右と左のセンサが白を読むまで前進
	while(analogRead(phtLr)<limen||analogRead(phtRl)<limen){
		MOVE(100,100);
		delay(5);
	}
}

bool moveUntilLineFound(enum direction direction,int delaymSecond){
	
	//delaymSecondミリ秒間directionに応じて前進または旋回する
	for(int i=0;i<delaymSecond;i++){
		switch(direction){
			case R:
				MOVE(100,-100);
				break;
			case L:
				MOVE(-100,100);
				break;
			case F:
				MOVE(100,100);
				break;
			default:
				break;
		}
		delay(1);

		//黒い線を見つけたらtrueを返して処理を終了する
		if(analogRead(phtLl)<limen) return true;
		if(analogRead(phtLr)<limen) return true;
		if(analogRead(phtC)<limen) return true;
		if(analogRead(phtRl)<limen) return true;
		if(analogRead(phtRr)<limen) return true;
	}

	//delaymSecond秒前進または旋回しても黒い線が見つからなかったらfalseを返して処理を終了する
	return false;

}
