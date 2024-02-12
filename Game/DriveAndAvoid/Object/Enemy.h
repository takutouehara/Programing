#pragma once

#include <string>
#include "../Utility/Vector2D.h"

class Enemy
{
private:
	int type;			// タイプ
	float speed;		// 速さ
	Vector2D location;	// 位置情報
	Vector2D box_size;	// 当たり判定の大きさ

	//コメント
	std::string coment;
	//フォントハンドル
	int font;
	//文字の大きさ
	int fontSize;

public:
	Enemy();
	~Enemy();

	void Initialize();
	void Update(float speed);
	void Draw()const;
	void Finalize();
	
	int GetType() const;			// タイプ取得
	Vector2D GetLocation()const;	// 位置情報の取得
	Vector2D GetBoxSize()const;		// 当たり判定の大きさを取得

	//コメント生成関数
	void GenerateComent();
};