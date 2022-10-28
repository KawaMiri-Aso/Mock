#include "Stone.h"
#include "../Collision/Collision.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Player/PlayerManager.h"
#include "../Common.h"

CStoneTrap g_stone_trap;

CStoneTrap::CStoneTrap()
{
	handle_ = 0;
	memset(&pos_, 0, sizeof(VECTOR));
	memset(&rot_, 0, sizeof(VECTOR));
	state_ = STONE_TRAP_STATE_BEFORE;
	app_time_ = 0.0f;
}

CStoneTrap::~CStoneTrap()
{
}

void CStoneTrap::Init()
{
	handle_ = MV1LoadModel("Data/Model/Trap/Stone/Stone.x");
	memset(&pos_, 0, sizeof(VECTOR));
	memset(&rot_, 0, sizeof(VECTOR));
	state_ = STONE_TRAP_STATE_BEFORE;
	app_time_ = 0.0f;
}

void CStoneTrap::Init(VECTOR pos)
{
	handle_ = MV1LoadModel("Data/Model/Trap/Stone/Stone.x");
	pos_ = pos;
	state_ = STONE_TRAP_STATE_BEFORE;
	app_time_ = 0.0f;
}

void CStoneTrap::Step()
{
	//��ɏd�͂�������
	pos_.y -= GRAVITY_STONE;
	
	VECTOR vVec;
	vVec = g_map.HitCheck(pos_, STONE_RAD);
	pos_ = VAdd(pos_, vVec);

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	//�܂�㩂��쓮���ĂȂ��Ȃ�
	if (state_ == STONE_TRAP_STATE_BEFORE)
	{
		//���Ƃ̐ڒn�ʂ��v�Z
		float bottom = pos_.y - STONE_RAD;
		//�R��ɂ���Ȃ�
		if (bottom > 0)
		{
			//�v���C���[�Ɠ����蔻��Ƃ�
			if (CCollision::IsHitSphere(pos_, STONE_RAD, player->GetPos(), PLAYER_W * 0.5f))
			{
				//�v���C���[�����������ɉ����o��
				pos_ = MyMath::VecAdd(pos_, player->GetSpeed());
			}
		}
		else
		{
			//�R���ɂ�������쓮�t���O�����Ă�
			state_ = STONE_TRAP_STATE_AFTER;
			app_time_ = 0.0f;
		}
	}
	
	//�◎�Ƃ����쓮������
	if (state_ == STONE_TRAP_STATE_AFTER)
	{
		app_time_ += 1.0f / FRAME_RATE;

		//�o�����Ԃ𒴂�����
		if (app_time_ >= STONE_APP_TIME)
		{
			//���ŏ�Ԃɂ���
			state_ = STONE_TRAP_STATE_OUT;
			MV1DeleteModel(handle_);
		}
	}
	

	//���W�ݒ� =====

	MV1SetPosition(handle_, pos_);
}

void CStoneTrap::Draw()
{
	//���ŏ�ԂłȂ�������`�悷��
	if (state_ != STONE_TRAP_STATE_OUT)
	{
		MV1DrawModel(handle_);
	}
}

void CStoneTrap::Fin()
{
	MV1DeleteModel(handle_);
}
