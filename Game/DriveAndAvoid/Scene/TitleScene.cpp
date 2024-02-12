#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene():background_image(NULL),background_font(NULL), menu_image(NULL), cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

// 初期化処理
void TitleScene::Initialize()
{
	// 画像の読み込み
	background_image = LoadGraph("Resource/images/Title_Back.png");
	background_font = LoadGraph("Resource/images/Title_Font2.png");
	menu_image = LoadGraph("Resource/images/MENU_F.png");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	// エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title_Back.pngがありません\n");
	}
	if (background_font == -1)
	{
		throw("Resource/images/Title_Font2.pngがありません\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/MENU_F.pngがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}
	
}

// 更新処理
eSceneType TitleScene::Update()
{
	// カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor+=2;
		// 一番下に到達したら一番上にする
		if (menu_cursor > 6)
		{
			menu_cursor = 0;
		}
	}
	// カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		// 一番上に到達したら一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	// カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_RANKING_DISP;
		case 2:
			return eSceneType::E_HELP;
		default:
			return eSceneType::E_END;
		}
	}
	
	// 現在のシーンタイプを返す
	return GetNowScene();
}

// 描画処理
void TitleScene::Draw() const
{
	// タイトル画面の描画
	DrawGraph(0, 0, background_image, FALSE);

	// タイトル名の描画
	DrawGraph(20, 20, background_font, FALSE);

	// メニュー画面の描画
	DrawGraph(120, 200, menu_image, TRUE);

	// カーソル画像の描画
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}

// 終了時処理
void TitleScene::Finalize()
{
	// 読み込ん画像の削除
	DeleteGraph(background_image);
	DeleteGraph(background_font);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

// 現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}
