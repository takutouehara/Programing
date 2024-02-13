#pragma once

#include "Vector2D.h"

#define MAXL_X 32767.f  //���X�e�B�b�NX���̍ő�l(float�^)
#define MAXL_Y 32767.f  //���X�e�B�b�NY���̍ő�l(float�^)

// ���͊Ǘ��@�\
class InputControl
{
private:
	static bool now_button[16]; // ���݃t���[�����͒l 
	static bool old_button[16]; // �ߋ��t���[�����͒l
	static float trigger[2];	// ���E�g���K�[���͒l
	static Vector2D stick[2];	// ���E�X�e�B�b�N���͒l
	static float LstickRadX;		// ���X�e�B�b�Nx�p�x
	static float LstickRadY;		// ���X�e�B�b�Ny�p�x

public:
	static void Update();	// �X�V����

	// �{�^�����͎擾����
	static bool GetButton(int button);		// ���������Ă����
	static bool GetButtonDown(int button);	// �������u��
	static bool GetButtonUp(int button);	// �������u��

	// �g���K�[���͎擾����
	static float GetLeftTrigger();	// ���g���K�[
	static float GetRightTrigger();	// �E�g���K�[

	// �X�e�B�b�N���͎擾����
	static Vector2D GetleftStick();		// ���X�e�B�b�N
	static Vector2D GetRightStick();	// �E�X�e�B�b�N	

	static float GetLstickRadX();//�X�e�B�b�Nx�p�x�擾
	static float GetLstickRadY();//�X�e�B�b�Ny�p�x�擾

private:
	// �{�^���z��͈̓`�F�b�N
	static bool CheckButtonRange(int button);
};