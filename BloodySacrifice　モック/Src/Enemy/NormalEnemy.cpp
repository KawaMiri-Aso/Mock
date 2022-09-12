#include "NormalEnemy.h"
#include "../Common.h"
#include "../Player/PlayerManager.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Trap/Stone.h"
#include "../Collision/Collision.h"

namespace {
	int NORMAL_ENEMY_HP = 10;
	float NORMAL_ENEMY_RAD = 3.0f;
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
	is_active_ = true;
	hp_ = NORMAL_ENEMY_HP;
	rad_ = NORMAL_ENEMY_RAD;
	is_hit_stonetrap = false;
}

void CNormalEnemy::Load()
{
	handle_ = MV1LoadModel("Data/Model/Enemy/enemy-mock.x");
}

void CNormalEnemy::Step()
{
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