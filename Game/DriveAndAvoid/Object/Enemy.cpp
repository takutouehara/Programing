#include "Enemy.h"
#include "DxLib.h"
#include <memory>
#include <random>

Enemy::Enemy(int* image, ComentType type, std::string text, int font) :type(type), speed(0.0f), location(0.0f), box_size(0.0f)
{
	Initialize(type,text,font);
	if (type == ComentType::LAUGTH)
	{
		explosionImage = image;
	}
}
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
void Enemy::Initialize(ComentType type, std::string text, int font)
{
	//乱数生成
	std::random_device rnd;
	std::mt19937 mt(rnd());

	// 出現させるｘ座標パターンを取得
	float random_x = static_cast<float>(GetRand(3) * 50 + 1340);
	float random_y = static_cast<float>(GetRand(10) * 50 + 200);
	// 生成位置の設定
	location = Vector2D(1340, random_y);
	
	// 速さの設定
	std::uniform_int_distribution<> randSpeed(3, 7);
	speed = static_cast<float>(randSpeed(mt));
	
	exprosionState = ExprosionState::NONE;
	explosionAnimationCount = 0;
	animationUpdateTime = 0;
	this->font = font;
	//コメントを生成
	CreateComent(type,text);
}

void Enemy::Update()
{
	if (exprosionState == ExprosionState::NONE)
	{
		// 位置情報に移動量を加算する
		location.x -= speed;
	}
	else
	{
		if (++animationUpdateTime % 3 == 0 && explosionAnimationCount < 10)
		{
			explosionAnimationCount++;
			if (10 <= explosionAnimationCount)
			{
				exprosionState = ExprosionState::FINISH;
			}
		}
	}

	//デバック用
	BoxLocation1 = location - (box_size / 2);
	BoxLocation2 = location + (box_size / 2);

}

void Enemy::Draw() const
{
	if (exprosionState == ExprosionState::NONE)
	{
		// コメント表示
		DrawFormatStringToHandle(location.x, location.y, textColor, font, coment.c_str());
		//DrawBoxAA(location.x, location.y, location.x + box_size.x, location.y + box_size.y, 0xff0000, FALSE);
	}
	else if (exprosionState == ExprosionState::EXPROSION)
	{
		DrawGraphF(location.x, location.y, explosionImage[explosionAnimationCount],TRUE);
	}

	//デバック用
	DrawBoxAA(BoxLocation1.x, BoxLocation1.y, BoxLocation2.x, BoxLocation2.y, 0xff0000, false);
}

void Enemy::Finalize()
{
	if (type == ComentType::LAUGTH)
	{
		if (explosionImage != nullptr)
		{
			for (int i = 0; i < 10; i++)
			{
				if (explosionImage[i] == NULL)
				{
					DeleteGraph(explosionImage[i]);
				}
			}
		}
	}

	font = 0;
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
	
	if (type == ComentType::NORMAL || type == ComentType::LAUGTH)
	{
		textColor = 0xffffff;
	}
	else
	{
		textColor = 0x5AFF19;
	}

	coment = text;

	this->type = type;

	int bX = fontSize * (coment.size() / 2);
	int bY = fontSize;
	box_size = Vector2D(bX, bY);
}

//爆発
void Enemy::Explosion()
{
	exprosionState = ExprosionState::EXPROSION;
}
