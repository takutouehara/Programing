#include "Enemy.h"
#include "DxLib.h"
#include <memory>
#include <random>

Enemy::Enemy(int* image, ComentType type, std::string text) :type(type), speed(0.0f), location(0.0f), box_size(0.0f)
{
	Initialize(type,text);
	explosionImage = image;

	//�f�o�b�N�p
	BoxLocation1 = Vector2D(0.0f, 0.0f);
	BoxLocation2 = Vector2D(0.0f, 0.0f);
}

Enemy::~Enemy()
{
	Finalize();
}

// ����������
void Enemy::Initialize(ComentType type, std::string text)
{
	//��������
	std::random_device rnd;
	std::mt19937 mt(rnd());

	// �o�������邘���W�p�^�[�����擾
	float random_x = static_cast<float>(GetRand(3) * 50 + 1340);
	float random_y = static_cast<float>(GetRand(13) * 50 + 30);
	// �����ʒu�̐ݒ�
	location = Vector2D(1340, random_y);
	// �����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	// �����̐ݒ�
	std::uniform_int_distribution<> randSpeed(3, 7);
	speed = static_cast<float>(randSpeed(mt));
	
	isExplosion = false;

	//�R�����g�𐶐�
	CreateComent(type,text);
}

void Enemy::Update()
{
	if (isExplosion == false)
	{
		// �ʒu���Ɉړ��ʂ����Z����
		location.x -= speed;
	}
	else
	{
		//�����A�j���[�V����
		explosionAnimation++;
	}

	//�f�o�b�N�p
	BoxLocation1 = location - (box_size / 2);
	BoxLocation2 = location + (box_size / 2);

}

void Enemy::Draw() const
{
	if (isExplosion == false)
	{
		// �R�����g�\��
		DrawFormatStringToHandle(location.x, location.y, 0xffffff, font, coment.c_str());
	}
	else
	{
		//�����A�j���[�V�����Đ�
	}

	//�f�o�b�N�p
	DrawBoxAA(BoxLocation1.x, BoxLocation1.y, BoxLocation2.x, BoxLocation2.y, 0xff0000, false);
}

void Enemy::Finalize()
{
	explosionImage = nullptr;
}

// �G�^�C�v���擾
Enemy::ComentType Enemy::GetType() const
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
void Enemy::CreateComent(ComentType type, std::string text)
{

	fontSize = 20;
	font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", fontSize, 10, DX_FONTTYPE_ANTIALIASING_8X8);

	coment = text;

	this->type = type;

	int bX = fontSize * coment.size();
	int bY = fontSize;
	box_size = Vector2D(bX, bY);
}

void Enemy::SetComentString(ComentType type)
{

	
}

//����
void Enemy::Explosion()
{
	isExplosion = true;
}
