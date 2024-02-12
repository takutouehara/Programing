#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene():background_image(NULL),background_font(NULL), menu_image(NULL), cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

// ����������
void TitleScene::Initialize()
{
	// �摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Title_Back.png");
	background_font = LoadGraph("Resource/images/Title_Font2.png");
	menu_image = LoadGraph("Resource/images/MENU_F.png");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	// �G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title_Back.png������܂���\n");
	}
	if (background_font == -1)
	{
		throw("Resource/images/Title_Font2.png������܂���\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/MENU_F.png������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmp������܂���\n");
	}
	
}

// �X�V����
eSceneType TitleScene::Update()
{
	// �J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor+=2;
		// ��ԉ��ɓ��B�������ԏ�ɂ���
		if (menu_cursor > 6)
		{
			menu_cursor = 0;
		}
	}
	// �J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		// ��ԏ�ɓ��B�������ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	// �J�[�\������i���肵����ʂɑJ�ڂ���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_RANKING_DISP;
		case 2:
			return eSceneType::E_HELP;
		default:
			return eSceneType::E_END;
		}
	}
	
	// ���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

// �`�揈��
void TitleScene::Draw() const
{
	// �^�C�g����ʂ̕`��
	DrawGraph(0, 0, background_image, FALSE);

	// �^�C�g�����̕`��
	DrawGraph(20, 20, background_font, FALSE);

	// ���j���[��ʂ̕`��
	DrawGraph(120, 200, menu_image, TRUE);

	// �J�[�\���摜�̕`��
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}

// �I��������
void TitleScene::Finalize()
{
	// �ǂݍ���摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(background_font);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

// ���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}
