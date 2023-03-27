#include "NormalEnemy.h"
#include "../Common.h"
//#include "../Player/PlayerManager.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Trap/Stone.h"
#include "../Collision/Collision.h"
#include "../AI/AINormalEnemy.h"
#include "../Totem/Totem.h"
#include <math.h>
#include "../Common/Time.h"
#include "../Enemy/EnemyManager.h"

#define DEBUG

namespace {
	int NORMAL_ENEMY_HP = 10;
	float NORMAL_ENEMY_RAD = 3.0f;
	float NORMAL_ENEMY_MOVE_SPEED = 0.25f;
	float NORMAL_ENEMY_ATTACK_RANGE = 25.0f;
	float NORMAL_ENEMY_CAUTION_RANGE = 38.0f;
	float NORMAL_ENEMY_BACK_RANGE = 58.0f;
	float DAMAGE = 5.0f;	//�^����_���[�W
	float ATTACK_TIME = 60.0f;
}


CNormalEnemy::CNormalEnemy()
{
	handle_ = 0;
	timer_ = 0.0f;
}

CNormalEnemy::~CNormalEnemy()
{
	Fin();
}

void CNormalEnemy::Init()
{
	active_ = true;			//�����t���O
	hp_ = NORMAL_ENEMY_HP;		//HP
	rad_ = NORMAL_ENEMY_RAD;	//���a
	//is_hit_stonetrap = false;	//��Ɠ������Ă��邩
	//AI��ԑJ�ڂ�ݒ�
	enemy_ai_ = new CAINomalEnemy;
	static_cast<CAINomalEnemy*>(enemy_ai_)->Init(NORMAL_ENEMY_ATTACK_RANGE, NORMAL_ENEMY_CAUTION_RANGE, NORMAL_ENEMY_BACK_RANGE);
}

void CNormalEnemy::Load()
{
	//���f���̓ǂݍ���
	handle_ = MV1LoadModel("Data/Model/Enemy/Goblin.x");
	//���f���̃X�P�[���ݒ�
	MV1SetScale(handle_, VGet(0.25f, 0.25f, 0.25f));

	// �A�j���̍Đ�
	m_animIdx[ANIM_MAIN] = MV1AttachAnim(handle_, EN_WALK);
	m_animCount[ANIM_MAIN] = 0.0f;
	m_animSpeed[ANIM_MAIN] = ANIM_SPD;
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

		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		CEnemy* enemy = CEnemyManager::GetInstance()->GetEnemy();

		//�v���C���[�ƓG�̓����蔻��
		/*if (HitCheckEnemyToPlayer(player, enemy))
		{
			StepHitBack();
		}
		else */
		/*if (HitCheckEnemyToPlayerAttack(player, enemy))
		{
			StepHitBack();
		}*/

		//�ړ�����
		pos_ = MyMath::VecAdd(pos_, move_);

		//�A�j���X�V
		AnimUpdate();

		MV1SetRotationXYZ(handle_, rot_);
		MV1SetPosition(handle_, pos_);
	}

	if (CCollision::IsHitSphere(pos_, NORMAL_ENEMY_RAD, g_totem.GetPos(), TOTEM_RAD))
	{
		pos_.x -= move_.x;
		pos_.z -= move_.z;
	}

	//if (CCollision::IsHitSphere(pos_, NORMAL_ENEMY_RAD, g_stone_trap.GetPos(), STONE_RAD))
	//{
	//	is_active_ = false;
	//}

	
}

void CNormalEnemy::Draw()
{
	MV1DrawModel(handle_);

#ifdef DEBUG
	DrawFormatString(10, 58, GetColor(255, 128, 0), "�GHP�F%d", hp_);
	DrawSphere3D(pos_, 10.0f, 4, GetColor(255, 255, 0), GetColor(255, 255, 0), FALSE);
#endif 
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
	case CAIBase::ENEMY_AI_STATE_IDLE:		//�ҋ@��ԍX�V
		StepIdle();
		break;
	case CAIBase::ENEMY_AI_STATE_ATTACK:	//�U����ԍX�V
		StepAttack();
		break;
	case CAIBase::ENEMY_AI_STATE_HITBACK:	//�̂�����
		StepHitBack();
		break;
	case CAIBase::ENEMY_AI_STATE_DEAD:		//���S
		StepDead();
		break;
	}

}

//��ԁF����
void CNormalEnemy::StepIdle()
{
	//�g�[�e���Ɍ������Ă���
	VECTOR vec = MyMath::VecCreate(pos_, g_totem.GetPos());
	// y�v�f��0��
	vec.y = 0.0f;
	// ���̃x�N�g�����ړ��X�s�[�h�̒����ɂ��Ĉړ��ʂƂ���
	vec = MyMath::VecNormalize(vec);
	VECTOR move_vec = MyMath::VecScale(vec, NORMAL_ENEMY_MOVE_SPEED);
	move_.x = move_vec.x;
	move_.z = move_vec.z;
	// �ړ��������������
	rot_.y = atan2f(-move_.x, -move_.z);

	Request(EN_WALK, ANIM_SPD);
}

//��ԁF�U��
void CNormalEnemy::StepAttack()
{
	////�v���C���[�܂ł̃x�N�g�����쐬
	//CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	//VECTOR player_vec = MyMath::VecCreate(pos_, player->GetPos());
	
	////�g�[�e���Ɍ������Ă���
	//VECTOR vec = MyMath::VecCreate(pos_, g_totem.GetPos());
	////Y�v�f��0
	//vec.y = 0.0f;
	////������ݒ�
	//rot_.y = atan2f(-vec.x, -vec.z);
	////�x�N�g�����ړ��X�s�[�h�̒����ɂ��Ĉړ��ʂɂ���
	//vec = MyMath::VecNormalize(vec);
	//VECTOR move_vec = MyMath::VecScale(vec, NORMAL_ENEMY_MOVE_SPEED);
	//move_.x = move_vec.x;
	//move_.z = move_vec.z;

	//�g�[�e���ɒ��������_�ōU��
	//�ړ����~�߂�
	move_.x = 0.0f;
	move_.z = 0.0f;

	Request(EN_ATTACK, ANIM_SPD);

	if (timer_ >= ATTACK_TIME)
	{
		g_totem.Damage(DAMAGE);
		timer_ = 0.0f;
	}

	timer_ += Comn::GetGameDeltaFrame();
}

//��ԁF�̂�����
void CNormalEnemy::StepHitBack()
{
	Request(EN_HIT_BACK, ANIM_SPD);
}

//��ԁF���S
void CNormalEnemy::StepDead()
{
	Request(EN_DEAD, ANIM_SPD);
}

//�A�j���[�V�������N�G�X�g
void CNormalEnemy::Request(int animID, float animSpd)
{
	// �����A�j���͖���
	if (m_animType == animID) return;

	// �Ƃ肠����2�ȏ�͖����A���ł�2�Đ�����1����
	if (m_animIdx[ANIM_SUB] != -1)
	{
		MV1DetachAnim(handle_, m_animIdx[ANIM_SUB]);
		m_animIdx[ANIM_SUB] = -1;
	}
	// ���C���Đ��̃A�j�������T�u�Ɉړ�
	m_animIdx[ANIM_SUB] = m_animIdx[ANIM_MAIN];
	m_animCount[ANIM_SUB] = m_animCount[ANIM_MAIN];
	m_animSpeed[ANIM_SUB] = m_animSpeed[ANIM_MAIN];

	// ���̌�V�����A�^�b�`���Ȃ���
	m_animIdx[ANIM_MAIN] = MV1AttachAnim(handle_, animID);
	// ���C���A�j���͐ݒ肵�Ȃ���
	m_animSpeed[ANIM_MAIN] = animSpd;
	m_animCount[ANIM_MAIN] = 0;

	m_animRate = 1.f;		// ���[�g�ݒ肵�Ȃ���
	m_animType = animID;
}

//�A�j���X�V
void CNormalEnemy::AnimUpdate()
{
	// ���[�g�̍X�V======================================================
	if (m_animRate > 0.0f)
	{
		m_animRate -= CHANGE_SPD;
		// ���[�g��0�����������Â����̃A�j���[�V�������폜
		if (m_animRate < 0.0f)
		{
			MV1DetachAnim(handle_, m_animIdx[ANIM_SUB]);
			m_animIdx[ANIM_SUB] = -1;
		}
	}
	// ==================================================================

	// �A�j���[�V�����X�V
	for (int i = 0; i < BLEND_NUM; i++)
	{
		if (m_animIdx[i] == -1) continue;
		m_animCount[i] += m_animSpeed[i];

		// �A�j�����Ō�܂Ői�񂾂�ŏ���
		if (MV1GetAnimTotalTime(handle_, m_animIdx[i]) < m_animCount[i])
		{
			m_animCount[i] = 0.0f;
		}

		// ���ԍX�V
		MV1SetAttachAnimTime(handle_, m_animIdx[i], m_animCount[i]);
		// ���[�g��ݒ肷��
		float rate = i == ANIM_MAIN ? 1.0f - m_animRate : m_animRate;
		MV1SetAttachAnimBlendRate(handle_, m_animIdx[i], rate);
	}

	// ���W�X�V
	MV1SetPosition(handle_, pos_);
}