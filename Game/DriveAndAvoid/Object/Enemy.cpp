#include "Enemy.h"
#include "DxLib.h"
#include <memory>

Enemy::Enemy(int* image, ComentType type, std::string text) :type(type), speed(0.0f), location(0.0f), box_size(0.0f)
{
	Initialize(type,text);
	explosionImage = image;
}

Enemy::~Enemy()
{
	Finalize();
}

// ����������
void Enemy::Initialize(ComentType type, std::string text)
{
	// �o�������邘���W�p�^�[�����擾
	float random_y = (float)(GetRand(6) * 105 + 40);
	// �����ʒu�̐ݒ�
	location = Vector2D(1000, random_y);
	// �����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	// �����̐ݒ�
	speed = 10.0f;
	
	isExplosion = false;

	//�R�����g�𐶐�
	CreateComent(type,text);
}

void Enemy::Update(float speed)
{
	if (isExplosion == false)
	{
		// �ʒu���Ɉړ��ʂ����Z����
		location.x += speed;
	}
	else
	{
		//�����A�j���[�V����
		explosionAnimation++;
	}


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
