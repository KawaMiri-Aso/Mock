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

//Œ»ÝˆÊ’u‚ÉÀ•W‰ÁŽZ
void CEnemy::ReflectCollision(VECTOR addVec)
{
	// ƒI[ƒ‹ƒ[ƒ‚È‚ç‰½‚à‚µ‚È‚¢
	if (addVec.x == 0.0f && addVec.y == 0.0f && addVec.z == 0.0f) return;

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR	pos = player->GetPos();
	pos = VAdd(pos, addVec);
	//m_gravity = 0.0f;
	SetPos(pos);
}

//ƒvƒŒƒCƒ„[‚ÌUŒ‚‚ªƒqƒbƒg‚µ‚½Œã‚Ìˆ—
void CEnemy::HitCalc(VECTOR move)
{
	move_ = move;
	
}

////ƒvƒŒƒCƒ„[‚Æ“G‚Ì“–‚½‚è”»’è
//bool CEnemy::HitCheckEnemyToPlayer(CPlayer* player, CEnemy* enemy)
//{
//	VECTOR plPos = player->GetPos();
//	VECTOR enPos = GetPos();
//
//	//‚Q“_ŠÔ‚Ì‹——£‚ðŽæ“¾
//	VECTOR vec = VSub(enPos, plPos);
//	float len = VSize(vec);
//
//	//ˆê’è”ÍˆÍ‚æ‚è’Z‚¯‚ê‚Îƒqƒbƒg
//	if (len < 10.0f)
//	{
//		//“G‚ð‰Ÿ‚µ•Ô‚·
//		vec = VNorm(vec);
//		vec = VScale(vec, 10.0f - len);
//		ReflectCollision(vec);
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
////ƒvƒŒƒCƒ„[‚ÌUŒ‚‚Æ“G‚Ì“–‚½‚è”»’è
//bool CEnemy::HitCheckEnemyToPlayerAttack(CPlayer* player, CEnemy* enemy)
//{
//	//UŒ‚’†‚Å‚È‚¯‚ê‚ÎI—¹
//	if (!player->IsAttack())
//	{
//		return false;
//	}
//
//	//“G‚ÌÀ•W‚ÆƒvƒŒƒCƒ„[‚ÌUŒ‚‚µ‚½À•W‚ðŽæ“¾
//	VECTOR plAttackPos = player->GetAttackPos();
//	VECTOR enPos = GetPos();
//
//	//2“_ŠÔ‚Ì‹——£‚ðŽæ“¾
//	VECTOR vec = MyMath::VecSubtract(enPos, plAttackPos);
//	float len = VSize(vec);
//
//	//ˆê’è”ÍˆÍ‚æ‚è’Z‚¯‚ê‚Îƒqƒbƒg
//	if (len < 50.0f)
//	{
//		//vec = MyMath::VecNormalize(vec);
//		//vec.y = 5.0f;						//ã•ûŒü‚É”ò‚Î‚·—Í
//		//vec = MyMath::VecScale(vec, 3.0f);	//‘S‘Ì‚Ì‚«”ò‚Î‚·—Í
//
//		////“G‚É‚«”ò‚Ô•ûŒü‚ð—^‚¦‚é
//		//HitCalc(vec);
//
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

void CEnemy::OnPlCollisionEnter(CPlayer* another)
{

}