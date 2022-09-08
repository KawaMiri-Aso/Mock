#include "NormalEnemy.h"
#include "../Common.h"
#include "../Player/PlayerManager.h"
#include "../MyMath/MyMath.h"

namespace {
	int NORMAL_ENEMY_HP = 10;

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
}

void CNormalEnemy::Init(VECTOR pos, VECTOR rot)
{

}

void CNormalEnemy::Load()
{

}

void CNormalEnemy::Step()
{

}

void CNormalEnemy::Draw()
{

}

void CNormalEnemy::Delete()
{

}

void CNormalEnemy::Fin()
{

}

CEnemy* CNormalEnemy::Clone()
{

}