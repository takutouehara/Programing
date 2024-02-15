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
	int starttime;
	int FPSCount;
	int high_time;		// ハイスコア
	int barrier_image;	// バリア画像
	int mileage;		// 走行距離
	int enemy_count[3];	// 通り過ぎた敵カウント
	//int Hp_width;       // Hpゲージの横幅
	//int Hp;             // 体力
	//int MaxHp;          // 体力の最大値
	//int HpGauge;
	Player* player;		// プレイヤー
	
	//敵（コメント）配列
	std::vector<std::shared_ptr<Enemy>> enemy;
	//コメントテキスト格納配列
	std::unordered_map<Enemy::ComentType, std::vector<std::string>>comentText;
	//コメント最大生成数
	int maxSpawnNum;
	//コメントフォント
	int comentFont;
	//laughtコメントを生成する乱数値の範囲
	int laughtLengthNum;
	//コメント生成間隔時間
	int spawnInterval;
	//背景動画ハンドル
	int movieHandle;
	//爆発アニメーション画像
	int exprosionImage[10];
	//バリアコメントが存在しているかのフラグ
	bool isSpawnBaria;
	//ヒットSE
	int seHit;
	//爆発SE
	int seExprosion;
	//回復SE
	int seHeal;
	//画面照度値
	int brightValue;
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
	void ReadHighTime();
	// 当たり判定
	bool IsHitCheck(Player* p, std::shared_ptr<Enemy> e);
	//コメントテキスト設定関数
	void SetComentText();
	//コメント設定関数
	std::string SetComent(Enemy::ComentType type);
	//コメント生成関数
	void SpawnCooment(int time);
};