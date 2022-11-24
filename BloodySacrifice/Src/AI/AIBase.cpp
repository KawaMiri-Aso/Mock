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

//�v���C���[�܂ł̋����Z�o
float CAIBase::GetPlayerDist(CEnemy* enemy)
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR dis_vec = MyMath::VecCreate(player->GetPos(), enemy->GetPos());
	dis_vec.y = 0.0f;
	return MyMath::VecLong(dis_vec);
}

//�A�҃|�C���g�܂ł̋����Z�o
float CAIBase::GetBackPosDist(CEnemy* enemy)
{
	VECTOR dis_vec = MyMath::VecCreate(enemy->GetBackPos(), enemy->GetPos());
	dis_vec.y = 0.0f;
	return MyMath::VecLong(dis_vec);
}

//�g�[�e���܂ł̋����Z�o
float CAIBase::GetTotemDist(CEnemy* enemy)
{
	VECTOR dis_vec = MyMath::VecCreate(g_totem.GetPos(), enemy->GetPos());
	dis_vec.y = 0.0f;
	return MyMath::VecLong(dis_vec);
}