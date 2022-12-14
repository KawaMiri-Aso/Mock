#include "Enemy.h"
#include "../Map/Map.h"
#include "../Common.h"
#include "../MyMath/MyMath.h"

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

//プレイヤーと敵の当たり判定
void CEnemy::HitCheckEnemyToPlayer(CPlayer* player, CEnemy* enemy)
{
	VECTOR plPos = player->GetPos();
	VECTOR enPos = GetPos();

	//２点間の距離を取得
	VECTOR vec = VSub(enPos, plPos);
	float len = VSize(vec);

	//一定範囲より短ければヒット
	if (len < 10.0f)
	{
		//敵を押し返す
		vec = VNorm(vec);
		vec = VScale(vec, 10.0f - len);
		ReflectCollision(vec);
	}
}

//プレイヤーの攻撃と敵の当たり判定
void CEnemy::HitCheckEnemyToPlayerAttack(CPlayer* player, CEnemy* enemy)
{
	//攻撃中でなければ終了
	if (!player->IsAttack())
	{
		return;
	}

	//敵の座標とプレイヤーの攻撃した座標を取得
	VECTOR plAttackPos = player->GetAttackPos();
	VECTOR enPos = GetPos();

	//2点間の距離を取得
	VECTOR vec = MyMath::VecSubtract(enPos, plAttackPos);
	float len = VSize(vec);

	//一定範囲より短ければヒット
	if (len < 10.0f)
	{
		vec = MyMath::VecNormalize(vec);
		vec.y = 5.0f;						//上方向に飛ばす力
		vec = MyMath::VecScale(vec, 3.0f);	//全体の吹き飛ばす力

		//敵に吹き飛ぶ方向を与える
		HitCalc(vec);
	}
}
