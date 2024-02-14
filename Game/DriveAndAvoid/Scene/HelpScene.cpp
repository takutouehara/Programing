#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene():background_image(NULL), background_font(NULL), color(GetColor(255, 255, 255))
{

}

HelpScene::~HelpScene()
{

}

// ����������
void HelpScene::Initialize()
{
	// �摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Ranking_Back.png");
	background_font = LoadGraph("Resource/images/Help_Font.png");

	// �G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Ranking_Back.png������܂���\n");
	}
	if (background_font == -1)
	{
		throw("Resource/images/Help_Font.png������܂���\n");
	}
}

// �X�V����
eSceneType HelpScene::Update()
{
	// B�{�^���������ꂽ��^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

// �`�揈��
void HelpScene::Draw() const
{
	// �w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);
	// �����摜�̕`��
	DrawGraph(100, 45, background_font, TRUE);

	// �Q�[������
	SetFontSize(40);

	DrawBox(64, 180, 1216, 648, GetColor(0, 153, 0), TRUE);
	DrawBox(64, 180, 1216, 648, GetColor(0, 0, 0), FALSE);

	DrawBox(260, 185, 1000, 340, GetColor(155, 0, 0), TRUE);

	DrawString(450, 190, "������@", color, 0);
	DrawString(290, 240, "�ړ�        �@�@�@�@    �X�e�B�b�N", color, 0);
	DrawString(290, 290, "����/�L�����Z��/�o���A�@A�{�^��", color, 0);

	DrawString(80, 350, "�E����Ă���R�����g�ɓ�����ƃ_���[�W", color, 0);
	DrawString(80, 400, "�E'�΂�'�Ɋւ��錾�t�ɓ�����Ɣ������đ�_���[�W", color, 0);
	DrawString(80, 450, "�E�̗͂��O�ɂȂ�ƃQ�[���[�I�[�o�[", color, 0);
	DrawString(80, 500, "�E�R�����g�̒��ɂ͓�����Ɨǂ����Ƃ�������̂�����܂�", color, 0);

	SetFontSize(55);
	DrawString(80, 555, "�R�����g����������n�C�X�R�A��ڎw�����I", 0xff00dd, 0);

	SetFontSize(20);
	DrawString(420, 620, "---- A�{�^���������ă^�C�g���֖߂� ----", 0xdd0000, 0);
}

// �I��������
void HelpScene::Finalize()
{
	// �ǂݍ��񂾉摜���폜
	DeleteGraph(background_image);
	DeleteGraph(background_font);
}

// ���݂̃V�[�������擾
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}
