#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"

class Player
{
private:
	bool is_active;		// �L����Ԃ�
	int image;			// �摜�f�[�^
	Vector2D location;	// �ʒu���W
	Vector2D box_size;	// �����蔻��̑傫��
	float angle;		// �p�x
	float speed;		// ����
	float hp;			// �̗�
	float fuel;			// �R��
	int barrier_count;	// �o���A�̖���
	Barrier* barrier;	// �o���A

	bool is_HitFlg;	//�G�ƐڐG������
	int FlashTime;	//�_�Ŏ���

	//�f�o�b�N�p
	Vector2D BoxLocation1;	//������̍��W
	Vector2D BoxLocation2;	//�E����̍��W


public:
	Player();
	~Player();

	void Initialize();	// ����������
	void Update();		// �X�V����
	void Draw();		// �`�揈��
	void Finalize();	// �I��������

public:
	void SetActive(bool flg);		// �L���t���O�ݒ�
	void DecreaseHp(float value);	// �̗͌�������
	Vector2D GetLocation()const;	// �ʒu���W�擾
	Vector2D GetBoxSize()const;		// �����蔻��̑傫���擾
	float GetSpeed()const;			// �����擾����
	float GetFuel()const;			// �R���擾
	float GetHp()const;				// �̗͎擾
	int GetBarriarCount()const;		// �o���A�̖����擾
	void AddBarriarCount() { barrier_count++; }
	bool IsBarrier()const;			// �o���A���L�������擾
	void SetHitFlg(bool flg);		// �G�ƐڐG�t���O�ݒ�
	bool GetHitFlg();				// �G�ƐڐG�t���O�擾
	float GetFlashTime()const;		//�_�Ŏ��Ԏ擾


private:
	void Movement();	// �ړ�����
	void Acceleration();	// ��������
};