#include "AIBase.h"
#include "../Player/PlayerManager.h"
#include "../Totem/Totem.h"
#include "../MyMath/MyMath.h"

CAIBase::CAIBase()
{
}

CAIBase::~CAIBase()
{
}

//プレイヤーまでの距離算出
float CAIBase::GetPlayerDist(CEnemy* enemy)
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR dis_vec = MyMath::VecCreate(player->GetPos(), enemy->GetPos());
	dis_vec.y = 0.0f;
	return MyMath::VecLong(dis_vec);
}

//帰還ポイントまでの距離算出
float CAIBase::GetBackPosDist(CEnemy* enemy)
{
	VECTOR dis_vec = MyMath::VecCreate(enemy->GetBackPos(), enemy->GetPos());
	dis_vec.y = 0.0f;
	return MyMath::VecLong(dis_vec);
}

//トーテムまでの距離算出
float CAIBase::GetTotemDist(CEnemy* enemy)
{
	VECTOR dis_vec = MyMath::VecCreate(g_totem.GetPos(), enemy->GetPos());
	dis_vec.y = 0.0f;
	return MyMath::VecLong(dis_vec);
}