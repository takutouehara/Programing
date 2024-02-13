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
	int high_score;		// �n�C�X�R�A
	int back_ground;	// �w�i�摜
	int barrier_image;	// �o���A�摜
	int mileage;		// ���s����
	int enemy_image[3];	// �G�摜
	int enemy_count[3];	// �ʂ�߂����G�J�E���g
	Player* player;		// �v���C���[
	
	//�G�i�R�����g�j�z��
	std::vector<std::shared_ptr<Enemy>> enemy;
	//�R�����g�e�L�X�g�i�[�z��
	std::unordered_map<Enemy::ComentType, std::vector<std::string>>comentText;
	//std::unordered_map<Enemy::ComentType, std::vector<std::string>>comentText;
	
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
	void ReadHighScore();
	// �����蔻��
	bool IsHitCheck(Player* p, std::shared_ptr<Enemy> e);
	//�R�����g�e�L�X�g�ݒ�֐�
	void SetComentText();
	//�R�����g�ݒ�֐�
	std::string SetComent(Enemy::ComentType type);
};