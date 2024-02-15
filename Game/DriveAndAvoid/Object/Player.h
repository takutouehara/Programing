#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"

class Player
{
private:
	bool is_active;		// 有効状態か
	int image;			// 画像データ
	Vector2D location;	// 位置座標
	Vector2D box_size;	// 当たり判定の大きさ
	float angle;		// 角度
	float speed;		// 速さ
	float hp;			// 体力
	float fuel;			// 燃料
	int barrier_count;	// バリアの枚数
	Barrier* barrier;	// バリア

	bool is_HitFlg;	//敵と接触したか
	int FlashTime;	//点滅時間

	//デバック用
	Vector2D BoxLocation1;	//左上隅の座標
	Vector2D BoxLocation2;	//右上隅の座標


public:
	Player();
	~Player();

	void Initialize();	// 初期化処理
	void Update();		// 更新処理
	void Draw();		// 描画処理
	void Finalize();	// 終了時処理

public:
	void SetActive(bool flg);		// 有効フラグ設定
	bool GetActive()const { return is_active; }
	void DecreaseHp(float value);	// 体力減少処理
	Vector2D GetLocation()const;	// 位置座標取得
	Vector2D GetBoxSize()const;		// 当たり判定の大きさ取得
	float GetSpeed()const;			// 速さ取得処理
	float GetFuel()const;			// 燃料取得
	float GetHp()const;				// 体力取得
	int GetBarriarCount()const;		// バリアの枚数取得
	void AddBarriarCount() { barrier_count++; }
	bool IsBarrier()const;			// バリアが有効かを取得
	void SetHitFlg(bool flg);		// 敵と接触フラグ設定
	bool GetHitFlg();				// 敵と接触フラグ取得
	float GetFlashTime()const;		//点滅時間取得


private:
	void Movement();	// 移動処理
	void Acceleration();	// 加速処理
};