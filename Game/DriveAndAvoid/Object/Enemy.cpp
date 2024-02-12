#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy() :type(type), speed(0.0f), location(0.0f), box_size(0.0f)
{
	fontSize = 20;
	font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", fontSize, 10, DX_FONTTYPE_ANTIALIASING_8X8);
	coment = "";
	type = 0;

	Initialize();
}

Enemy::~Enemy()
{
	Finalize();
}

// ����������
void Enemy::Initialize()
{
	// �o�������邘���W�p�^�[�����擾
	float random_y = (float)(GetRand(6) * 105 + 40);
	// �����ʒu�̐ݒ�
	location = Vector2D(1000, random_y);
	// �����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	// �����̐ݒ�
	speed = (float)(this->type * 2);
	
	//�R�����g�𐶐�
	GenerateComent();
}

void Enemy::Update(float speed)
{
	// �ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(this->speed + speed - 6, 0.0f);
}

void Enemy::Draw() const
{
	// �R�����g�\��
	DrawFormatStringToHandle(location.x, location.y, 0xffffff, font, coment.c_str());

}

void Enemy::Finalize()
{

}

// �G�^�C�v���擾
int Enemy::GetType() const
{
	return type;
}

// �ʒu�����擾
Vector2D Enemy::GetLocation() const
{
	return location;
}

// �����蔻��̑傫�����擾
Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}

//�R�����g����
void Enemy::GenerateComent()
{
	coment = "wwww";

	int bX = fontSize * coment.size();
	int bY = fontSize;
	box_size = Vector2D(bX, bY);
}