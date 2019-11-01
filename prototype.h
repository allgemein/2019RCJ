#pragma once

/*プロトタイプ宣言用ヘッダーファイル*/

void MOVE(int Lpower, int Rpower);
void debug_pht();
void debug_color();
void debug_motor();
void debug_USSR();
void debug_green();
void digitalpins_pinMode();
int judge_phase();
void set_limen(int *p);
double get_distance(int position);
void get_color(int *p);
int count_pht_silver();
int count_backpht_black();
int count_backpht_black();
void turn(int position);
void rescue();
void crossing();
void rightangle(int position);
void obstacle();
void white();
void linetrace();
void linetrace_old();
void linetrace_ONOFF();
void brake();
void lolicon();
int judge_green1();
int judge_green2();
int judge_green3();
int judge_green4();
