#pragma once

#include "SceneBase.h"
#include "../Object/RankingData.h"

class RankingInputScene :public SceneBase
{
private:
	int background_image;	// 背景画像
	RankingData* ranking;	// ランキング情報
	int time;				// スコア
	char name[15];			// 名前
	int name_num;			// 名前入力数
	int cursor_x;			// カーソルX座標
	int cursor_y;			// カーソルY座標
	
public:
	int cursor_se;			//カーソル音
	int enter_se;			//決定音
	int BGM;
	RankingInputScene();
	virtual ~RankingInputScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	// 名前入力処理
	bool InputName();
};