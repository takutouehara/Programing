#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene():background_image(NULL), background_font(NULL), color(GetColor(255, 255, 255))
{

}

HelpScene::~HelpScene()
{

}

// 初期化処理
void HelpScene::Initialize()
{
	// 画像の読み込み
	background_image = LoadGraph("Resource/images/Ranking_Back.png");
	background_font = LoadGraph("Resource/images/Help_Font.png");

	// エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Ranking_Back.pngがありません\n");
	}
	if (background_font == -1)
	{
		throw("Resource/images/Help_Font.pngがありません\n");
	}
}

// 更新処理
eSceneType HelpScene::Update()
{
	// Bボタンが押されたらタイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

// 描画処理
void HelpScene::Draw() const
{
	// 背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);
	// 文字画像の描画
	DrawGraph(100, 45, background_font, TRUE);

	// ゲーム説明
	SetFontSize(40);

	DrawBox(64, 180, 1216, 648, GetColor(0, 153, 0), TRUE);
	DrawBox(64, 180, 1216, 648, GetColor(0, 0, 0), FALSE);

	DrawBox(260, 185, 1000, 340, GetColor(155, 0, 0), TRUE);

	DrawString(450, 190, "操作方法", color, 0);
	DrawString(290, 240, "移動        　　　　    スティック", color, 0);
	DrawString(290, 290, "決定/キャンセル/バリア　Aボタン", color, 0);

	DrawString(80, 350, "・流れてくるコメントに当たるとダメージ", color, 0);
	DrawString(80, 400, "・'笑い'に関する言葉に当たると爆発して大ダメージ", color, 0);
	DrawString(80, 450, "・体力が０になるとゲームーオーバー", color, 0);
	DrawString(80, 500, "・コメントの中には当たると良いことがあるものもあります", color, 0);

	SetFontSize(55);
	DrawString(80, 555, "コメントを避け続けハイスコアを目指そう！", 0xff00dd, 0);

	SetFontSize(20);
	DrawString(420, 620, "---- Aボタンを押してタイトルへ戻る ----", 0xdd0000, 0);
}

// 終了時処理
void HelpScene::Finalize()
{
	// 読み込んだ画像を削除
	DeleteGraph(background_image);
	DeleteGraph(background_font);
}

// 現在のシーン情報を取得
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}
