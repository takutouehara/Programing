#include "Enemy.h"
#include "DxLib.h"
#include <memory>

Enemy::Enemy(int* image, ComentType type, std::string text) :type(type), speed(0.0f), location(0.0f), box_size(0.0f)
{
	Initialize(type,text);
	explosionImage = image;
}

Enemy::~Enemy()
{
	Finalize();
}

// 初期化処理
void Enemy::Initialize(ComentType type, std::string text)
{
	// 出現させるｘ座標パターンを取得
	float random_y = (float)(GetRand(6) * 105 + 40);
	// 生成位置の設定
	location = Vector2D(1000, random_y);
	// 当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	// 速さの設定
	speed = 10.0f;
	
	isExplosion = false;

	//コメントを生成
	CreateComent(type,text);
}

void Enemy::Update(float speed)
{
	if (isExplosion == false)
	{
		// 位置情報に移動量を加算する
		location.x += speed;
	}
	else
	{
		//爆発アニメーション
		explosionAnimation++;
	}


}

void Enemy::Draw() const
{
	if (isExplosion == false)
	{
		// コメント表示
		DrawFormatStringToHandle(location.x, location.y, 0xffffff, font, coment.c_str());
	}
	else
	{
		//爆発アニメーション再生
	}

}

void Enemy::Finalize()
{
	explosionImage = nullptr;
}

// 敵タイプを取得
Enemy::ComentType Enemy::GetType() const
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
void Enemy::CreateComent(ComentType type, std::string text)
{

	fontSize = 20;
	font = CreateFontToHandle("UD デジタル 教科書体 N-B", fontSize, 10, DX_FONTTYPE_ANTIALIASING_8X8);

	coment = text;

	this->type = type;

	int bX = fontSize * coment.size();
	int bY = fontSize;
	box_size = Vector2D(bX, bY);
}

void Enemy::SetComentString(ComentType type)
{

	
}

//爆発
void Enemy::Explosion()
{
	isExplosion = true;
}
