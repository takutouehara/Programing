#include "RankingInputScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

RankingInputScene::RankingInputScene():background_image(NULL),ranking(nullptr),time(0),name_num(0),cursor_x(0),cursor_y(0)
{
	memset(name, NULL, (sizeof(char) * 15));
	BGM = LoadSoundMem("Resource/sound/maou_bgm_fantasy10.mp3");
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, TRUE);
}

RankingInputScene::~RankingInputScene()
{
	
}

// 初期化処理
void RankingInputScene::Initialize()
{
	// 画像の読み込み
	background_image = LoadGraph("Resource/images/Ranking_Back.png");
	cursor_se = LoadSoundMem("Resource/sound/select01.mp3");
	enter_se = LoadSoundMem("Resource/sound/決定ボタンを押す3.mp3");
	// エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Ranking_Back.pngがありません\n");
	}

	// メモリの動的確保
	ranking = new RankingData;
	ranking->Initialize();

	// リザルトデータを取得する
	FILE* fp = nullptr;
	// ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが読み込めません\n");
	}

	// 結果を読み込む
	fscanf_s(fp, "%6d,\n", &time);

	// ファイルクローズ
	fclose(fp);
}

// 更新処理
eSceneType RankingInputScene::Update()
{
	bool is_change = false;

	// 名前入力処理
	is_change = InputName();

	// シーン変更は可能か？
	if (is_change)
	{
			StopSoundMem(BGM, 0);

		// ランキング表示に遷移
		return eSceneType::E_RANKING_DISP;
		
	}
	else
	{
		return GetNowScene();
	}
	return eSceneType();
}

// 描画処理
void RankingInputScene::Draw() const
{
	// 背景画像の描画
	DrawGraph(0, 0, background_image, TRUE);

	DrawBox(128, 180, 1152, 650, GetColor(0, 153, 0), TRUE);
	DrawBox(128, 180, 1152, 650, GetColor(0, 0, 0), FALSE);

	SetFontSize(64);
	// 名前入力指示文字列の描画
	DrawString(280, 90, "ランキングに登録します", 0xFF0000);
	DrawFormatString(180, 200, GetColor(255, 255, 255), ">%s", name);

	// 選択用文字を描画
	const int font_size = 75;
	for (int i = 0; i < 26; i++)
	{
		int x = (i % 13) * font_size + 170;
		int y = (i / 13) * font_size + 270;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%-6c", 'a' + i);
		y = ((i / 13) + 2) * font_size + 270;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%-3c", 'A' + i);
	}
	DrawString(380, 570, "決定", GetColor(255, 0, 0));
	DrawString(580 + font_size * 2, 570, "消す", GetColor(255, 0, 0));

	// 選択文字をフォーカスする
	if (cursor_y < 4)
	{
		int x = cursor_x * font_size + 150;
		int y = cursor_y * font_size + 265;
		DrawBox(x, y, x + font_size, y + font_size, GetColor(255, 255, 255), FALSE);
	}
	else
	{
		if (cursor_x == 0)
		{
			DrawBox(600, 100, font_size, font_size, GetColor(0, 0, 255), FALSE);
		}
		else
		{
			DrawBox(0, 0, font_size, font_size, GetColor(255, 0, 0), FALSE);
		}
	}
}

// 終了時処理
void RankingInputScene::Finalize()
{
	// ランキングにデータを格納
	ranking->SetRankingData(time, name);

	// 読み込んだ画像を削除
	DeleteGraph(background_image);

	// 動的メモリの解放
	delete ranking;
}

// 現在のシーン情報を取得
eSceneType RankingInputScene::GetNowScene() const
{
	return eSceneType::E_RANKING_INPUT;
}

// 名前入力処理
bool RankingInputScene::InputName()
{
	// カーソル操作処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{

		if (cursor_x > 0)
		{
			cursor_x--;
		}
		else
		{
			cursor_x = 12;
		}
		PlaySoundMem(cursor_se, DX_PLAYTYPE_NORMAL, TRUE);

	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{

		if (cursor_x < 12)
		{
			cursor_x++;
		}
		else
		{
			cursor_x = 0;
		}
		PlaySoundMem(cursor_se, DX_PLAYTYPE_NORMAL, TRUE);

	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{

		if (cursor_y > 0)
		{
			cursor_y--;
		}
		PlaySoundMem(cursor_se, DX_PLAYTYPE_NORMAL, TRUE);

	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{

		if (cursor_y < 4)
		{
			cursor_y++;
			if (cursor_y == 4)
			{
				cursor_x = 0;
			}
		}
		PlaySoundMem(cursor_se, DX_PLAYTYPE_NORMAL, TRUE);

	}

	// カーソル位置の文字を決定する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{

		if (cursor_y < 2)
		{
			PlaySoundMem(enter_se, DX_PLAYTYPE_NORMAL, TRUE);

			name[name_num++] = 'a' + cursor_x + (cursor_y * 13);
			if (name_num == 14)
			{
				cursor_x = 0;
				cursor_y = 4;
			}
		}
		else if (cursor_y < 4)
		{
			PlaySoundMem(enter_se, DX_PLAYTYPE_NORMAL, TRUE);

			name[name_num++] = 'A' + cursor_x + ((cursor_y - 2) * 13);
			if (name_num == 14)
			{
				cursor_x = 0;
				cursor_y = 4;
			}
		}
		else
		{
			if (cursor_x == 0)
			{
				PlaySoundMem(enter_se, DX_PLAYTYPE_NORMAL, TRUE);

				name[name_num] = '\0';
				return true;
			}
			else
			{
				PlaySoundMem(enter_se, DX_PLAYTYPE_NORMAL, TRUE);

				name[name_num--] = NULL;
			}
		}
	}


	return false;
}
