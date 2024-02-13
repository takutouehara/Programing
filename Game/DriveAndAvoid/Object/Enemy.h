#pragma once

#include <string>
#include "../Utility/Vector2D.h"
#include <unordered_map>

class Enemy
{
public:
	enum class ComentType
	{
		NORMAL,			//普通のコメント
		LAUGTH			//笑いに類似されるコメント
	};

private:
	ComentType type;			// タイプ
	float speed;		// 速さ
	Vector2D location;	// 位置情報
	Vector2D box_size;	// 当たり判定の大きさ

	//コメント
	std::string coment;
	//フォントハンドル
	int font;
	//文字の大きさ
	int fontSize;
	//爆発用フラグ
	bool isExplosion;
	//爆発アニメーション番号
	int explosionAnimation;
	//爆発画像
	int* explosionImage;

public:
	Enemy(int* image, ComentType type, std::string text);
	~Enemy();

	void Initialize(ComentType type, std::string text);
	void Update(float speed);
	void Draw()const;
	void Finalize();
	
	Enemy::ComentType GetType() const;			// タイプ取得
	Vector2D GetLocation()const;	// 位置情報の取得
	Vector2D GetBoxSize()const;		// 当たり判定の大きさを取得

	//コメント作成関数
	void CreateComent(ComentType type, std::string text);
	//コメント文字列設定関数
	void SetComentString(ComentType type);
	//爆発させる
	void Explosion();
	//爆発アニメーション番号のGetter
	int GetImage() { return explosionAnimation; }
};