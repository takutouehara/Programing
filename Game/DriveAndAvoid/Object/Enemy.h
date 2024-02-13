#pragma once

#include <string>
#include "../Utility/Vector2D.h"
#include <unordered_map>

class Enemy
{
public:
	enum class ComentType
	{
		NORMAL,			//���ʂ̃R�����g
		LAUGTH			//�΂��ɗގ������R�����g
	};

private:
	ComentType type;			// �^�C�v
	float speed;		// ����
	Vector2D location;	// �ʒu���
	Vector2D box_size;	// �����蔻��̑傫��

	//�R�����g
	std::string coment;
	//�t�H���g�n���h��
	int font;
	//�����̑傫��
	int fontSize;
	//�����p�t���O
	bool isExplosion;
	//�����A�j���[�V�����ԍ�
	int explosionAnimation;
	//�����摜
	int* explosionImage;

public:
	Enemy(int* image, ComentType type, std::string text);
	~Enemy();

	void Initialize(ComentType type, std::string text);
	void Update(float speed);
	void Draw()const;
	void Finalize();
	
	Enemy::ComentType GetType() const;			// �^�C�v�擾
	Vector2D GetLocation()const;	// �ʒu���̎擾
	Vector2D GetBoxSize()const;		// �����蔻��̑傫�����擾

	//�R�����g�쐬�֐�
	void CreateComent(ComentType type, std::string text);
	//�R�����g������ݒ�֐�
	void SetComentString(ComentType type);
	//����������
	void Explosion();
	//�����A�j���[�V�����ԍ���Getter
	int GetImage() { return explosionAnimation; }
};