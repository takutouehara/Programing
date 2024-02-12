#pragma once

#include <string>
#include "../Utility/Vector2D.h"

class Enemy
{
private:
	int type;			// �^�C�v
	float speed;		// ����
	Vector2D location;	// �ʒu���
	Vector2D box_size;	// �����蔻��̑傫��

	//�R�����g
	std::string coment;
	//�t�H���g�n���h��
	int font;
	//�����̑傫��
	int fontSize;

public:
	Enemy();
	~Enemy();

	void Initialize();
	void Update(float speed);
	void Draw()const;
	void Finalize();
	
	int GetType() const;			// �^�C�v�擾
	Vector2D GetLocation()const;	// �ʒu���̎擾
	Vector2D GetBoxSize()const;		// �����蔻��̑傫�����擾

	//�R�����g�����֐�
	void GenerateComent();
};