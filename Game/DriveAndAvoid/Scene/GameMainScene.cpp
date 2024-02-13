#include "GameMainScene.h"
#include "../Object//RankingData.h"
#include "DxLib.h"
#include <math.h>
#include <random>

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
	ReadHighScore();

	// 画像の読み込み
	back_ground = LoadGraph("Resource/images/back.bmp");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);
	// エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmpがありません\n");
	}
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

	clsDx();
	printfDx("%d", enemy.size());

	// 移動距離の更新
	mileage += (int)player->GetSpeed() + 5;

	// 敵生成処理
	if (FPSCount % spawnInterval == 0)
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

			// 画面外に行ったら敵を削除してスコア加算
			if (e->GetLocation().x + e->GetBoxSize().x <= 0.0f)
			{
				//enemy_count[e->GetType()]++;
				enemy.erase(enemy.begin() + i);
				e = nullptr;
				i++;
				continue;
			}

			// 当たり判定の確認
			if (IsHitCheck(player, enemy.at(i)))
			{
				player->SetActive(false);
				//player->DecreaseHp(-50.0f);
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


	// プレイヤーの燃料か体力が０未満ならリザルトに遷移する
	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}

	return GetNowScene();
}

// 描画処理
void GameMainScene::Draw() const
{
	// 背景画像の描画
	/*DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);*/

	// 敵の描画
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
	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	//DrawBox(50, 50, 50 + HpGauge, 70, GetColor(0, 255, 0), true);
	SetFontSize(16);
	DrawFormatString(510, 20, GetColor(0, 0, 0), "ハイスコア");
	DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d", high_score);
	DrawFormatString(510, 80, GetColor(0, 0, 0), "避けた数");
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE, FALSE);
		DrawFormatString(510 + (i * 50), 140, GetColor(255, 255, 255), "%03d", enemy_count[i]);
	}
	DrawFormatString(1010, 200, GetColor(0, 0, 255), "走行距離");
	DrawFormatString(1055, 220, GetColor(255, 255, 255), "%08d", mileage / 10);
	DrawFormatString(1010, 240, GetColor(255, 0, 0), "スピード");
	DrawFormatString(1055, 260, GetColor(255, 255, 255), "%08.1f", player->GetSpeed());

	DrawFormatString(0, 0, GetColor(255, 255, 255), "経過時間:%d秒",starttime);

	// バリア枚数の描画
	for (int i = 0; i < player->GetBarriarCount(); i++)
	{
		DrawRotaGraph(1020 + i * 25, 340, 0.2f, 0, barrier_image, TRUE, FALSE);
	}

	// 燃料ゲージの描画
	float fx = 1010.0f;
	float fy = 590.0f;
	DrawFormatString(fx, fy, GetColor(0, 0, 255), "FUEL METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy + 40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	// 体力ゲージの描画
	fx = 1010.0f;
	fy = 630.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 255, 0), "HP");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy + 40.0f, GetColor(0, 255, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
}

// 終了時処理
void GameMainScene::Finalize()
{
	// スコアを加算する
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
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
	fprintf(fp, "%d,\n", score);

	// 走行距離を保存
	fprintf(fp, "%d,\n", mileage / 10);

	// 経過時間を保存
	fprintf(fp, "%d,\n", starttime);

	// 避けた数と得点を保存
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	// ファイルクローズ
	fclose(fp);

	// 動的確保したオブジェクトを削除する
	player->Finalize();
	delete player;

	//enemyのメモリ開放
	enemy.clear();
	enemy.shrink_to_fit();

}

// 現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

// ハイスコアの読み込み
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

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
	std::vector<std::string> normalComent{ "タヒネ","ここすき","うぽつ" };
	std::vector<std::string> laughtComent{ "wwwww","草","爆笑" };

	comentText[Enemy::ComentType::NORMAL] = normalComent;
	comentText[Enemy::ComentType::LAUGTH] = laughtComent;

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

	enemy.emplace_back(std::make_shared<Enemy>(enemy_image, type, SetComent(type)));
}
