#include "Stone.h"
#include "../Collision/Collision.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Player/PlayerManager.h"
#include "../Common.h"

CStoneTrap g_stone_trap;

CStoneTrap::CStoneTrap()
{
	handle_ = 0;
	memset(&pos_, 0, sizeof(VECTOR));
	memset(&rot_, 0, sizeof(VECTOR));
	state_ = STONE_TRAP_STATE_BEFORE;
	app_time_ = 0.0f;
}

CStoneTrap::~CStoneTrap()
{
}

void CStoneTrap::Init()
{
	handle_ = MV1LoadModel("Data/Model/Trap/Stone/Stone.x");
	memset(&pos_, 0, sizeof(VECTOR));
	memset(&rot_, 0, sizeof(VECTOR));
	state_ = STONE_TRAP_STATE_BEFORE;
	app_time_ = 0.0f;
}

void CStoneTrap::Init(VECTOR pos)
{
	handle_ = MV1LoadModel("Data/Model/Trap/Stone/Stone.x");
	pos_ = pos;
	state_ = STONE_TRAP_STATE_BEFORE;
	app_time_ = 0.0f;
}

void CStoneTrap::Step()
{
	//常に重力をかける
	pos_.y -= GRAVITY_STONE;
	
	VECTOR vVec;
	vVec = g_map.HitCheck(pos_, STONE_RAD);
	pos_ = VAdd(pos_, vVec);

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	//まだ罠を作動してないなら
	if (state_ == STONE_TRAP_STATE_BEFORE)
	{
		//床との接地面を計算
		float bottom = pos_.y - STONE_RAD;
		//崖上にあるなら
		if (bottom > 0)
		{
			//プレイヤーと当たり判定とる
			if (CCollision::IsHitSphere(pos_, STONE_RAD, player->GetPos(), PLAYER_W * 0.5f))
			{
				//プレイヤーが押す方向に押し出す
				pos_ = MyMath::VecAdd(pos_, player->GetSpeed());
			}
		}
		else
		{
			//崖下にいったら作動フラグをたてる
			state_ = STONE_TRAP_STATE_AFTER;
			app_time_ = 0.0f;
		}
	}
	
	//岩落としが作動したら
	if (state_ == STONE_TRAP_STATE_AFTER)
	{
		app_time_ += 1.0f / FRAME_RATE;

		//出現時間を超えたら
		if (app_time_ >= STONE_APP_TIME)
		{
			//消滅状態にする
			state_ = STONE_TRAP_STATE_OUT;
			MV1DeleteModel(handle_);
		}
	}
	

	//座標設定 =====

	MV1SetPosition(handle_, pos_);
}

void CStoneTrap::Draw()
{
	//消滅状態でなかったら描画する
	if (state_ != STONE_TRAP_STATE_OUT)
	{
		MV1DrawModel(handle_);
	}
}

void CStoneTrap::Fin()
{
	MV1DeleteModel(handle_);
}
