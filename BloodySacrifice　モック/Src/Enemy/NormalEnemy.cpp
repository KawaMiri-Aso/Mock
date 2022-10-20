#include "NormalEnemy.h"
#include "../Common.h"
#include "../Player/PlayerManager.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Trap/Stone.h"
#include "../Collision/Collision.h"
#include "../AI/AINormalEnemy.h"
#include <math.h>

namespace {
	int NORMAL_ENEMY_HP = 10;
	float NORMAL_ENEMY_RAD = 3.0f;
	float NORMAL_ENEMY_MOVE_SPEED = 0.5f;
	float NORMAL_ENEMY_ATTACK_RANGE = 25.0f;
	float NORMAL_ENEMY_CAUTION_RANGE = 38.0f;
	float NORMAL_ENEMY_BACK_RANGE = 58.0f;
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
	is_active_ = true;			//�����t���O
	hp_ = NORMAL_ENEMY_HP;		//HP
	rad_ = NORMAL_ENEMY_RAD;	//���a
	is_hit_stonetrap = false;	//��Ɠ������Ă��邩
	//AI��ԑJ�ڂ�ݒ�
	enemy_ai_ = new CAINomalEnemy;
	static_cast<CAINomalEnemy*>(enemy_ai_)->Init(NORMAL_ENEMY_ATTACK_RANGE, NORMAL_ENEMY_CAUTION_RANGE, NORMAL_ENEMY_BACK_RANGE);
}

void CNormalEnemy::Load()
{
	handle_ = MV1LoadModel("Data/Model/Enemy/enemy-mock.x");
}

void CNormalEnemy::Step()
{
	//����AI�̏�Ԃ�ݒ�
	ai_state_ = enemy_ai_->GetNextState(this);

	if (IsActive())
	{
		//AI�X�V
		StepAI();

		//��ɏd�͂�������
		move_.y -= GRAVITY;

		//�}�b�v�Ƃ̓����蔻��
		/*VECTOR vVec;
		vVec = g_map.HitCheck(pos_, rad_);
		pos_ = VAdd(pos_, vVec);*/
		HitMap();

		//�ړ�����
		pos_ = MyMath::VecAdd(pos_, move_);

		MV1SetRotationXYZ(handle_, rot_);
		MV1SetPosition(handle_, pos_);
	}

	if (CCollision::IsHitSphere(pos_, NORMAL_ENEMY_RAD, g_stone_trap.GetPos(), STONE_RAD))
	{
		is_active_ = false;
	}
}

void CNormalEnemy::Draw()
{
	MV1DrawModel(handle_);
}

void CNormalEnemy::Delete()
{
	MV1DeleteModel(handle_);
}

void CNormalEnemy::Fin()
{
	Delete();
}

CEnemy* CNormalEnemy::Clone()
{
	CNormalEnemy* clone =  new CNormalEnemy;
	*clone = *this;
	clone->handle_ = MV1DuplicateModel(handle_);
	return clone;
}

void CNormalEnemy::StepAI()
{
	//���݂̏�Ԃ���eAI������
	switch (ai_state_)
	{
	case CAIBase::ENEMY_AI_STATE_IDLE:	//�ҋ@��ԍX�V
		StepIdle();
		break;
	case CAIBase::ENEMY_AI_STATE_CAUTION:	//�x����ԍX�V
		StepCaution();
		break;
	case CAIBase::ENEMY_AI_STATE_ATTACK:	//�U����ԍX�V
		StepAttack();
		break;
	case CAIBase::ENEMY_AI_STATE_BACK:	//�A�ҏ�ԍX�V
		StepBack();
		break;
	}
}

void CNormalEnemy::StepIdle()
{
	//��ŃE���E��������
	//�ЂƂ܂��ړ����Ȃ�
	move_.x = 0.0f;
	move_.z = 0.0f;
}

void CNormalEnemy::StepCaution()
{
	//�v���C���[�܂ł̃x�N�g�����쐬
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR player_vec = MyMath::VecCreate(pos_, player->GetPos());
	//�v���C���[�̌����p�x���Z�o����Y��]�l�ɑ��
	rot_.y = atan2f(-player_vec.x, -player_vec.z);
	//�ړ����~�߂�
	move_.x = 0.0f;
	move_.z = 0.0f;
}

void CNormalEnemy::StepAttack()
{
	//�v���C���[�܂ł̃x�N�g�����쐬
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR player_vec = MyMath::VecCreate(pos_, player->GetPos());
	//Y�v�f��0
	player_vec.y = 0.0f;
	//������ݒ�
	rot_.y = atan2f(-player_vec.x, -player_vec.z);
	//�x�N�g�����ړ��X�s�[�h�̒����ɂ��Ĉړ��ʂɂ���
	player_vec = MyMath::VecNormalize(player_vec);
	VECTOR move_vec = MyMath::VecScale(player_vec, NORMAL_ENEMY_MOVE_SPEED);
	move_.x = move_vec.x;
	move_.z = move_vec.z;
}

void CNormalEnemy::StepBack()
{
	// �A�҃|�C���g�܂ł̃x�N�g�����쐬
	VECTOR back_vec = MyMath::VecCreate(pos_, back_pos_);
	// y�v�f��0��
	back_vec.y = 0.0f;
	// ���̃x�N�g�����ړ��X�s�[�h�̒����ɂ��Ĉړ��ʂƂ���
	back_vec = MyMath::VecNormalize(back_vec);
	VECTOR move_vec = MyMath::VecScale(back_vec, NORMAL_ENEMY_MOVE_SPEED);
	move_.x = move_vec.x;
	move_.z = move_vec.z;
	// �ړ��������������
	rot_.y = atan2f(-move_.x, -move_.z);
}