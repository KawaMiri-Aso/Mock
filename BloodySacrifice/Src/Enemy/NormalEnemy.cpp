#include "NormalEnemy.h"
#include "../Common.h"
#include "../Player/PlayerManager.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Trap/Stone.h"
#include "../Collision/Collision.h"
#include "../AI/AINormalEnemy.h"
#include "../Totem/Totem.h"
#include <math.h>
#include "../Common/Time.h"
#include "../Enemy/EnemyManager.h"

#define DEBUG

namespace {
	int NORMAL_ENEMY_HP = 10;
	float NORMAL_ENEMY_RAD = 3.0f;
	float NORMAL_ENEMY_MOVE_SPEED = 0.25f;
	float NORMAL_ENEMY_ATTACK_RANGE = 25.0f;
	float NORMAL_ENEMY_CAUTION_RANGE = 38.0f;
	float NORMAL_ENEMY_BACK_RANGE = 58.0f;
	float DAMAGE = 5.0f;	//与えるダメージ
	float ATTACK_TIME = 60.0f;
}


CNormalEnemy::CNormalEnemy()
{
	handle_ = 0;
	timer_ = 0.0f;
}

CNormalEnemy::~CNormalEnemy()
{
	Fin();
}

void CNormalEnemy::Init()
{
	active_ = true;			//生存フラグ
	hp_ = NORMAL_ENEMY_HP;		//HP
	rad_ = NORMAL_ENEMY_RAD;	//半径
	//is_hit_stonetrap = false;	//岩と当たっているか
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

	if (IsActive())
	{
		//AI更新
		StepAI();

		//常に重力をかける
		move_.y -= GRAVITY;

		//マップとの当たり判定
		/*VECTOR vVec;
		vVec = g_map.HitCheck(pos_, rad_);
		pos_ = VAdd(pos_, vVec);*/
		HitMap();

		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		CEnemy* enemy = CEnemyManager::GetInstance()->GetEnemy();

		//プレイヤーと敵の当たり判定
		HitCheckEnemyToPlayer(player, enemy);
		HitCheckEnemyToPlayerAttack(player, enemy);

		//移動処理
		pos_ = MyMath::VecAdd(pos_, move_);

		MV1SetRotationXYZ(handle_, rot_);
		MV1SetPosition(handle_, pos_);
	}

	if (CCollision::IsHitSphere(pos_, NORMAL_ENEMY_RAD, g_totem.GetPos(), TOTEM_RAD))
	{
		pos_.x -= move_.x;
		pos_.z -= move_.z;
	}

	//if (CCollision::IsHitSphere(pos_, NORMAL_ENEMY_RAD, g_stone_trap.GetPos(), STONE_RAD))
	//{
	//	is_active_ = false;
	//}
}

void CNormalEnemy::Draw()
{
	MV1DrawModel(handle_);

#ifdef DEBUG
	DrawFormatString(10, 58, GetColor(255, 128, 0), "敵HP：%d", hp_);
#endif 
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
	//case CAIBase::ENEMY_AI_STATE_CAUTION:	//警戒状態更新
	//	StepCaution();
	//	break;
	case CAIBase::ENEMY_AI_STATE_ATTACK:	//攻撃状態更新
		StepAttack();
		break;
	//case CAIBase::ENEMY_AI_STATE_BACK:	//帰還状態更新
	//	StepBack();
	//	break;
	}
}

void CNormalEnemy::StepIdle()
{
	//トーテムに向かっていく
	VECTOR vec = MyMath::VecCreate(pos_, g_totem.GetPos());
	// y要素は0で
	vec.y = 0.0f;
	// そのベクトルを移動スピードの長さにして移動量とする
	vec = MyMath::VecNormalize(vec);
	VECTOR move_vec = MyMath::VecScale(vec, NORMAL_ENEMY_MOVE_SPEED);
	move_.x = move_vec.x;
	move_.z = move_vec.z;
	// 移動する方向を向く
	rot_.y = atan2f(-move_.x, -move_.z);

}

//void CNormalEnemy::StepCaution()
//{
//	//プレイヤーまでのベクトルを作成
//	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
//	VECTOR player_vec = MyMath::VecCreate(pos_, player->GetPos());
//	//プレイヤーの向く角度を算出してY回転値に代入
//	rot_.y = atan2f(-player_vec.x, -player_vec.z);
//	//移動を止める
//	move_.x = 0.0f;
//	move_.z = 0.0f;
//}

void CNormalEnemy::StepAttack()
{
	////プレイヤーまでのベクトルを作成
	//CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	//VECTOR player_vec = MyMath::VecCreate(pos_, player->GetPos());
	
	////トーテムに向かっていく
	//VECTOR vec = MyMath::VecCreate(pos_, g_totem.GetPos());
	////Y要素は0
	//vec.y = 0.0f;
	////向きを設定
	//rot_.y = atan2f(-vec.x, -vec.z);
	////ベクトルを移動スピードの長さにして移動量にする
	//vec = MyMath::VecNormalize(vec);
	//VECTOR move_vec = MyMath::VecScale(vec, NORMAL_ENEMY_MOVE_SPEED);
	//move_.x = move_vec.x;
	//move_.z = move_vec.z;

	//移動を止める
	move_.x = 0.0f;
	move_.z = 0.0f;

	if (timer_ >= ATTACK_TIME)
	{
		g_totem.Damage(DAMAGE);
		timer_ = 0.0f;
	}

	timer_ += Comn::GetGameDeltaFrame();
}

//void CNormalEnemy::StepBack()
//{
//	// 帰還ポイントまでのベクトルを作成
//	VECTOR back_vec = MyMath::VecCreate(pos_, back_pos_);
//	// y要素は0で
//	back_vec.y = 0.0f;
//	// そのベクトルを移動スピードの長さにして移動量とする
//	back_vec = MyMath::VecNormalize(back_vec);
//	VECTOR move_vec = MyMath::VecScale(back_vec, NORMAL_ENEMY_MOVE_SPEED);
//	move_.x = move_vec.x;
//	move_.z = move_vec.z;
//	// 移動する方向を向く
//	rot_.y = atan2f(-move_.x, -move_.z);
//}