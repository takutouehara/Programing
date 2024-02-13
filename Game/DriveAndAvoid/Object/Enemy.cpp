#include "Enemy.h"
#include "DxLib.h"
#include <memory>
#include <random>

Enemy::Enemy(int* image, ComentType type, std::string text) :type(type), speed(0.0f), location(0.0f), box_size(0.0f)
{
	Initialize(type,text);
	explosionImage = image;

	//デバック用
	BoxLocation1 = Vector2D(0.0f, 0.0f);
	BoxLocation2 = Vector2D(0.0f, 0.0f);
}

Enemy::~Enemy()
{
	Finalize();
}

// 初期化処理
void Enemy::Initialize(ComentType type, std::string text)
{
	//乱数生成
	std::random_device rnd;
	std::mt19937 mt(rnd());

	// 出現させるｘ座標パターンを取得
	float random_x = static_cast<float>(GetRand(3) * 50 + 1340);
	float random_y = static_cast<float>(GetRand(13) * 50 + 30);
	// 生成位置の設定
	location = Vector2D(1340, random_y);
	// 当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	// 速さの設定
	std::uniform_int_distribution<> randSpeed(3, 7);
	speed = static_cast<float>(randSpeed(mt));
	
	isExplosion = false;

	//コメントを生成
	CreateComent(type,text);
}

void Enemy::Update()
{
	if (isExplosion == false)
	{
		// 位置情報に移動量を加算する
		location.x -= speed;
	}
	else
	{
		//爆発アニメーション
		explosionAnimation++;
	}

	//デバック用
	BoxLocation1 = location - (box_size / 2);
	BoxLocation2 = location + (box_size / 2);

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

	//デバック用
	DrawBoxAA(BoxLocation1.x, BoxLocation1.y, BoxLocation2.x, BoxLocation2.y, 0xff0000, false);
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
