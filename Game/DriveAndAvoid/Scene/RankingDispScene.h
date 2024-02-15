#pragma once

#include "SceneBase.h"
#include "../Object/RankingData.h"

class RankingDispScene :public SceneBase
{
private:

private:
	int background_font;	// 文字画像
	int background_image;	// 背景画像
	int enter_se;
	int BGM;
	RankingData* ranking;	// ランキング情報

public:
	RankingDispScene();
	virtual ~RankingDispScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};
