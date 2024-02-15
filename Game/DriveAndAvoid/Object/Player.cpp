#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
 
#define PleyerMoveSpeed 5	//プレイヤーの移動速度

Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr),
is_HitFlg(false),FlashTime(120)
{

}

Player::~Player()
{

}

// 初期化処理
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(17.0f, 20.5f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 1000;
	fuel = 20000;
	barrier_count = 3;

	// 画像の読み込み
	image = LoadGraph("Resource/images/Player_Acter.png");

	// エラーチェック
	if (image == -1)
	{
		throw("Resource/images/Player_Acter.pngがありません\n");
	}

	//デバック用
	BoxLocation1 = Vector2D(0.0f, 0.0f);
	BoxLocation2 = Vector2D(0.0f, 0.0f);

}

// 更新処理
void Player::Update()
{
	// 操作不可状態であれば、自身を回転させる
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			angle = 0.0f;
			is_active = true;
		}
		//return;
	}

	//�_�ł����鎞�Ԃ̃J�E���g
	if (is_HitFlg == true)
	{
		FlashTime--;
		if (FlashTime < 0)
		{
			FlashTime = 120;
			is_HitFlg = false;
		}
	}
	

	// �R���̏���
	fuel -= speed;

	// 移動処理
	Movement();

	// 加減速処理
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	// バリア処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	// バリアが生成されていたら、更新を行う
	if (barrier != nullptr)
	{
		// バリア時間が経過したか　していたら、削除する
		if (barrier->IsFinished())
		{
			delete barrier;
			barrier = nullptr;
		}
	}

	//デバック用
	BoxLocation1 = location - (box_size );
	BoxLocation2 = location + (box_size );

}

// 描画処理
void Player::Draw()
{
	// �v���C���[�摜�̕`��
	if (is_HitFlg == true) {

		if (FlashTime % 20 < 10) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else {
			DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
		}

	}
	else {
		DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
	}
	
	// バリアが生成されていたら、描画を行う
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}

	//デバック用
	//DrawBoxAA(BoxLocation1.x,BoxLocation1.y, BoxLocation2.x, BoxLocation2.y,0xff0000,false );
}

// 終了時処理
void Player::Finalize()
{
	// 読み込んだ画像を削除
	DeleteGraph(image);

	// バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

// 状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

// 体力減少処理
void Player::DecreaseHp(float value)
{
	if (is_active == true && barrier == nullptr)
	{
		this->hp += value;
	}
}

// 位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

// 当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

// 速さ取得処理
float Player::GetSpeed() const
{
	return this->speed;
}

// 燃料取得処理
float Player::GetFuel() const
{
	return this->fuel;
}

// 体力取得処理
float Player::GetHp() const
{
	return this->hp;
}

// バリア枚数取得処理
int Player::GetBarriarCount() const
{
	return this->barrier_count;
}

// バリアが有効か　を処理
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

void Player::SetHitFlg(bool flg)
{
	this->is_HitFlg = flg;
}

bool Player::GetHitFlg()
{
	return this->is_HitFlg;
}

float Player::GetFlashTime() const
{
	return this->FlashTime;
}

// �ړ�����
void Player::Movement()
{
	float  stick_y = InputControl::GetLstickRadY();
	float  stick_x = InputControl::GetLstickRadX();

	Vector2D move = Vector2D(0.0f);
	

	if (stick_y != 0 || stick_x != 0) {
		move += Vector2D(stick_x * PleyerMoveSpeed, -stick_y * PleyerMoveSpeed);
	}

	location += move;

	// 画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= 1280.0f - box_size.x) || (location.y < box_size.y) || (location.y >= 720.0f - box_size.y)||(location.y <= 150.0f - box_size.y))
	{
		location -= move;
	}
}

// 加減速処理
void Player::Acceleration()
{
	// LBボタンが押されたら減速する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	// RBボタンが押されたら加速する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}


