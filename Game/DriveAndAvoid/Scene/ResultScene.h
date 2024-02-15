#pragma once

#include "SceneBase.h"

class ResultScene :public SceneBase
{
private:
	int back_ground;	// ”wŒi‰æ‘œ
	int starttime;
	int BGM;
public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	void ReadResultData();
};