//レスキューのところに来たら動くプログラム

//1.壁まで突き進む
//2.右に曲がって壁まで進む
//3.90°旋回して後ろに進む
//4.壁まで来たら画像の動きをする
//5.一定時間センサが反応
//              →しなかったら4
//              →したら6
//6.移動しながらボールを持ち上げる
//7.三角コーナーを見つける為にコースを周回
//8.三角コーナー見つけたらボールを捨てる


//サーボで「アームの上下」と「アームの開閉」を行う
//アームが閉じた状態で移動→最初に開く挙動を入れる

#include"rescue.h"

float DisL = 0;
float DisR = 0;

float minDisL = 100;
float minDisR = 100;

Servo arm_servo;

void setUpServo(){
    arm_servo.attach(arm_servo_pin);
}

//壁まで進んで角まで後進するプログラム
void rescue_setup(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR){
    
    move_to_wall(usF);  
    localozation_wall(usL);

    while (!(usF.getDistance() <= machine_size )){
        MOVE(100,100);
        delay(5);
    }

    MOVE(-100,-100);
    delay(300);

    for(int time = 0; time <= 50; time++){
        MOVE(100,-100);
        if (minDisL > usL.getDistance()){
            minDisL = usL.getDistance();
        }
        delay(100);
    }

    while(!(usL.getDistance() == minDisL)){
        MOVE(-100,100);
        delay(5);
    }

    arm_servo.write(arm_open);
    delay(3000);

    MOVE(-100,-100);
    delay(sec);
    find_ball(usL,usF,usR);
}

//ボールが見つかるまでコース内を走行するプログラム
void find_ball(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR){

    localozation_wall(usL);
    localozation_wall(usR);

    while(1){
    
        minDisL = 100;
        for(int time = 0; time <= 50; time++){ //入口から見て右
            MOVE(100,-100);
            if (minDisL > usL.getDistance()){
                minDisL = usL.getDistance();
            }
            delay(100);
        }

        while(!(usL.getDistance() == minDisL)){
            MOVE(-100,10);
            delay(5);
        }

        MOVE(-100,-100);
        delay(change_line);
        float minDisF = 100;

        for(int time = 0; time <= 50; time=time+1){ 
            MOVE(50,-50);
            if (minDisF > usF.getDistance()){
                minDisF = usF.getDistance();
            }
            delay(100);
        }

        while(!(usF.getDistance() == minDisF)){
            MOVE(-100,100);
            delay(5);
        }

        MOVE(-100,-100);
        delay(sec);

        if(analogRead(photoBall) > exsist_ball){
            delay(2000);
            if(analogRead(photoBall) > exsist_ball){ 
                pic_up_ball();
            }
        }
        
        minDisL = 100;
        for(int time = 0; time <= 50; time=time+1){ //入口から見て左で回るやつ
            MOVE(-100,100);
            if (minDisL > usR.getDistance()){
                minDisL = usR.getDistance();
            }
            delay(100);
        }

        while(!(usL.getDistance() == minDisL)){
            MOVE(100,-100);
            delay(5);
        }

        MOVE(-100,-100);
	    delay(change_line);
        minDisF = 100;

        for(int time = 0; time <= 50; time=time+1){ 
            MOVE(-100,100);
            if (minDisF > usF.getDistance()){
                minDisF = usF.getDistance();
            }
            delay(100);
        }

        while(!(usF.getDistance() == minDisF)){
            MOVE(100,-100);
            delay(5);
        }

        MOVE(-100,-100);
        delay(sec);

        if(analogRead(photoBall) > exsist_ball){
            delay(2000);
            if(analogRead(photoBall) > exsist_ball){ 
                pic_up_ball();
            }
        }
    }
}

//ボールが見つかったら回収するプログラム
void pic_up_ball(){
    arm_servo.attach(arm_close);
    delay(10000);
    find_triangle_and_drop_ball();
}

//ボールを持ってるのを確認出来たら三角コーナーを探してボールを落とすプログラム
void find_triangle_and_drop_ball(ultraSonicSensor usL,ultraSonicSensor usF,ultraSonicSensor usR){
    //壁まで移動
    while(usF.getDistance() > 7){
        MOVE(100,100);
    }    

    //ここから右回りに角を探す作業
    while(1){

        minDisR = 100;

        for(int time = 0; time <= 50; time++){ 
            MOVE(100,-100);
            
            if (minDisR > usR.getDistance()){
               minDisR = usR.getDistance();
            }
            delay(100);
        }

        while(!(usR.getDistance() == minDisR)){
            MOVE(-100,100);
            delay(5);
        }

        MOVE(-100,-100);
        delay(sec);

        if(usR.getDistance() >= minDisR + 2){
            arm_servo.write(arm_open);
            break;
        }

    }

    
}
