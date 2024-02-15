#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include <vector>
#include <memory>
#include <unordered_map>

class GameMainScene :public SceneBase
{
private:
	int starttime;
	int FPSCount;
	int high_time;		// �n�C�X�R�A
	int barrier_image;	// �o���A�摜
	int mileage;		// ���s����
	int enemy_count[3];	// �ʂ�߂����G�J�E���g
	//int Hp_width;       // Hp�Q�[�W�̉���
	//int Hp;             // �̗�
	//int MaxHp;          // �̗͂̍ő�l
	//int HpGauge;
	Player* player;		// �v���C���[
	
	//�G�i�R�����g�j�z��
	std::vector<std::shared_ptr<Enemy>> enemy;
	//�R�����g�e�L�X�g�i�[�z��
	std::unordered_map<Enemy::ComentType, std::vector<std::string>>comentText;
	//�R�����g�ő吶����
	int maxSpawnNum;
	//�R�����g�t�H���g
	int comentFont;
	//laught�R�����g�𐶐����闐���l�͈̔�
	int laughtLengthNum;
	//�R�����g�����Ԋu����
	int spawnInterval;
	//�w�i����n���h��
	int movieHandle;
	//�����A�j���[�V�����摜
	int exprosionImage[10];
	//�o���A�R�����g�����݂��Ă��邩�̃t���O
	bool isSpawnBaria;
	//�q�b�gSE
	int seHit;
	//����SE
	int seExprosion;
	//��SE
	int seHeal;
	//��ʏƓx�l
	int brightValue;
public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	// �n�C�X�R�A�ǂݍ��ݏ���
	void ReadHighTime();
	// �����蔻��
	bool IsHitCheck(Player* p, std::shared_ptr<Enemy> e);
	//�R�����g�e�L�X�g�ݒ�֐�
	void SetComentText();
	//�R�����g�ݒ�֐�
	std::string SetComent(Enemy::ComentType type);
	//�R�����g�����֐�
	void SpawnCooment(int time);
};