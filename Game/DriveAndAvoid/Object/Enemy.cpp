#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy() :type(type), speed(0.0f), location(0.0f), box_size(0.0f)
{
	fontSize = 20;
	font = CreateFontToHandle("UD デジタル 教科書体 N-B", fontSize, 10, DX_FONTTYPE_ANTIALIASING_8X8);
	coment = "";
	type = 0;

	Initialize();
}

Enemy::~Enemy()
{
	Finalize();
}

// 初期化処理
void Enemy::Initialize()
{
	// 出現させるｘ座標パターンを取得
	float random_y = (float)(GetRand(6) * 105 + 40);
	// 生成位置の設定
	location = Vector2D(1000, random_y);
	// 当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	// 速さの設定
	speed = (float)(this->type * 2);
	
	//コメントを生成
	GenerateComent();
}

void Enemy::Update(float speed)
{
	// 位置情報に移動量を加算する
	location += Vector2D(this->speed + speed - 6, 0.0f);
}

void Enemy::Draw() const
{
	// コメント表示
	DrawFormatStringToHandle(location.x, location.y, 0xffffff, font, coment.c_str());

}

void Enemy::Finalize()
{

}

// 敵タイプを取得
int Enemy::GetType() const
{
	return type;
}

// 位置情報を取得
Vector2D Enemy::GetLocation() const
{
	return location;
}

// 当たり判定の大きさを取得
Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}

//コメント生成
void Enemy::GenerateComent()
{
	coment = "wwww";

	int bX = fontSize * coment.size();
	int bY = fontSize;
	box_size = Vector2D(bX, bY);
}