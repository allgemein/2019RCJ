#include "define.h"
#include"pin.h"
#include"prototype.h"

void linetrace_old(){
	int diff,Lpower,Rpower,differential;
	Lpower=0;
	Rpower=0;

	float fix_power_differential;
	char str[254];//sprintf()用の文字配列
	static int previous_diff = 50;

	diff = analogRead(phtLr)-analogRead(phtRl);//左右内側のフォトリフレクタの値の差を取る
	differential = abs(diff)-abs(previous_diff);//前回のループと今回のループのdiffの差を取り、両者の間での変化の激しさを調べる。この値を用いて微分的な処理などを行う

	if(abs(diff)>600){//diffに激しい変化があった場合
		fix_power_differential=1.5;//p値の係数を大きくする
		Serial.println("1.5");
	}else if(differential<150){//diffの変化が少量であった場合
		fix_power_differential=0.7;//p値の係数を小さくし
		Serial.println("0.7");
		Lpower+=50;
		Rpower+=50;//左右のモータの基礎出力を上げる
	}else{//乗算に使う変数なので、どちらでもない場合には影響のないよう1を代入しておく
		Serial.println("");
		fix_power_differential=1;
	}

	Lpower += basic_motorpower+(diff*Kp*fix_power_differential);
	Rpower += basic_motorpower-(diff*Kp*fix_power_differential);//前進するための基礎出力に対し、左右のフォトリフレクタの値の差と比例の係数と先ほどの係数とをかけたものを加算(と減算)する

	if(analogRead(phtC)>limenC){//中央のフォトリフレクタが白のとき、角やカーブと判定して出力の差を増強する

		if(analogRead(phtLl)>analogRead(phtRr)){
			Lpower+=boostpower_corner;
			Rpower-=boostpower_corner;
		}else{
			Lpower-=boostpower_corner;
			Rpower+=boostpower_corner;
		}
	}

	if(Rpower<0){
		Rpower-=basic_motorpower;
	}
	if(Lpower<0){
		Lpower-=basic_motorpower;
	}



	sprintf(str,"power: %4d,%4d",Lpower,Rpower);//シリアルモニタに見やすく表示されるよう、配列にLpowerとRpowerと文字列を結合した文字列を格納する
	Serial.print(str);//先の文字列をシリアルモニタに出力する
	debug_pht();//フォトリフレクタの値を出力する

	MOVE(Lpower,Rpower);//決定された出力でモータを動かす
	delay(5);//負荷軽減のためにdelayをかける

	previous_diff = diff;//比較に使うために今回のdiffの値を保存しておく
}

void linetraceONOFF(){
  int valRr, valRl, valC,valLr, valLl;
  char str[254];

  valRr = analogRead(phtRr);
  valRl = analogRead(phtRl);
  valC = analogRead(phtC);
  valLr = analogRead(phtLr);
  valLl = analogRead(phtLl);

  if (valRr < limen) MOVE(255, -200);
  else if (valLl < limen) MOVE(-200, 255);
  else if (valRr < limen) MOVE(255, 100);
  else if (valLr < limen) MOVE(100, 255);
  else if (valC < limen) MOVE(100 , 100 );
  else MOVE(100 , 100 );


  delay(5);

  sprintf(str, "pht:%4d%4d%4d%4d%4d", valLl, valLr, valC, valRl, valRr);
  Serial.println(str);

}

void linetrace(){
	int diff,propotial,integral,differential,Lpower,Rpower;
	char str[254];
	static int previous_diff = 0;
	static int previous_diff2 = 0;

	diff = analogRead(phtLr)-analogRead(phtRl);

	propotial = Kp*(diff-previous_diff);
	integral = Ki*diff;
	differential = Kd*((diff-previous_diff)-(previous_diff-previous_diff2));

	Lpower = basic_motorpower+(propotial+integral+differential);
	Rpower = basic_motorpower-(propotial+integral+differential);

	MOVE(Lpower,Rpower);

	previous_diff2 = previous_diff;
	previous_diff = diff;

	sprintf(str,"power: %4d%4d",Lpower,Rpower);

	Serial.println(str);
	
	delay(5);
}

void white(){
	int i = 0;
	while(count_backpht_black()==0){
		MOVE(150,150);
		delay(5);
		if(i==50) break;
	}
	while(count_backpht_black()==0){
		MOVE(-150,-150);
		delay(5);
	}
}
