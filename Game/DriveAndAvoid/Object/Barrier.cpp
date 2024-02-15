#include "Barrier.h"
#include "DxLib.h"

Barrier::Barrier() :image(NULL), life_span(300),drawTimer(40)
{
	// 画像の読み込み
	image = LoadGraph("Resource/images/barrier.png");

	// エラーチェック
	if (image == -1)
	{
		throw("Resource/images/barrier.pngがありません\n");
	}
}

Barrier::~Barrier()
{
	// 読み込んだ画像を削除
	DeleteGraph(image);
}

// 描画処理
void Barrier::Draw(const Vector2D& location)
{
	if (120 < life_span || (life_span <= 120 && drawTimer <= 20))
	{
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	}
}

// 寿命が尽きたか
bool Barrier::IsFinished()
{
	if (0 < life_span)
	{
		life_span--;
	}
	if (life_span <= 120)
	{
		drawTimer++;
		if (40 <= drawTimer)
		{
			drawTimer = 0;
		}
	}
	return (life_span <= 0);
}
