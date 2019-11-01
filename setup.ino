#include"define.h"
#include"pin.h"
#include"prototype.h"

void digitalpins_pinMode(){
	pinMode(USSRtrigR,OUTPUT);//超音波センサ用のデジタルピンのpinMode
	pinMode(USSRtrigL,OUTPUT);
	pinMode(USSRechoR,INPUT);
	pinMode(USSRechoL,INPUT);
	pinMode(RedLED,OUTPUT);
	pinMode(GreenLED,OUTPUT);
	pinMode(BlueLED,OUTPUT);
}
void set_limen(int *p){
	int valRr, valRl, valC,valLr,valLl,max_val,min_val;
	
	static int max_white = default_max_white;
	static int min_black = default_min_black;
	static int max_whiteC = default_max_whiteC;
	static int min_blackC = default_min_blackC;

	valRr = analogRead(phtRr);
	valRl = analogRead(phtRl);
	valC = analogRead(phtC);
	valLr = analogRead(phtLr);
	valLl = analogRead(phtLl);

	max_val = valRr;
	min_val = valRr;

	if (valRl>max_val){
		max_val = valRl;
	}else{
		min_val = valRl;
	}


	if (valLr>max_val){
		max_val = valLr;
	}else{
		min_val = valLr;
	}

	if (valLl>max_val){
		max_val = valLl;
	}else{
		min_val = valLl;
	}




	if(max_white<max_val) max_white = max_val;
	if(min_black>min_val) min_black = min_val;

	if(max_whiteC<valC) max_whiteC = valC;
	if(min_blackC>valC) min_blackC = valC;
	
	p[0] = (max_white+min_black)/2;
	p[1] = (max_whiteC+min_blackC)/2;

}
