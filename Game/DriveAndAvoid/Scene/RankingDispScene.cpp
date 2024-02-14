#include "RankingDispScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

RankingDispScene::RankingDispScene():background_image(NULL), background_font(NULL),ranking(nullptr)
{

}

RankingDispScene::~RankingDispScene()
{

}

// ����������
void RankingDispScene::Initialize()
{
	// �摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Ranking_Back.png");
	background_font=LoadGraph("Resource/images/Ranking_Font.png");


	// �G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Ranking_Back.png������܂���\n");
	}
	if (background_font == -1)
	{
		throw("Resource/images/Ranking_Font.png������܂���\n");
	}

	// �����L���O�����擾
	ranking = new RankingData;
	ranking->Initialize();
}

// �X�V����
eSceneType RankingDispScene::Update()
{
	// B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

// �`�揈��
void RankingDispScene::Draw() const
{
	// �w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);
	// �����摜�̕`��
	DrawGraph(50, 35, background_font, TRUE);
	
	// �擾���������L���O�f�[�^��`�悷��
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

// �I��������
void RankingDispScene::Finalize()
{
	// �ǂݍ��񂾉摜���폜
	DeleteGraph(background_image);
	DeleteGraph(background_font);

	// ���I�������̉��
	ranking->Finalize();
	delete ranking;
}

// ���݂̃V�[�������擾
eSceneType RankingDispScene::GetNowScene() const
{
	return eSceneType::E_RANKING_DISP;
}
