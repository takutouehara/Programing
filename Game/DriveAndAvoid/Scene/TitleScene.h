#pragma once

#include "SceneBase.h"

class TitleScene :public SceneBase
{
private:
	
private:
	int background_font;
	int background_image;	// 背景画像 
	int menu_image;			// メニュー画像
	int cursor_image;		// カーソル画像
	int menu_cursor;		// メニューカーソル画像

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};