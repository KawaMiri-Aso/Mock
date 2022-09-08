#include "Enemy.h"
#include "../Map/Map.h"
#include "../Common.h"

CEnemy::CEnemy()
{
	is_active_ = false;
	hp_ = 0;
	pos_ = { 0 };
	rot_ = { 0 };
	move_ = { 0 };
	rad_ = 0.0f;
}

CEnemy::~CEnemy()
{
}

void CEnemy::HitMap()
{
	//èÌÇ…èdóÕÇÇ©ÇØÇÈ
	pos_.y -= GRAVITY;

	VECTOR vVec;
	vVec = g_map.HitCheck(pos_, rad_);
	pos_ = VAdd(pos_, vVec);
}