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

// ����������
void RankingInputScene::Initialize()
{
	// �摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Ranking_Back.png");
	cursor_se = LoadSoundMem("Resource/sound/select01.mp3");
	ChangeVolumeSoundMem(100, cursor_se);
	enter_se = LoadSoundMem("Resource/sound/����{�^��������3.mp3");
	ChangeVolumeSoundMem(100, enter_se);
	// �G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Ranking_Back.png������܂���\n");
	}

	// �������̓��I�m��
	ranking = new RankingData;
	ranking->Initialize();

	// ���U���g�f�[�^���擾����
	FILE* fp = nullptr;
	// �t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���ǂݍ��߂܂���\n");
	}

	// ���ʂ�ǂݍ���
	fscanf_s(fp, "%6d,\n", &time);

	// �t�@�C���N���[�Y
	fclose(fp);
}

// �X�V����
eSceneType RankingInputScene::Update()
{
	bool is_change = false;

	// ���O���͏���
	is_change = InputName();

	// �V�[���ύX�͉\���H
	if (is_change)
	{
			StopSoundMem(BGM, 0);

		// �����L���O�\���ɑJ��
		return eSceneType::E_RANKING_DISP;
		
	}
	else
	{
		return GetNowScene();
	}
	return eSceneType();
}

// �`�揈��
void RankingInputScene::Draw() const
{
	// �w�i�摜�̕`��
	DrawGraph(0, 0, background_image, TRUE);

	DrawBox(128, 180, 1152, 650, GetColor(0, 153, 0), TRUE);
	DrawBox(128, 180, 1152, 650, GetColor(0, 0, 0), FALSE);

	SetFontSize(64);
	// ���O���͎w��������̕`��
	DrawString(280, 90, "�����L���O�ɓo�^���܂�", 0xFF0000);
	DrawFormatString(180, 200, GetColor(255, 255, 255), ">%s", name);

	// �I��p������`��
	const int font_size = 75;
	for (int i = 0; i < 26; i++)
	{
		int x = (i % 13) * font_size + 170;
		int y = (i / 13) * font_size + 270;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%-6c", 'a' + i);
		y = ((i / 13) + 2) * font_size + 270;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%-3c", 'A' + i);
	}
	DrawString(380, 570, "����", GetColor(255, 0, 0));
	DrawString(580 + font_size * 2, 570, "����", GetColor(255, 0, 0));

	// �I�𕶎����t�H�[�J�X����
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

// �I��������
void RankingInputScene::Finalize()
{
	// �����L���O�Ƀf�[�^���i�[
	ranking->SetRankingData(time, name);

	// �ǂݍ��񂾃f�[�^���폜
	DeleteGraph(background_image);
	DeleteSoundMem(BGM);
	DeleteSoundMem(cursor_se);
	DeleteSoundMem(enter_se);

	// ���I�������̉��
	delete ranking;
}

// ���݂̃V�[�������擾
eSceneType RankingInputScene::GetNowScene() const
{
	return eSceneType::E_RANKING_INPUT;
}

// ���O���͏���
bool RankingInputScene::InputName()
{
	//�X�e�B�b�N���͒l
	Vector2D lstick = InputControl::GetleftStick();

	// �J�[�\�����쏈��
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

	// �J�[�\���ʒu�̕��������肷��
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
