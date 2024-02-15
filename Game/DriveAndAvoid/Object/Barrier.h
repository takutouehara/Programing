#pragma once

#include "../Utility/Vector2D.h"

class Barrier
{
private:
	int image;			// �o���A�摜
	int life_span;	// �o���A�̎���
	int drawTimer;	//�o���A�\������
public:
	Barrier();
	~Barrier();

	void Draw(const Vector2D& location);	// �`�揈��
	bool IsFinished();			// �������s������
};