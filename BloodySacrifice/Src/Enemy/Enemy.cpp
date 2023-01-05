#include "Enemy.h"
#include "../Map/Map.h"
#include "../Common.h"
#include "../Player/PlayerManager.h"

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

//現在位置に座標加算
void CEnemy::ReflectCollision(VECTOR addVec)
{
	// オールゼロなら何もしない
	if (addVec.x == 0.0f && addVec.y == 0.0f && addVec.z == 0.0f) return;

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR	pos = player->GetPos();
	pos = VAdd(pos, addVec);
	//m_gravity = 0.0f;
	SetPos(pos);
}

//プレイヤーの攻撃がヒットした後の処理
void CEnemy::HitCalc(VECTOR move)
{
	move_ = move;
	
}