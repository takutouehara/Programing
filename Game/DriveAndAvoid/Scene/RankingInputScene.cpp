#include "RankingInputScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

RankingInputScene::RankingInputScene():background_image(NULL),ranking(nullptr),time(0),name_num(0),cursor_x(0),cursor_y(0)
{
	memset(name, NULL, (sizeof(char) * 15));
	BGM = LoadSoundMem("Resource/sound/maou_bgm_fantasy10.mp3");
	ChangeVolumeSoundMem(100, BGM);
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
	ChangeVolumeSoundMem(100, cursor_se);
	enter_se = LoadSoundMem("Resource/sound/決定ボタンを押す3.mp3");
	ChangeVolumeSoundMem(100, enter_se);
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
		float x = static_cast<float>(cursor_x * font_size + 150);
		float y = (cursor_y * font_size + 265);
		
		DrawBoxAA(x, y, x + font_size, y + font_size, 0x000000, FALSE, 2.0);
	}
	else
	{
		if (cursor_x == 0)
		{
			float x = static_cast <float>(5 * font_size);
			float y = static_cast <float>(4 * font_size + 265);
			
			DrawBoxAA(x, y, x + font_size * 2, y + font_size, 0x0000ff, FALSE, 2.0);
		}
		else
		{
			float x = static_cast <float>(10 * font_size - 30);
			float y = static_cast <float>(4 * font_size + 265);
			
			DrawBoxAA(x, y, x + font_size * 2, y + font_size, 0xff0000, FALSE, 2.0);
		}
	}
}

// 終了時処理
void RankingInputScene::Finalize()
{
	// ランキングにデータを格納
	ranking->SetRankingData(time, name);

	// 読み込んだデータを削除
	DeleteGraph(background_image);
	DeleteSoundMem(BGM);
	DeleteSoundMem(cursor_se);
	DeleteSoundMem(enter_se);

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
	//スティック入力値
	Vector2D lstick = InputControl::GetleftStick();

	// カーソル操作処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT) || lstick.x == -1.0f)
	{

		if (cursor_x > 0)
		{
			cursor_x--;
		}
		else
		{
			cursor_x = 12;
			if (cursor_y == 4)
			{
				cursor_x = 1;
			}
		}
		PlaySoundMem(cursor_se, DX_PLAYTYPE_NORMAL, TRUE);

	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT) || lstick.x == 1.0f)
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
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP) || lstick.y == 1.0f)
	{

		if (cursor_y > 0)
		{
			if (cursor_y == 4)
			{
				if (cursor_x == 0)
				{
					cursor_x = 3;
				}
				else
				{
					cursor_x = 8;
				}
			}
			cursor_y--;
		}
		else
		{
			cursor_y = 4;
			if (cursor_x <= 6)
			{
				cursor_x = 0;
			}
			else
			{
				cursor_x = 1;
			}
		}
		PlaySoundMem(cursor_se, DX_PLAYTYPE_NORMAL, TRUE);

	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || lstick.y == -1.0f)
	{

		if (cursor_y < 4)
		{
			cursor_y++;
			if (cursor_y == 4)
			{
				if (cursor_x <= 6)
				{
					cursor_x = 0;
				}
				else
				{
					cursor_x = 1;
				}
			}
		}
		else
		{
			cursor_y = 0;
			if (cursor_x == 0)
			{
				cursor_x = 3;
			}
			else
			{
				cursor_x = 8;
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

			if (name_num < 14)
			{
				name[name_num++] = 'a' + cursor_x + (cursor_y * 13);
			}
			
		}
		else if (cursor_y < 4)
		{
			PlaySoundMem(enter_se, DX_PLAYTYPE_NORMAL, TRUE);

			if (name_num < 14)
			{
				name[name_num++] = 'A' + cursor_x + ((cursor_y - 2) * 13);
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
				if (0 < name_num)
				{
					name_num--;
				}
				name[name_num] = NULL;
			}
		}
	}


	return false;
}
