#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
 
#define PleyerMoveSpeed 5	//�v���C���[�̈ړ����x

Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr)
{

}

Player::~Player()
{

}

// ����������
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(17.0f, 20.5f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 1000;
	fuel = 20000;
	barrier_count = 3;

	// �摜�̓ǂݍ���
	image = LoadGraph("Resource/images/Player_Acter.png");

	// �G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/Player_Acter.png������܂���\n");
	}

	//�f�o�b�N�p
	BoxLocation1 = Vector2D(0.0f, 0.0f);
	BoxLocation2 = Vector2D(0.0f, 0.0f);

}

// �X�V����
void Player::Update()
{
	// ����s��Ԃł���΁A���g����]������
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}

	// �R���̏���
	fuel -= speed;

	// �ړ�����
	Movement();

	// ����������
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	// �o���A����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	// �o���A����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		// �o���A���Ԃ��o�߂������@���Ă�����A�폜����
		if (barrier->IsFinished())
		{
			delete barrier;
			barrier = nullptr;
		}
	}

	//�f�o�b�N�p
	BoxLocation1 = location - (box_size );
	BoxLocation2 = location + (box_size );

}

// �`�揈��
void Player::Draw()
{
	// �v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
	
	// �o���A����������Ă�����A�`����s��
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}

	//�f�o�b�N�p
	//DrawBoxAA(BoxLocation1.x,BoxLocation1.y, BoxLocation2.x, BoxLocation2.y,0xff0000,false );
}

// �I��������
void Player::Finalize()
{
	// �ǂݍ��񂾉摜���폜
	DeleteGraph(image);

	// �o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

// ��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

// �̗͌�������
void Player::DecreaseHp(float value)
{
	if (is_active == true && barrier == nullptr)
	{
		this->hp += value;
		if (this->hp < 0)
		{
			this->hp = 0;
		}
	}
}

// �ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

// �����蔻��̑傫���擾����
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

// �����擾����
float Player::GetSpeed() const
{
	return this->speed;
}

// �R���擾����
float Player::GetFuel() const
{
	return this->fuel;
}

// �̗͎擾����
float Player::GetHp() const
{
	return this->hp;
}

// �o���A�����擾����
int Player::GetBarriarCount() const
{
	return this->barrier_count;
}

// �o���A���L�����@������
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

// �ړ�����
void Player::Movement()
{
	float  stick_y = InputControl::GetLstickRadY();
	float  stick_x = InputControl::GetLstickRadX();

	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	if (stick_y != 0 || stick_x != 0) {
		move += Vector2D(stick_x * PleyerMoveSpeed, -stick_y * PleyerMoveSpeed);
	}

	location += move;

	// ��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 1280.0f - box_size.x) || (location.y < box_size.y) || (location.y >= 720.0f - box_size.y)||(location.y <= 150.0f - box_size.y))
	{
		location -= move;
	}
}

// ����������
void Player::Acceleration()
{
	// LB�{�^���������ꂽ�猸������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	// RB�{�^���������ꂽ���������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}


