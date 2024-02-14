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
	movieHandle = LoadGraph("Resource/movies/sm43358357.mp4");
	PlayMovieToGraph(movieHandle);

}

GameMainScene::~GameMainScene()
{
}

// 初期化処理
void GameMainScene::Initialize()
{
	FPSCount = 0;
	starttime = 0;
	spawnInterval = 10;
	/*Hp_width = 200;
	Hp = 100;
	MaxHp = 100;
	HpGauge = 0;*/
	// 高得点を読み込む
	ReadHighTime();

	// 画像の読み込み
	barrier_image = LoadGraph("Resource/images/barrier.png");
	LoadDivGraph("Resource/images/exprosion.png", 10, 10, 1, 108, 108, exprosionImage);
	
	// エラーチェック
	if (barrier_image == -1)
	{
		throw("Resource/images/barrierがありません\n");
	}

	// オブジェクトの生成
	player = new Player;

	// オブジェクトの初期化
	player->Initialize();

	//コメント読み込み
	SetComentText();

	comentFont = CreateFontToHandle("UD デジタル 教科書体 N-B", 20, 10, DX_FONTTYPE_ANTIALIASING_8X8);;
	isSpawnBaria = false;
}

// 更新処理
eSceneType GameMainScene::Update()
{
	FPSCount++;
	if (FPSCount == 60)
	{
		FPSCount = 0;
		starttime++;
		//３０秒ごとにコメント生成間隔を早くする
		if (starttime % 20 == 0 && spawnInterval != 1)
		{
			spawnInterval--;
		}
	}
	// プレイヤーの更新
	player->Update();

	// 移動距離の更新
	mileage += (int)player->GetSpeed() + 5;

	// 敵生成処理
	if (FPSCount % spawnInterval == 0 && enemy.size()<10)
	{
		SpawnCooment(starttime);
	}
	// 敵の更新と当たり判定チェック
	int i = 0;
	for (auto& e : enemy)
	{
		if (e != nullptr)
		{
			e->Update();


			//爆破アニメーションが終了してから削除
			if (e->GetType() == Enemy::ComentType::LAUGTH && e->GetExprosionState() == Enemy::ExprosionState::FINISH)
			{
				enemy.erase(enemy.begin() + i);
				continue;
			}

			// 当たり判定の確認
			if (IsHitCheck(player,e))
			{
				player->SetActive(false);

				Enemy::ComentType type = e->GetType();

				//コメントの種類に応じて処理を変更
				switch (type)
				{
				case Enemy::ComentType::NORMAL:
					player->DecreaseHp(-50.0f);
					break;
				case Enemy::ComentType::LAUGTH:
					player->DecreaseHp(-150.0f);
					e->Explosion();
					break;
				case Enemy::ComentType::HEAL_HP:
					player->DecreaseHp(100);
					break;
				case Enemy::ComentType::HEAL_BARRIER:
					player->AddBarriarCount();
					isSpawnBaria = false;
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

			// 画面外に行ったら敵を削除
			if (e->GetLocation().x + e->GetBoxSize().x <= 0.0f)
			{
				enemy.erase(enemy.begin() + i);
				continue;
			}

		}
		else
		{
			enemy.erase(enemy.begin() + i);
			continue;
		}
		i++;
	}

	//HpGauge = Hp_width * Hp / MaxHp;


	// プレイヤーの体力が０未満ならリザルトに遷移する
	if (player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}

	//動画ループ処理
	if (GetMovieStateToGraph(movieHandle) != 1)
	{
		SeekMovieToGraph(movieHandle, 0);
		PlayMovieToGraph(movieHandle);
	}

	return GetNowScene();
}

// 描画処理
void GameMainScene::Draw() const
{
	DrawGraph(0, 0, movieHandle, FALSE);
	// 背景画像の描画
	/*DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);*/

	 //敵の描画
	for (auto& e : enemy)
	{
		if (e != nullptr)
		{
			e->Draw();
		}
	}

	//プレイヤーの描画
	player->Draw();

	//UIの描画
	DrawBox(0, 0, 700, 100, GetColor(100, 200, 255), TRUE);
	//DrawBox(50, 50, 50 + HpGauge, 70, GetColor(0, 255, 0), true);
	SetFontSize(20);
	DrawFormatString(50, 10, GetColor(255, 255, 255), "経過時間");
	DrawFormatString(80, 50, GetColor(255, 255, 255), "%d", starttime);

	DrawFormatString(180, 10, GetColor(255, 0, 0), "走行距離");
	DrawFormatString(180, 50, GetColor(255, 255, 255), "%08d", mileage / 10);
	

	DrawFormatString(300, 10, GetColor(0, 0, 255), "残りのバリア");

	// バリア枚数の描画
	for (int i = 0; i < player->GetBarriarCount(); i++)
	{
		DrawRotaGraph(320 + i * 25, 60, 0.2f, 0, barrier_image, TRUE, FALSE);
	}

	

	// 体力ゲージの描画
	float fx = 450.0f;
	float fy = 30.0f;
	DrawFormatStringF(fx, fy - 10, GetColor(0, 255, 0), "HP METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 200 / 1000), fy + 50.0f, GetColor(0, 255, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 200.0f, fy + 50.0f, GetColor(0, 0, 0), FALSE);

}

// 終了時処理
void GameMainScene::Finalize()
{
	// スコアを加算する
	int time = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		time += (i + 1) * 50 * enemy_count[i];
	}

	// リザルトデータの書き込み
	FILE* fp = nullptr;
	// ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result.csvが開けません\n");
	}

	// スコアを保存
	//fprintf(fp, "%d,\n", time);

	// 走行距離を保存
	//fprintf(fp, "%d,\n", mileage / 10);

	// 経過時間を保存
	fprintf(fp, "%d,\n", starttime);

	// 避けた数と得点を保存
	//for (int i = 0; i < 3; i++)
	//{
	//	fprintf(fp, "%d,\n", enemy_count[i]);
	//}

	// ファイルクローズ
	fclose(fp);

	// 動的確保したオブジェクトを削除する
	player->Finalize();
	delete player;

	//enemyのメモリ開放
	enemy.clear();
	enemy.shrink_to_fit();

	InitGraph();
	DeleteFontToHandle(comentFont);
}

// 現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

// ハイスコアの読み込み
void GameMainScene::ReadHighTime()
{
	RankingData data;
	data.Initialize();

	high_time = data.GetTime(0);

	data.Finalize();
}

// 当たり判定処理（プレイヤーと敵）
bool GameMainScene::IsHitCheck(Player* p, std::shared_ptr<Enemy> e)
{
	// プレイヤーがバリアを貼っていたら当たり判定を無視する
	if (p->IsBarrier())
	{
		return false;
	}

	// 敵情報が無ければ当たり判定を無視する
	if (e == nullptr)
	{
		return false;
	}

	// 位置情報の差分を取得
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	// 当たり判定サイズの大きさを取得
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	// コリジョンデータより位置情報の差分が小さいならヒット判定とする
	return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

	
}

//コメントテキスト設定
void GameMainScene::SetComentText()
{
	std::vector<std::string> normalComent{ "タヒネ","きっしょ","〇す","56す"};
	std::vector<std::string> laughtComent{ "ｗｗｗｗ","草","爆笑" };
	std::vector<std::string> healComent{ "ここすき"};
	std::vector<std::string> bariaComent{ "バリア" };

	comentText[Enemy::ComentType::NORMAL] = normalComent;
	comentText[Enemy::ComentType::LAUGTH] = laughtComent;
	comentText[Enemy::ComentType::HEAL_HP] = healComent;
	comentText[Enemy::ComentType::HEAL_BARRIER] = bariaComent;

}

//コメント決定
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

	if (time % 20 == 0)
	{
		laughtLengthNum++;
	}

	//乱数生成
	std::random_device rnd;
	std::mt19937 mt(rnd());

	 std::uniform_int_distribution<> randNum(1, 10);

	if (randNum(mt) <= laughtLengthNum)
	{
		type = Enemy::ComentType::LAUGTH;
	}

	//5%の確立で回復コメント生成
	std::uniform_int_distribution<> healProbability(1, 20);
	if (healProbability(mt) == 20)
	{
		type = Enemy::ComentType::HEAL_HP;
	}

	//４０秒ごとにバリア回復コメント生成
	if (time % 40 == 0 && time != 0 && isSpawnBaria == false)
	{
		type = Enemy::ComentType::HEAL_BARRIER;
		isSpawnBaria = true;
	}

	enemy.emplace_back(std::make_shared<Enemy>(exprosionImage, type, SetComent(type),comentFont));
}
