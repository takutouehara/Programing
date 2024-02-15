#include "RankingDispScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

RankingDispScene::RankingDispScene():background_image(NULL), background_font(NULL),ranking(nullptr)
{
	BGM = LoadSoundMem("Resource/sound/maou_bgm_fantasy10.mp3");
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, TRUE);
}

RankingDispScene::~RankingDispScene()
{

}

// 初期化処理
void RankingDispScene::Initialize()
{
	// 画像の読み込み
	background_image = LoadGraph("Resource/images/Ranking_Back.png");
	background_font=LoadGraph("Resource/images/Ranking_Font.png");
	enter_se = LoadSoundMem("Resource/sound/決定ボタンを押す3.mp3");


	// エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Ranking_Back.pngがありません\n");
	}
	if (background_font == -1)
	{
		throw("Resource/images/Ranking_Font.pngがありません\n");
	}

	// ランキング情報を取得
	ranking = new RankingData;
	ranking->Initialize();
}

// 更新処理
eSceneType RankingDispScene::Update()
{
	// Aボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{

		PlaySoundMem(enter_se, DX_PLAYTYPE_NORMAL, TRUE);
		StopSoundMem(BGM, 0);

		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

// 描画処理
void RankingDispScene::Draw() const
{
	// 背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);
	// 文字画像の描画
	DrawGraph(50, 35, background_font, TRUE);
	
	// 取得したランキングデータを描画する
	SetFontSize(70);
	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(50, 170 + i * 100, 0xff0000, "%2d", ranking->GetRank(i));
		DrawFormatString(200, 170 + i * 100, 0xffffff, "%-15s", ranking->GetName(i));

		if (ranking->GetTime(i) / 60 < 10 && ranking->GetTime(i) % 60 < 10)
		{
			DrawFormatString(800, 170 + i * 100, 0xffffff, "0%d:0%d", ranking->GetTime(i) / 60, ranking->GetTime(i) % 60);
		}
		if (ranking->GetTime(i) / 60 < 10 && ranking->GetTime(i) % 60 > 9)
		{
			DrawFormatString(800, 170 + i * 100, 0xffffff, "0%d:%d", ranking->GetTime(i) / 60, ranking->GetTime(i) % 60);
		}
		if (ranking->GetTime(i) / 60 > 9 && ranking->GetTime(i) % 60 < 10)
		{
			DrawFormatString(800, 170 + i * 100, 0xffffff, "%d:0%d", ranking->GetTime(i) / 60, ranking->GetTime(i) % 60);
		}
		if (ranking->GetTime(i) / 60 > 9 && ranking->GetTime(i) % 60 > 9)
		{
			DrawFormatString(800, 170 + i * 100, 0xffffff, "%d %d", ranking->GetTime(i) / 60, ranking->GetTime(i) % 60);
		}
	}
}

// 終了時処理
void RankingDispScene::Finalize()
{
	// 読み込んだ画像と音声を削除
	InitGraph();
	InitSoundMem();

	// 動的メモリの解放
	ranking->Finalize();
	delete ranking;
}

// 現在のシーン情報を取得
eSceneType RankingDispScene::GetNowScene() const
{
	return eSceneType::E_RANKING_DISP;
}
