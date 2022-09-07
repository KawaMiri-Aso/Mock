#include "Stone.h"
#include "../Collision/Collision.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Player/PlayerManager.h"
#include "../Common.h"

//重力
#define GRAVITY		(1.15f)

CStoneTrap g_stone_trap;

CStoneTrap::CStoneTrap()
{
	m_nHandle = 0;
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_eState = STONE_TRAP_STATE_BEFORE;
	m_fAppTime = 0.0f;
}

CStoneTrap::~CStoneTrap()
{
}

void CStoneTrap::Init()
{
	m_nHandle = m_nHandle = MV1LoadModel("Data/Model/Trap/Stone/Stone.x");
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_eState = STONE_TRAP_STATE_BEFORE;
	m_fAppTime = 0.0f;
}

void CStoneTrap::Init(VECTOR pos)
{
	m_nHandle = MV1LoadModel("Data/Model/Trap/Stone/Stone.x");
	m_vPos = pos;
	m_eState = STONE_TRAP_STATE_BEFORE;
	m_fAppTime = 0.0f;
}

void CStoneTrap::Step()
{
	//常に重力をかける
	m_vPos.y -= GRAVITY;
	
	VECTOR vVec;
	vVec = g_map.HitCheck(m_vPos, STONE_RAD);
	m_vPos = VAdd(m_vPos, vVec);

	CPlayer* player = g_player_manager.GetPlayer();
	//まだ罠を作動してないなら
	if (m_eState == STONE_TRAP_STATE_BEFORE)
	{
		//床との接地面を計算
		float bottom = m_vPos.y - STONE_RAD;
		//崖上にあるなら
		if (bottom > 0)
		{
			//プレイヤーと当たり判定とる
			if (CCollision::IsHitSphere(m_vPos, STONE_RAD, player->GetPos(), PLAYER_W * 0.5f))
			{
				//プレイヤーが押す方向に押し出す
				m_vPos = MyMath::VecAdd(m_vPos, player->GetSpeed());
			}
		}
		else
		{
			//崖下にいったら作動フラグをたてる
			m_eState = STONE_TRAP_STATE_AFTER;
			m_fAppTime = 0.0f;
		}
	}
	
	//岩落としが作動したら
	if (m_eState == STONE_TRAP_STATE_AFTER)
	{
		m_fAppTime += 1.0f / FRAME_RATE;

		//出現時間を超えたら
		if (m_fAppTime >= STONE_APP_TIME)
		{
			//消滅状態にする
			m_eState = STONE_TRAP_STATE_OUT;
			MV1DeleteModel(m_nHandle);
		}
	}
	

	//座標設定 =====

	MV1SetPosition(m_nHandle, m_vPos);
}

void CStoneTrap::Draw()
{
	//消滅状態でなかったら描画する
	if (m_eState != STONE_TRAP_STATE_OUT)
	{
		MV1DrawModel(m_nHandle);
	}
}

void CStoneTrap::Fin()
{
	MV1DeleteModel(m_nHandle);
}
