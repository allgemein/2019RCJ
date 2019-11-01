#include"define.h"
#include"pin.h"
#include"prototype.h"

int judge_phase(){

	int phase;

	/*if(count_pht_silver()>=3){

	  phase = case_rescue;//銀テープを通ったとき
	  Serial.println("rescue");

	  }else*/if(analogRead(phtLl)<limen && analogRead(phtLr)<limen && phtRl<limen && analogRead(phtRr)<limen){

		  phase = case_crossing;//黒い線の上に乗ったとき
		  Serial.println("crossing");

	  }else if(analogRead(phtC)>limenC && count_backpht_white()==4){

		  phase = case_white;

	  }else if(analogRead(phtC)>limenC &&
			  analogRead(phtLl)<limen && 
			  analogRead(phtRl)>limen && analogRead(phtRr)>limen){

		  phase = case_Lrightangle;//左側のフォトリフレクタのみ黒になったとき

	  }else if(analogRead(phtC)>limenC &&
			  analogRead(phtLl)>limen && analogRead(phtLr)>limen &&
			  analogRead(phtRr)<limen){

		  phase = case_Rrightangle;//右側のフォトリフレクタのみ黒になったとき

	  }else if(digitalRead(bumperL)==0){

		  phase = case_obstacle;//10cm未満の距離に物体があったとき
		  Serial.println("obstacle");

	  }else {

		  phase = 1024;//普通のライントレースに移行するとき。値は適当

	  }

return phase;
}

int judge_green1(){
	int color[6];

	int num_green = 0;

	get_color(color);

	static int previous_redL = color[RedL];
	static int previous_redR = color[RedR];
	static int previous_greenL = color[GreenL];
	static int previous_greenR = color[GreenR];
	static int previous_blueL = color[BlueL];
	static int previous_blueR = color[BlueR];




	if((map(color[RedL]-previous_redL,0,previous_redL,0,1024)<map(color[GreenL]-previous_greenL,0,previous_greenL,0,1024)) &&
			!(map(color[GreenL]-previous_greenL,0,previous_greenL,0,1024)>map(color[BlueL]-previous_blueL,0,previous_blueL,0,1024))){
		num_green = L_position; 

	}else if(!(map(color[RedL]-previous_redL,0,previous_redL,0,1024)<map(color[GreenL]-previous_greenL,0,previous_greenL,0,1024)) &&
			(map(color[GreenL]-previous_greenL,0,previous_greenL,0,1024)>map(color[BlueL]-previous_blueL,0,previous_blueL,0,1024))){

		num_green = R_position;

	}else if((map(color[RedL]-previous_redL,0,previous_redL,0,1024)<map(color[GreenL]-previous_greenL,0,previous_greenL,0,1024)) &&
			(map(color[GreenL]-previous_greenL,0,previous_greenL,0,1024)>map(color[BlueL]-previous_blueL,0,previous_blueL,0,1024))){

		num_green = 2;

	}else{
		num_green= 0;
	}

	map(color[RedR]-previous_redR,0,previous_redR,0,1024);
	map(color[GreenR]-previous_greenR,0,previous_greenR,0,1024);
	map(color[BlueR]-previous_blueR,0,previous_blueR,0,1024);

	return num_green;
}

int judge_green2(){
	int color[6];

	int num_green = 0;

	get_color(color);

	static int previous_redL = color[RedL];
	static int previous_redR = color[RedR];
	
	int drop_redL = map(color[RedL]-previous_redL,0,previous_redL,0,100);
	int drop_redR = map(color[RedR]-previous_redR,0,previous_redR,0,100);


	if(drop_redL>=40 && drop_redL<40){

		num_green = L_position;

	}else if(drop_redL<40 && drop_redR>=40){

		num_green = R_position;

	}else if(drop_redL>=40 && drop_redR>=40){

		num_green = 2;

	}else{
		num_green = 0;
	}

	if(count_backpht_black()>3){
		num_green = 0;
	}

	return num_green;
}

int judge_green3(){
	int color[6];

	int num_green = 0;

	get_color(color);

	if((color[GreenL]-color[RedL])>limenG &&!(color[GreenR]>color[RedR])){
		num_green = L_position;
	}else if(!(color[GreenL]-color[RedL])>limenG && (color[GreenR]>color[RedR])){
		num_green = R_position;
	}else if((color[GreenL]-color[RedL])>limenG&&(color[GreenR]>color[RedR])){
		num_green = 2;
	}else{
		num_green = 0;
	}

	return num_green;
}

