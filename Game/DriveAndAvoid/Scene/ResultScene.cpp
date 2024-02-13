#include "ResultScene.h"
#include "../Object/RankingData.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "GameMainScene.h"

ResultScene::ResultScene():back_ground(NULL),starttime(0),test(603)
{
	
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

	if (test / 60 < 60 )
	{
		if (test / 60 < 10 && test % 60 < 10)
		{
			DrawFormatString(180, 240, 0xffffff, "0%d:0%d", test / 60, test % 60);
		}
		if (test / 60 < 10 && test % 60 > 9)
		{
			DrawFormatString(180, 240, 0xee0000, "0%d:%d", test / 60, test % 60);
		}
		if (test / 60 > 9 && test % 60 < 10)
		{
			DrawFormatString(180, 240, 0xffffff, "%d:0%d", test / 60, test % 60);
		}
		if (test / 60 > 9 && test % 60 > 9)
		{
			DrawFormatString(180, 240, 0xffffff, "%d %d", test / 60, test % 60);
		}
	}
	else if (test / 60 > 59)
	{
		DrawString(150, 100, "error", 0xee0000);
	}
	
	SetFontSize(40);
	DrawString(245, 580, "---- A�{�^���������ă^�C�g���֖߂� ----", 0xdd0000, 0);
}

// �I��������
void ResultScene::Finalize()
{
	// �ǂݍ��񂾉摜���폜
	DeleteGraph(back_ground);
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

	fscanf_s(fp, "%6d,\n", &starttime);

	// �t�@�C���N���[�Y
	fclose(fp);
}
