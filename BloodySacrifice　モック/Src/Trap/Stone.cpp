#include "Stone.h"
#include "../Collision/Collision.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Player/PlayerManager.h"
#include "../Common.h"

//�d��
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
	//��ɏd�͂�������
	m_vPos.y -= GRAVITY;
	
	VECTOR vVec;
	vVec = g_map.HitCheck(m_vPos, STONE_RAD);
	m_vPos = VAdd(m_vPos, vVec);

	CPlayer* player = g_player_manager.GetPlayer();
	//�܂�㩂��쓮���ĂȂ��Ȃ�
	if (m_eState == STONE_TRAP_STATE_BEFORE)
	{
		//���Ƃ̐ڒn�ʂ��v�Z
		float bottom = m_vPos.y - STONE_RAD;
		//�R��ɂ���Ȃ�
		if (bottom > 0)
		{
			//�v���C���[�Ɠ����蔻��Ƃ�
			if (CCollision::IsHitSphere(m_vPos, STONE_RAD, player->GetPos(), PLAYER_W * 0.5f))
			{
				//�v���C���[�����������ɉ����o��
				m_vPos = MyMath::VecAdd(m_vPos, player->GetSpeed());
			}
		}
		else
		{
			//�R���ɂ�������쓮�t���O�����Ă�
			m_eState = STONE_TRAP_STATE_AFTER;
			m_fAppTime = 0.0f;
		}
	}
	
	//�◎�Ƃ����쓮������
	if (m_eState == STONE_TRAP_STATE_AFTER)
	{
		m_fAppTime += 1.0f / FRAME_RATE;

		//�o�����Ԃ𒴂�����
		if (m_fAppTime >= STONE_APP_TIME)
		{
			//���ŏ�Ԃɂ���
			m_eState = STONE_TRAP_STATE_OUT;
			MV1DeleteModel(m_nHandle);
		}
	}
	

	//���W�ݒ� =====

	MV1SetPosition(m_nHandle, m_vPos);
}

void CStoneTrap::Draw()
{
	//���ŏ�ԂłȂ�������`�悷��
	if (m_eState != STONE_TRAP_STATE_OUT)
	{
		MV1DrawModel(m_nHandle);
	}
}

void CStoneTrap::Fin()
{
	MV1DeleteModel(m_nHandle);
}
