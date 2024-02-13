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
		LAUGTH,			//�΂��ɗގ������R�����g
		HEAL_HP,		//�񕜃R�����g
		HEAL_BARRIER	//�o���A�񕜃R�����g
	};

	//���j�X�e�[�^�X
	enum class ExprosionState
	{
		NONE,			//���j���Ă��Ȃ�
		EXPROSION,		//���j��
		FINISH			//���j�I��
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
	//�����X�e�[�^�X
	ExprosionState exprosionState;
	//�����摜
	int* explosionImage;
	//�����A�j���[�V�����J�E���^�[
	int explosionAnimationCount;
	//�����A�j���[�V�����X�V����
	int animationUpdateTime;
public:
	Enemy(int* image, ComentType type, std::string text);
	~Enemy();

	void Initialize(ComentType type, std::string text);
	void Update();
	void Draw()const;
	void Finalize();
	
	ComentType GetType() const;			// �^�C�v�擾
	ExprosionState GetExprosionState()const { return exprosionState; }
	Vector2D GetLocation()const;	// �ʒu���̎擾
	Vector2D GetBoxSize()const;		// �����蔻��̑傫�����擾

	//�R�����g�쐬�֐�
	void CreateComent(ComentType type, std::string text);
	//����������
	void Explosion();
};