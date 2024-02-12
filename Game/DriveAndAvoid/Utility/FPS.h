#pragma once
#include<math.h>
#include"Dxlib.h"

class FPS 
{
	int StartTime; //測定開始時間
	int nowTime;
	int Count;    //カウンタ
	float Fps;
	static const int N = 60; // 平均をとる
	static const int sFps = 60;// 設定したFPS

public:
	bool Update() {
		if (Count == 0) { //1フレーム目なら時刻を記憶
			StartTime = GetNowCount();
		}
		if (Count == N) { //60フレーム目なら平均を計算する
			int t = GetNowCount();
			Fps = 1000.f / ((t - StartTime) / (float)N);
			Count = 0;
			StartTime = t;
		}
		Count++;
		nowTime = GetNowCount();
		return true;
	}
	void Draw() {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", Fps);
	}

	void Wait() {
		int tookTime = GetNowCount() - StartTime;		//かかった時間
		int waitTime = Count * 1000 / sFps - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
		}
	}
};
