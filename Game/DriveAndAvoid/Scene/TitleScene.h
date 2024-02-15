#pragma once

#include "SceneBase.h"

class TitleScene :public SceneBase
{
private:
	
private:
	int background_font;	// 文字画像
	int background_image;	// 背景画像 
	int menu_image;			// メニュー画像
	int cursor_image;		// カーソル画像
	int menu_cursor;		// メニューカーソル画像
	int acter;				// アクター画像
	int BGM;				// タイトルBGM
	int cursor_se;			// カーソル音
	int enter_se;			// 決定音

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};