#pragma once

#include "SceneBase.h"
#include "../Object/RankingData.h"

class RankingDispScene :public SceneBase
{
private:

private:
	int background_font;	// •¶š‰æ‘œ
	int background_image;	// ”wŒi‰æ‘œ
	int enter_se;

	RankingData* ranking;	// ƒ‰ƒ“ƒLƒ“ƒOî•ñ

public:
	RankingDispScene();
	virtual ~RankingDispScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};
