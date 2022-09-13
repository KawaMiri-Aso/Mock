#include "NormalEnemy.h"
#include "../Common.h"
#include "../Player/PlayerManager.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Trap/Stone.h"
#include "../Collision/Collision.h"
#include "../AI/AINormalEnemy.h"
#include <math.h>

namespace {
	int NORMAL_ENEMY_HP = 10;
	float NORMAL_ENEMY_RAD = 3.0f;
	float NORMAL_ENEMY_MOVE_SPEED = 0.5f;
	float NORMAL_ENEMY_ATTACK_RANGE = 3.0f;
	float NORMAL_ENEMY_CAUTION_RANGE = 5.0f;
	float NORMAL_ENEMY_BACK_RANGE = 7.0f;
}


CNormalEnemy::CNormalEnemy()
{
	handle_ = 0;
}

CNormalEnemy::~CNormalEnemy()
{
	Fin();
}

void CNormalEnemy::Init()
{
	is_active_ = true;			//生存フラグ
	hp_ = NORMAL_ENEMY_HP;		//HP
	rad_ = NORMAL_ENEMY_RAD;	//半径
	is_hit_stonetrap = false;	//岩と当たっているか
	//AI状態遷移を設定
	enemy_ai_ = new CAINomalEnemy;
	static_cast<CAINomalEnemy*>(enemy_ai_)->Init(NORMAL_ENEMY_ATTACK_RANGE, NORMAL_ENEMY_CAUTION_RANGE, NORMAL_ENEMY_BACK_RANGE);
}

void CNormalEnemy::Load()
{
	handle_ = MV1LoadModel("Data/Model/Enemy/enemy-mock.x");
}

void CNormalEnemy::Step()
{
	//次のAIの状態を設定
	ai_state_ = enemy_ai_->GetNextState(this);
	//AI更新
	StepAI();

	if (IsActive())
	{
		//常に重力をかける
		move_.y -= GRAVITY;

		//マップとの当たり判定
		VECTOR vVec;
		vVec = g_map.HitCheck(pos_, rad_);
		pos_ = VAdd(pos_, vVec);

		MV1SetRotationXYZ(handle_, rot_);
		MV1SetPosition(handle_, pos_);
	}

	if (CCollision::IsHitSphere(pos_, NORMAL_ENEMY_RAD, g_stone_trap.GetPos(), STONE_RAD))
	{
		is_active_ = false;
	}
}

void CNormalEnemy::Draw()
{
	MV1DrawModel(handle_);
}

void CNormalEnemy::Delete()
{
	MV1DeleteModel(handle_);
}

void CNormalEnemy::Fin()
{
	Delete();
}

CEnemy* CNormalEnemy::Clone()
{
	CNormalEnemy* clone =  new CNormalEnemy;
	*clone = *this;
	clone->handle_ = MV1DuplicateModel(handle_);
	return clone;
}

void CNormalEnemy::StepAI()
{
	//現在の状態から各AI処理へ
	switch (ai_state_)
	{
	case CAIBase::ENEMY_AI_STATE_IDLE:	//待機状態更新
		StepIdle();
		break;
	case CAIBase::ENEMY_AI_STATE_CAUTION:	//待機状態更新
		StepCaution();
		break;
	case CAIBase::ENEMY_AI_STATE_ATTACK:	//待機状態更新
		StepAttack();
		break;
	case CAIBase::ENEMY_AI_STATE_BACK:	//待機状態更新
		StepBack();
		break;
	}
}

void CNormalEnemy::StepIdle()
{
	//後でウロウロさせる
	//ひとまず移動しない
	move_.x = 0.0f;
	move_.z = 0.0f;
}

void CNormalEnemy::StepCaution()
{
	//プレイヤーまでのベクトルを作成
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR player_vec = MyMath::VecCreate(pos_, player->GetPos());
	//プレイヤーの向く角度を算出してY回転値に代入
	rot_.y = atan2f(player_vec.x, player_vec.z);
	//移動を止める
	move_.x = 0.0f;
	move_.z = 0.0f;
}

void CNormalEnemy::StepAttack()
{
	//プレイヤーまでのベクトルを作成
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR player_vec = MyMath::VecCreate(pos_, player->GetPos());
	//Y要素は0
	player_vec.y = 0.0f;
	//向きを設定
	rot_.y = atan2f(player_vec.x, player_vec.z);
	//ベクトルを移動スピードの長さにして移動量にする
	player_vec = MyMath::VecNormalize(player_vec);
	VECTOR move_vec = MyMath::VecScale(player_vec, NORMAL_ENEMY_MOVE_SPEED);
	move_.x = move_vec.x;
	move_.z = move_vec.z;
}

void CNormalEnemy::StepBack()
{

}