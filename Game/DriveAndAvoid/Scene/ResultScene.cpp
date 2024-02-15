#include "ResultScene.h"
#include "../Object/RankingData.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "GameMainScene.h"

ResultScene::ResultScene():back_ground(NULL),starttime(0)
{
	BGM = LoadSoundMem("Resource/sound/maou_bgm_fantasy10.mp3");
	ChangeVolumeSoundMem(100,BGM);
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, TRUE);

	SetDrawBright(255, 255, 255);
}

ResultScene::~ResultScene()
{

}

// 初期化処理
void ResultScene::Initialize()
{
	// 画像の読み込み
	back_ground = LoadGraph("Resource/images/Stage_Back.png");
	
	// エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/Stage_Back.pngがありません\n");
	}

	// ゲーム結果の読み込み
	ReadResultData();
}

// 更新処理
eSceneType ResultScene::Update()
{
	// Bボタンでランキングに遷移する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		return eSceneType::E_RANKING_INPUT;
	}

	return GetNowScene();
}

// 描画処理
void ResultScene::Draw() const
{
	// 背景画像を描画
	DrawGraph(0, 0, back_ground, TRUE);

	// スコア等表示領域
	DrawBox(128, 72, 1152, 648, 0x87cefa, TRUE);
	DrawBox(128, 72, 1152, 648, GetColor(0, 0, 0), FALSE);

	SetFontSize(80);
	DrawString(225,100,"R E S U L T  T I M E",0x7fff00);

	SetFontSize(350);

	if (starttime / 60 < 60 )
	{
		if (starttime / 60 < 10 && starttime % 60 < 10)
		{
			DrawFormatString(180, 240, 0xffffff, "0%d:0%d", starttime / 60, starttime % 60);
		}
		if (starttime / 60 < 10 && starttime % 60 > 9)
		{
			DrawFormatString(180, 240, 0xffffff, "0%d:%d", starttime / 60, starttime % 60);
		}
		if (starttime / 60 > 9 && starttime % 60 < 10)
		{
			DrawFormatString(180, 240, 0xffffff, "%d:0%d", starttime / 60, starttime % 60);
		}
		if (starttime / 60 > 9 && starttime % 60 > 9)
		{
			DrawFormatString(180, 240, 0xffffff, "%d %d", starttime / 60, starttime % 60);
		}
	}
	else if (starttime / 60 > 59)
	{
		DrawString(180, 240, "error", 0xee0000);
	}
	
	SetFontSize(40);
	DrawString(245, 580, "---- Aボタンを押してランキングへ ----", 0xdd0000, 0);
}

// 終了時処理
void ResultScene::Finalize()
{
	// 読み込んだ画像を削除
	InitGraph();
	InitSoundMem();
}

// 現在のシーン情報を取得
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

// リザルトデータの読み込み
void ResultScene::ReadResultData()
{
	// ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが読み込めません\n");
	}

	fscanf_s(fp, "%d,\n", &starttime);

	// ファイルクローズ
	fclose(fp);
}
