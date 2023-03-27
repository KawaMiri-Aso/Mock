#include "NormalEnemy.h"
#include "../Common.h"
//#include "../Player/PlayerManager.h"
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
	//モデルの読み込み
	handle_ = MV1LoadModel("Data/Model/Enemy/Goblin.x");
	//モデルのスケール設定
	MV1SetScale(handle_, VGet(0.25f, 0.25f, 0.25f));

	// アニメの再生
	m_animIdx[ANIM_MAIN] = MV1AttachAnim(handle_, EN_WALK);
	m_animCount[ANIM_MAIN] = 0.0f;
	m_animSpeed[ANIM_MAIN] = ANIM_SPD;
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
		/*if (HitCheckEnemyToPlayer(player, enemy))
		{
			StepHitBack();
		}
		else */
		/*if (HitCheckEnemyToPlayerAttack(player, enemy))
		{
			StepHitBack();
		}*/

		//移動処理
		pos_ = MyMath::VecAdd(pos_, move_);

		//アニメ更新
		AnimUpdate();

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
	DrawSphere3D(pos_, 10.0f, 4, GetColor(255, 255, 0), GetColor(255, 255, 0), FALSE);
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
	case CAIBase::ENEMY_AI_STATE_IDLE:		//待機状態更新
		StepIdle();
		break;
	case CAIBase::ENEMY_AI_STATE_ATTACK:	//攻撃状態更新
		StepAttack();
		break;
	case CAIBase::ENEMY_AI_STATE_HITBACK:	//のけぞり
		StepHitBack();
		break;
	case CAIBase::ENEMY_AI_STATE_DEAD:		//死亡
		StepDead();
		break;
	}

}

//状態：歩き
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

	Request(EN_WALK, ANIM_SPD);
}

//状態：攻撃
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

	//トーテムに着いた時点で攻撃
	//移動を止める
	move_.x = 0.0f;
	move_.z = 0.0f;

	Request(EN_ATTACK, ANIM_SPD);

	if (timer_ >= ATTACK_TIME)
	{
		g_totem.Damage(DAMAGE);
		timer_ = 0.0f;
	}

	timer_ += Comn::GetGameDeltaFrame();
}

//状態：のけぞり
void CNormalEnemy::StepHitBack()
{
	Request(EN_HIT_BACK, ANIM_SPD);
}

//状態：死亡
void CNormalEnemy::StepDead()
{
	Request(EN_DEAD, ANIM_SPD);
}

//アニメーションリクエスト
void CNormalEnemy::Request(int animID, float animSpd)
{
	// 同じアニメは無視
	if (m_animType == animID) return;

	// とりあえず2つ以上は無理、すでに2つ再生中は1つ消す
	if (m_animIdx[ANIM_SUB] != -1)
	{
		MV1DetachAnim(handle_, m_animIdx[ANIM_SUB]);
		m_animIdx[ANIM_SUB] = -1;
	}
	// メイン再生のアニメ情報をサブに移動
	m_animIdx[ANIM_SUB] = m_animIdx[ANIM_MAIN];
	m_animCount[ANIM_SUB] = m_animCount[ANIM_MAIN];
	m_animSpeed[ANIM_SUB] = m_animSpeed[ANIM_MAIN];

	// その後新しくアタッチしなおす
	m_animIdx[ANIM_MAIN] = MV1AttachAnim(handle_, animID);
	// メインアニメは設定しなおし
	m_animSpeed[ANIM_MAIN] = animSpd;
	m_animCount[ANIM_MAIN] = 0;

	m_animRate = 1.f;		// レート設定しなおし
	m_animType = animID;
}

//アニメ更新
void CNormalEnemy::AnimUpdate()
{
	// レートの更新======================================================
	if (m_animRate > 0.0f)
	{
		m_animRate -= CHANGE_SPD;
		// レートが0を下回ったら古い方のアニメーションを削除
		if (m_animRate < 0.0f)
		{
			MV1DetachAnim(handle_, m_animIdx[ANIM_SUB]);
			m_animIdx[ANIM_SUB] = -1;
		}
	}
	// ==================================================================

	// アニメーション更新
	for (int i = 0; i < BLEND_NUM; i++)
	{
		if (m_animIdx[i] == -1) continue;
		m_animCount[i] += m_animSpeed[i];

		// アニメが最後まで進んだら最初へ
		if (MV1GetAnimTotalTime(handle_, m_animIdx[i]) < m_animCount[i])
		{
			m_animCount[i] = 0.0f;
		}

		// 時間更新
		MV1SetAttachAnimTime(handle_, m_animIdx[i], m_animCount[i]);
		// レートを設定する
		float rate = i == ANIM_MAIN ? 1.0f - m_animRate : m_animRate;
		MV1SetAttachAnimBlendRate(handle_, m_animIdx[i], rate);
	}

	// 座標更新
	MV1SetPosition(handle_, pos_);
}