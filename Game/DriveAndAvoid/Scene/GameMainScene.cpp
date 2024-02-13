#include "GameMainScene.h"
#include "../Object//RankingData.h"
#include "DxLib.h"
#include <math.h>
#include <fstream>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), barrier_image(NULL), mileage(0), player(nullptr)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{
}

// ����������
void GameMainScene::Initialize()
{
	FPSCount = 0;
	starttime = 0;
	/*Hp_width = 200;
	Hp = 100;
	MaxHp = 100;
	HpGauge = 0;*/
	// �����_��ǂݍ���
	ReadHighScore();

	// �摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/back.bmp");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);
	// �G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmp������܂���\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmp������܂���\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/images/barrier������܂���\n");
	}

	// �I�u�W�F�N�g�̐���
	player = new Player;

	// �I�u�W�F�N�g�̏�����
	player->Initialize();

	//�R�����g�ǂݍ���
	SetComentText();
}

// �X�V����
eSceneType GameMainScene::Update()
{
	FPSCount++;
	if (FPSCount == 60)
	{
		FPSCount = 0;
		starttime++;
	}
	// �v���C���[�̍X�V
	player->Update();

	// �ړ������̍X�V
	mileage += (int)player->GetSpeed() + 5;

	// �G��������
	if (mileage / 5 % 100 == 0)
	{
		Enemy::ComentType type = Enemy::ComentType::LAUGTH;
		enemy.emplace_back(std::make_shared<Enemy>(enemy_image, type, SetComent(type)));
	}

	// �G�̍X�V�Ɠ����蔻��`�F�b�N
	int i = 0;
	for (auto& e : enemy)
	{
		if (e != nullptr)
		{
			e->Update(player->GetSpeed());

			// ��ʊO�ɍs������G���폜���ăX�R�A���Z
			if (e->GetLocation().x + e->GetBoxSize().x <= 0.0f)
			{
				//enemy_count[e->GetType()]++;
				enemy.erase(enemy.begin() + i);
				e = nullptr;
				continue;
			}

			// �����蔻��̊m�F
			if (IsHitCheck(player, enemy.at(i)))
			{
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				e->Finalize();
				if (e == nullptr)
				{
					enemy.erase(enemy.begin() + i);
				}
			}
		}
		i++;
	}

	//HpGauge = Hp_width * Hp / MaxHp;


	// �v���C���[�̔R�����̗͂��O�����Ȃ烊�U���g�ɑJ�ڂ���
	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}

	return GetNowScene();
}

// �`�揈��
void GameMainScene::Draw() const
{
	// �w�i�摜�̕`��
	/*DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);*/

	// �G�̕`��
	for (auto& e : enemy)
	{
		if (e != nullptr)
		{
			e->Draw();
		}
	}

	//�v���C���[�̕`��
	player->Draw();

	//UI�̕`��
	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	DrawBox(0, 0, 1500, 100, GetColor(100, 200, 255), TRUE);
	//DrawBox(50, 50, 50 + HpGauge, 70, GetColor(0, 255, 0), true);
	SetFontSize(20);
	DrawFormatString(1100, 10, GetColor(255, 0, 200), "�n�C�X�R�A");
	DrawFormatString(1110, 50, GetColor(255, 255, 255), "%08d", high_score);
	DrawFormatString(520, 10, GetColor(0, 0, 0), "��������");
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(520 + (i * 50), 60, 0.3, 0, enemy_image[i], TRUE, FALSE);
		DrawFormatString(500+ (i * 50), 80, GetColor(255, 255, 255), "%03d", enemy_count[i]);
	}
	DrawFormatString(250, 10, GetColor(0, 0, 255), "���s����");
	DrawFormatString(250, 50, GetColor(255, 255, 255), "%08d", mileage / 10);
	DrawFormatString(380, 10, GetColor(255, 0, 0), "�X�s�[�h");
	DrawFormatString(380, 50, GetColor(255, 255, 255), "%08.1f", player->GetSpeed());

	DrawFormatString(100, 10, GetColor(255, 255, 255), "�o�ߎ���");
	DrawFormatString(130, 50, GetColor(255, 255, 255), "%d",starttime);

	// �o���A�����̕`��
	for (int i = 0; i < player->GetBarriarCount(); i++)
	{
		DrawRotaGraph(1000 + i * 25, 50, 0.2f, 0, barrier_image, TRUE, FALSE);
	}

	// �R���Q�[�W�̕`��
	float fx = 700.0f;
	float fy = 30.0f;
	DrawFormatString(fx, fy - 10, GetColor(0, 0, 255), "FUEL METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy + 50.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 50.0f, GetColor(0, 0, 0), FALSE);

	// �̗̓Q�[�W�̕`��
	fx = 850.0f;
	fy = 30.0f;
	DrawFormatStringF(fx, fy - 10, GetColor(0, 255, 0), "HP METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy + 50.0f, GetColor(0, 255, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 50.0f, GetColor(0, 0, 0), FALSE);
}

// �I��������
void GameMainScene::Finalize()
{
	// �X�R�A�����Z����
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

	// ���U���g�f�[�^�̏�������
	FILE* fp = nullptr;
	// �t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result.csv���J���܂���\n");
	}

	// �X�R�A��ۑ�
	fprintf(fp, "%d,\n", score);

	// ���s������ۑ�
	fprintf(fp, "%d,\n", mileage / 10);

	// ���������Ɠ��_��ۑ�
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	// ���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;

	//enemy�̃������J��
	enemy.clear();
	enemy.shrink_to_fit();

}

// ���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

// �n�C�X�R�A�̓ǂݍ���
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}

// �����蔻�菈���i�v���C���[�ƓG�j
bool GameMainScene::IsHitCheck(Player* p, std::shared_ptr<Enemy> e)
{
	// �v���C���[���o���A��\���Ă����瓖���蔻��𖳎�����
	if (p->IsBarrier())
	{
		return false;
	}

	// �G��񂪖�����Γ����蔻��𖳎�����
	if (e == nullptr)
	{
		return false;
	}

	// �ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	// �����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	// �R���W�����f�[�^���ʒu���̍������������Ȃ�q�b�g����Ƃ���
	return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

//�R�����g�e�L�X�g�ݒ�
void GameMainScene::SetComentText()
{
	std::vector<std::string> normalComent{ "�^�q�l","��������","���ۂ�" };
	std::vector<std::string> laughtComent{ "wwwww","��","����" };

	comentText[Enemy::ComentType::NORMAL] = normalComent;
	comentText[Enemy::ComentType::LAUGTH] = laughtComent;

}

//�R�����g����
std::string GameMainScene::SetComent(Enemy::ComentType type)
{
	std::string coment;

	int max = comentText[type].size();

	coment = comentText[type].at(GetRand(max - 1));

	return coment;
}