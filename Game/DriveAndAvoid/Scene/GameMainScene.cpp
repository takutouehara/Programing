#include "GameMainScene.h"
#include "../Object//RankingData.h"
#include "DxLib.h"
#include <math.h>
#include <random>

GameMainScene::GameMainScene() :high_time(0), barrier_image(NULL), mileage(0), player(nullptr), starttime(0)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_count[i] = NULL;
	}
	movieHandle = LoadGraph("Resource/movies/nekomeme.mp4");
	PlayMovieToGraph(movieHandle);
	ChangeMovieVolumeToGraph(100, movieHandle);
}

GameMainScene::~GameMainScene()
{
}

// ����������
void GameMainScene::Initialize()
{
	FPSCount = 0;
	starttime = 0;
	spawnInterval = 10;
	/*Hp_width = 200;
	Hp = 100;
	MaxHp = 100;
	HpGauge = 0;*/
	// �����_��ǂݍ���
	ReadHighTime();

	// �摜�̓ǂݍ���
	barrier_image = LoadGraph("Resource/images/barrier.png");
	LoadDivGraph("Resource/images/exprosion.png", 10, 10, 1, 108, 108, exprosionImage);
	
	// �G���[�`�F�b�N
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
	maxSpawnNum = 30;
	laughtLengthNum = 2;
	comentFont = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 20, 10, DX_FONTTYPE_ANTIALIASING_8X8);;
	isSpawnBaria = false;
	seHit = LoadSoundMem("Resource/sound/damaged2.mp3");
	seExprosion = LoadSoundMem("Resource/sound/mini_bomb1.mp3");
	seHeal = LoadSoundMem("Resource/sound/heal.mp3");
	ChangeVolumeSoundMem(100, seHit);
	ChangeVolumeSoundMem(100, seExprosion);
	ChangeVolumeSoundMem(100, seHeal);
	brightValue = 255;
}

// �X�V����
eSceneType GameMainScene::Update()
{
	if (player->GetActive() == true)
	{
		FPSCount++;
	}
	if (FPSCount == 60)
	{
		FPSCount = 0;
		starttime++;
		//20�b���Ƃɏ΂��R�����g�̏o���m�����グ,
		//�ő�o�������グ��
		if (starttime % 20 == 0 && laughtLengthNum < 10)
		{
			laughtLengthNum++;
		}
		//10�b���ƂɃR�����g�����Ԋu�𑁂����A�ő吔�𑝂₷
		if (starttime % 10 == 0 && 1 < spawnInterval)
		{
			spawnInterval--;
			maxSpawnNum += 20;
		}
	}
	// �v���C���[�̍X�V
	player->Update();
	
	// �ړ������̍X�V
	mileage += (int)player->GetSpeed() + 5;

	// �G��������
	if (FPSCount % spawnInterval == 0 && enemy.size() < maxSpawnNum)
	{
		SpawnCooment(starttime);
	}
	// �G�̍X�V�Ɠ����蔻��`�F�b�N
	int i = 0;
	for (auto& e : enemy)
	{
		if (e != nullptr)
		{
			e->Update();


			//���j�A�j���[�V�������I�����Ă���폜
			if (e->GetType() == Enemy::ComentType::LAUGTH && e->GetExprosionState() == Enemy::ExprosionState::FINISH)
			{
				enemy.erase(enemy.begin() + i);
				continue;
			}

			// �����蔻��̊m�F
			if (IsHitCheck(player,e) && player->GetActive() == true && player->GetHitFlg() == false)
			{
				//player->SetActive(false);

				Enemy::ComentType type = e->GetType();

				//�R�����g�̎�ނɉ����ď�����ύX
				switch (type)
				{
				case Enemy::ComentType::NORMAL:
					if (player->GetHitFlg() == false) {
						player->DecreaseHp(-100.0f);
						player->SetActive(false);
						player->SetHitFlg(true);
						PlaySoundMem(seHit, DX_PLAYTYPE_BACK, TRUE);
					}
					break;
				case Enemy::ComentType::LAUGTH:
					if (player->GetHitFlg() == false) {
						player->DecreaseHp(-200.0f);
						player->SetActive(false);
						player->SetHitFlg(true);
						e->Explosion();
						PlaySoundMem(seExprosion, DX_PLAYTYPE_BACK, TRUE);
					}
					break;
				case Enemy::ComentType::HEAL_HP:
					player->DecreaseHp(150);
					PlaySoundMem(seHeal, DX_PLAYTYPE_BACK, TRUE);
					break;
				case Enemy::ComentType::HEAL_BARRIER:
					player->AddBarriarCount();
					isSpawnBaria = false;
					PlaySoundMem(seHeal, DX_PLAYTYPE_BACK, TRUE);
					break;
				default:
					break;
				}

				

				if (e->GetType() != Enemy::ComentType::LAUGTH)
				{
					enemy.erase(enemy.begin() + i);
					continue;
				}
				i++;
				continue;
			}

			// ��ʊO�ɍs������G���폜
			if (e->GetLocation().x + e->GetBoxSize().x <= 0.0f)
			{
				enemy.erase(enemy.begin() + i);
				continue;
			}

		}
		i++;
	}

	//HpGauge = Hp_width * Hp / MaxHp;


	// �v���C���[�̗̑͂��O�����Ȃ烊�U���g�ɑJ�ڂ���
	if (player->GetHp() <= 0.0f)
	{
		//���񂾂�Â�����
		brightValue--;
		SetDrawBright(brightValue, brightValue, brightValue);
		if (brightValue <= 100)
		{
			return eSceneType::E_RESULT;
		}
	}

	//���惋�[�v����
	if (GetMovieStateToGraph(movieHandle) != 1)
	{
		SeekMovieToGraph(movieHandle, 0);
		PlayMovieToGraph(movieHandle);
	}

	return GetNowScene();
}

// �`�揈��
void GameMainScene::Draw() const
{
	DrawGraph(0, 0, movieHandle, FALSE);
	// �w�i�摜�̕`��
	/*DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);*/

	 //�G�̕`��
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
	DrawBox(0, 0, 1280, 100, GetColor(100, 200, 255), TRUE);
	//DrawBox(50, 50, 50 + HpGauge, 70, GetColor(0, 255, 0), true);
	SetFontSize(20);
	DrawFormatString(50, 10, GetColor(255, 255, 255), "�o�ߎ���");
	DrawFormatString(80, 50, GetColor(255, 255, 255), "%d", starttime);

	

	DrawFormatString(200, 10, GetColor(0, 0, 255), "�c��̃o���A");

	// �o���A�����̕`��
	for (int i = 0; i < player->GetBarriarCount(); i++)
	{
		DrawRotaGraph(220 + i * 25, 60, 0.2f, 0, barrier_image, TRUE, FALSE);
	}

	

	// �̗̓Q�[�W�̕`��
	float fx = 350.0f;
	float fy = 30.0f;
	DrawFormatStringF(fx, fy - 5, GetColor(0, 0, 0), "HP");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 200 / 1000), fy + 50.0f, GetColor(0, 255, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 200.0f, fy + 50.0f, GetColor(0, 0, 0), FALSE);

}

// �I��������
void GameMainScene::Finalize()
{
	// �X�R�A�����Z����
	int time = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		time += (i + 1) * 50 * enemy_count[i];
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
	//fprintf(fp, "%d,\n", time);

	// ���s������ۑ�
	//fprintf(fp, "%d,\n", mileage / 10);

	// �o�ߎ��Ԃ�ۑ�
	fprintf(fp, "%d,\n", starttime);

	// ���������Ɠ��_��ۑ�
	//for (int i = 0; i < 3; i++)
	//{
	//	fprintf(fp, "%d,\n", enemy_count[i]);
	//}

	// �t�@�C���N���[�Y
	fclose(fp);

	// ���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;

	//enemy�̃������J��
	enemy.clear();
	enemy.shrink_to_fit();

	InitGraph();
	InitSoundMem();
	DeleteFontToHandle(comentFont);
}

// ���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

// �n�C�X�R�A�̓ǂݍ���
void GameMainScene::ReadHighTime()
{
	RankingData data;
	data.Initialize();

	high_time = data.GetTime(0);

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
	Vector2D e_location = e->GetLocation();
	e_location.x += e->GetBoxSize().x / 2;
	e_location.y += e->GetBoxSize().y / 2;
	Vector2D diff_location = p->GetLocation() - e_location;

	// �����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + (e->GetBoxSize() / 2);

	// �R���W�����f�[�^���ʒu���̍������������Ȃ�q�b�g����Ƃ���
	return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	
}

//�R�����g�e�L�X�g�ݒ�
void GameMainScene::SetComentText()
{
	std::vector<std::string> normalComent{ "�^�q�l","��������","�Z��","56��","�A�܂��","���A����",
											"��������������������","�Ԃ���"};
	std::vector<std::string> laughtComent{ "��������","��","����","������","��������������������","�呐���s��" };
	std::vector<std::string> healComent{ "��������","�l�\","��������" };
	std::vector<std::string> bariaComent{ "�o���A" };

	comentText[Enemy::ComentType::NORMAL] = normalComent;
	comentText[Enemy::ComentType::LAUGTH] = laughtComent;
	comentText[Enemy::ComentType::HEAL_HP] = healComent;
	comentText[Enemy::ComentType::HEAL_BARRIER] = bariaComent;

}

//�R�����g����
std::string GameMainScene::SetComent(Enemy::ComentType type)
{
	std::string coment;

	int max = comentText[type].size();

	coment = comentText[type].at(GetRand(max - 1));

	return coment;
}

void GameMainScene::SpawnCooment(int time)
{
	Enemy::ComentType type = Enemy::ComentType::NORMAL;

	//��������
	std::random_device rnd;
	std::mt19937 mt(rnd());

	 std::uniform_int_distribution<> randNum(1, 10);

	if (randNum(mt) <= laughtLengthNum)
	{
		type = Enemy::ComentType::LAUGTH;
	}

	//5%�̊m���ŉ񕜃R�����g����
	std::uniform_int_distribution<> healProbability(1, 20);
	if (healProbability(mt) == 20)
	{
		type = Enemy::ComentType::HEAL_HP;
	}

	//�S�O�b���ƂɃo���A�񕜃R�����g����
	if (time % 40 == 0 && time != 0 && isSpawnBaria == false)
	{
		type = Enemy::ComentType::HEAL_BARRIER;
		isSpawnBaria = true;
	}

	enemy.emplace_back(std::make_shared<Enemy>(exprosionImage, type, SetComent(type),comentFont));
}
