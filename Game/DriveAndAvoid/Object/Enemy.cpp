#include "Enemy.h"
#include "DxLib.h"
#include <memory>
#include <random>

Enemy::Enemy(int* image, ComentType type, std::string text, int font) :type(type), speed(0.0f), location(0.0f), box_size(0.0f)
{
	Initialize(type,text,font);
	if (type == ComentType::LAUGTH)
	{
		explosionImage = image;
	}
}
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
void Enemy::Initialize(ComentType type, std::string text, int font)
{
	//��������
	std::random_device rnd;
	std::mt19937 mt(rnd());

	// �o�������邘���W�p�^�[�����擾
	float random_x = static_cast<float>(GetRand(3) * 50 + 1340);
	float random_y = static_cast<float>(GetRand(10) * 50 + 200);
	// �����ʒu�̐ݒ�
	location = Vector2D(1340, random_y);
	
	// �����̐ݒ�
	std::uniform_int_distribution<> randSpeed(3, 7);
	speed = static_cast<float>(randSpeed(mt));
	
	exprosionState = ExprosionState::NONE;
	explosionAnimationCount = 0;
	animationUpdateTime = 0;
	this->font = font;
	//�R�����g�𐶐�
	CreateComent(type,text);
}

void Enemy::Update()
{
	if (exprosionState == ExprosionState::NONE)
	{
		// �ʒu���Ɉړ��ʂ����Z����
		location.x -= speed;
	}
	else
	{
		if (++animationUpdateTime % 3 == 0 && explosionAnimationCount < 10)
		{
			explosionAnimationCount++;
			if (10 <= explosionAnimationCount)
			{
				exprosionState = ExprosionState::FINISH;
			}
		}
	}

	//�f�o�b�N�p
	BoxLocation1 = location - (box_size / 2);
	BoxLocation2 = location + (box_size / 2);

}

void Enemy::Draw() const
{
	if (exprosionState == ExprosionState::NONE)
	{
		// �R�����g�\��
		DrawFormatStringToHandle(location.x, location.y, textColor, font, coment.c_str());
		//DrawBoxAA(location.x, location.y, location.x + box_size.x, location.y + box_size.y, 0xff0000, FALSE);
	}
	else if (exprosionState == ExprosionState::EXPROSION)
	{
		DrawGraphF(location.x, location.y, explosionImage[explosionAnimationCount],TRUE);
	}

	//�f�o�b�N�p
	DrawBoxAA(BoxLocation1.x, BoxLocation1.y, BoxLocation2.x, BoxLocation2.y, 0xff0000, false);
}

void Enemy::Finalize()
{
	if (type == ComentType::LAUGTH)
	{
		if (explosionImage != nullptr)
		{
			for (int i = 0; i < 10; i++)
			{
				if (explosionImage[i] == NULL)
				{
					DeleteGraph(explosionImage[i]);
				}
			}
		}
	}

	font = 0;
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
	
	if (type == ComentType::NORMAL || type == ComentType::LAUGTH)
	{
		textColor = 0xffffff;
	}
	else
	{
		textColor = 0x5AFF19;
	}

	coment = text;

	this->type = type;

	int bX = fontSize * (coment.size() / 2);
	int bY = fontSize;
	box_size = Vector2D(bX, bY);
}

//����
void Enemy::Explosion()
{
	exprosionState = ExprosionState::EXPROSION;
}
