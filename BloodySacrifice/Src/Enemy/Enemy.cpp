#include "Enemy.h"
#include "../Map/Map.h"
#include "../Common.h"

CEnemy::CEnemy()
{
	active_ = false;
	hp_ = 0;
	pos_ = { 0 };
	rot_ = { 0 };
	move_ = { 0 };
	rad_ = 0.0f;
	/*is_hit_stonetrap = false;*/
}

CEnemy::~CEnemy()
{
}

void CEnemy::HitMap()
{
	VECTOR vVec;
	vVec = g_map.HitCheck(pos_, rad_);
	if (vVec.y > 0)
	{
		move_.y = 0.0f;
	}
	pos_ = VAdd(pos_, vVec);
}

void CEnemy::Dead()
{
	active_ = false;
}