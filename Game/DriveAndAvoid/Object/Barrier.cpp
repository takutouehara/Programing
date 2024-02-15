#include "Barrier.h"
#include "DxLib.h"

Barrier::Barrier() :image(NULL), life_span(300),drawTimer(40)
{
	// �摜�̓ǂݍ���
	image = LoadGraph("Resource/images/barrier.png");

	// �G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/barrier.png������܂���\n");
	}
}

Barrier::~Barrier()
{
	// �ǂݍ��񂾉摜���폜
	DeleteGraph(image);
}

// �`�揈��
void Barrier::Draw(const Vector2D& location)
{
	if (120 < life_span || (life_span <= 120 && drawTimer <= 20))
	{
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	}
}

// �������s������
bool Barrier::IsFinished()
{
	if (0 < life_span)
	{
		life_span--;
	}
	if (life_span <= 120)
	{
		drawTimer++;
		if (40 <= drawTimer)
		{
			drawTimer = 0;
		}
	}
	return (life_span <= 0);
}
