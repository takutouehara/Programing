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
		LAUGTH,			//笑いに類似されるコメント
		HEAL_HP,		//回復コメント
		HEAL_BARRIER	//バリア回復コメント
	};

	//爆破ステータス
	enum class ExprosionState
	{
		NONE,			//爆破していない
		EXPROSION,		//爆破中
		FINISH			//爆破終了
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
	//文字色
	int textColor;
	//爆発ステータス
	ExprosionState exprosionState;
	//爆発画像
	int* explosionImage;
	//爆発アニメーションカウンター
	int explosionAnimationCount;
	//爆発アニメーション更新時間
	int animationUpdateTime;

	//デバック用
	Vector2D BoxLocation1;	//左上隅の座標
	Vector2D BoxLocation2;	//右上隅の座標


public:
	Enemy(int* image, ComentType type, std::string text,int font);
	~Enemy();

	void Initialize(ComentType type, std::string text, int font);
	void Update();
	void Draw()const;
	void Finalize();
	
	ComentType GetType() const;			// タイプ取得
	ExprosionState GetExprosionState()const { return exprosionState; }
	Vector2D GetLocation()const;	// 位置情報の取得
	Vector2D GetBoxSize()const;		// 当たり判定の大きさを取得

	//コメント作成関数
	void CreateComent(ComentType type, std::string text);
	//爆発させる
	void Explosion();
};