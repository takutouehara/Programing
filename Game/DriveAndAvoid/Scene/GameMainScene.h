#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include <vector>
#include <memory>
#include <unordered_map>

class GameMainScene :public SceneBase
{
private:
	int high_score;		// ハイスコア
	int back_ground;	// 背景画像
	int barrier_image;	// バリア画像
	int mileage;		// 走行距離
	int enemy_image[3];	// 敵画像
	int enemy_count[3];	// 通り過ぎた敵カウント
	Player* player;		// プレイヤー
	
	//敵（コメント）配列
	std::vector<std::shared_ptr<Enemy>> enemy;
	//コメントテキスト格納配列
	std::unordered_map<Enemy::ComentType, std::vector<std::string>>comentText;
	//std::unordered_map<Enemy::ComentType, std::vector<std::string>>comentText;
	
public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	// ハイスコア読み込み処理
	void ReadHighScore();
	// 当たり判定
	bool IsHitCheck(Player* p, std::shared_ptr<Enemy> e);
	//コメントテキスト設定関数
	void SetComentText();
	//コメント設定関数
	std::string SetComent(Enemy::ComentType type);
};