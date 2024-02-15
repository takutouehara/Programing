#pragma once

#include "../Utility/Vector2D.h"

class Barrier
{
private:
	int image;			// バリア画像
	int life_span;	// バリアの寿命
	int drawTimer;	//バリア表示時間
public:
	Barrier();
	~Barrier();

	void Draw(const Vector2D& location);	// 描画処理
	bool IsFinished();			// 寿命が尽きたか
};