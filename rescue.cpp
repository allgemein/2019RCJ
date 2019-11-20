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

//壁まで進んで角まで後進するプログラム
void rescue_setup(){
    float minDisL = 0;
    move_to_wall(ultraSonicSensor usF);
    localozation_wall(ultraSonicSensor usL);

    while (!(usF.getDistance() <= machine_size )){
        MOVE(50, 50);
        delay(5);
    }

    MOVE(-50,-50);
    delay(300);

    for(int time = 0; time <= 60; time=time+1){
        MOVE(50,-50);
        if (minDisL > usL.getDistance()){
            minDisL = usL.getDistance();
        }
        delay(500);
    }

    while(!(usL.getDistance() = minDisL)){
        MOVE(-50,50);
        delay(5);
    }

    //ここにアームを開く動作を入れる//

    MOVE(-50,-50);
    delay(sec);
    find_ball();
}

//ボールが見つかるまでコース内を走行するプログラム
void find_ball(){

    float minDisL = 100;
    localozation_wallL(ultraSonicSensor usL);
    localozation_wallR(ultraSonicSensor usR);

    while(){    //ここにボールを持ってるかどうか判別する式を入れる//
        for(int time = 0; time <= 60; time=time+1){ //入口から見て右
            MOVE(50,-50);
            if (minDisL > usL.getDistance()){
                minDisL = usL.getDistance();
            }
            delay(500);
        }

        while(!(usL.getDistance() = minDisL)){
            MOVE(-50,50);
            delay(5);
        }

        MOVE(-50,-50);
        delay(change_line);
        float minDisF = 100;

        for(int time = 0; time <= 60; time=time+1){ 
            MOVE(50,-50);
            if (minDisF > usF.getDistance()){
                minDisF = usF.getDistance();
            }
            delay(500);
        }

        while(!(usF.getDistance() = minDisF)){
            MOVE(-50,50);
            delay(5);
        }

        MOVE(-100,-100);
        delay(sec);

        //ここにボールが合ったらpic_up_ballに移る動作を入れる//

        for(int time = 0; time <= 60; time=time+1){ //入口から見て左で回るやつ
            MOVE(-50,50);
            if (minDisL > usR.getDistance()){
                minDisL = usR.getDistance();
            }
            delay(500);
        }

        while(!(usL.getDistance() = minDisL)){
            MOVE(50,-50);
            delay(5);
        }

        MOVE(-50,-50);
        delay(change_line);
        float minDisF = 100;

        for(int time = 0; time <= 60; time=time+1){ 
            MOVE(-50,50);
            if (minDisF > usF.getDistance()){
                minDisF = usF.getDistance();
            }
            delay(500);
        }

        while(!(usF.getDistance() = minDisF)){
            MOVE(50,-50);
            delay(5);
        }

        MOVE(-100,-100);
        delay(sec);

        //ここにボールが合ったらpic_up_ballに移る動作を入れる//

    }

}

//ボールが見つかったら回収するプログラム
void pic_up_ball(){

}

//ボールを持ってるのを確認出来たら三角コーナーを探してボールを落とすプログラム
void find_triangle_and_drop_ball (){

}