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

// ����������
void ResultScene::Initialize()
{
	// �摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/Stage_Back.png");
	
	// �G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/Stage_Back.png������܂���\n");
	}

	// �Q�[�����ʂ̓ǂݍ���
	ReadResultData();
}

// �X�V����
eSceneType ResultScene::Update()
{
	// B�{�^���Ń����L���O�ɑJ�ڂ���
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		return eSceneType::E_RANKING_INPUT;
	}

	return GetNowScene();
}

// �`�揈��
void ResultScene::Draw() const
{
	// �w�i�摜��`��
	DrawGraph(0, 0, back_ground, TRUE);

	// �X�R�A���\���̈�
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
	DrawString(245, 580, "---- A�{�^���������ă����L���O�� ----", 0xdd0000, 0);
}

// �I��������
void ResultScene::Finalize()
{
	// �ǂݍ��񂾉摜���폜
	InitGraph();
	InitSoundMem();
}

// ���݂̃V�[�������擾
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

// ���U���g�f�[�^�̓ǂݍ���
void ResultScene::ReadResultData()
{
	// �t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���ǂݍ��߂܂���\n");
	}

	fscanf_s(fp, "%d,\n", &starttime);

	// �t�@�C���N���[�Y
	fclose(fp);
}
