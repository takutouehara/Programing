#pragma once
#include<math.h>
#include"Dxlib.h"

class FPS 
{
	int StartTime; //����J�n����
	int nowTime;
	int Count;    //�J�E���^
	float Fps;
	static const int N = 60; // ���ς��Ƃ�
	static const int sFps = 60;// �ݒ肵��FPS

public:
	bool Update() {
		if (Count == 0) { //1�t���[���ڂȂ玞�����L��
			StartTime = GetNowCount();
		}
		if (Count == N) { //60�t���[���ڂȂ畽�ς��v�Z����
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
		int tookTime = GetNowCount() - StartTime;		//������������
		int waitTime = Count * 1000 / sFps - tookTime;	//�҂ׂ�����
		if (waitTime > 0) {
			Sleep(waitTime);	//�ҋ@
		}
	}
};
