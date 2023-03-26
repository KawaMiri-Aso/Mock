
//Player.cpp
//�v���C���[�֘A

#include <math.h>
#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../Camera/PlayCamera.h"
#include "../MyMath/MyMath.h"
#include "../Collision/Collision.h"
#include "../Map/Map.h"
#include "../Trap/Stone.h"
#include "../Totem/Totem.h"

namespace {
	float PLAYER_HP = 500.0f;
	float PLAYER_LOW_ATTACK = 3.0f;
	float PLAYER_MID_ATTACK = 7.0f;
	float PLAYER_HIGH_ATTACK = 15.0f;
	
}

#define DEBUG

MyMath* math;

//�R���X�g���N�^
CPlayer::CPlayer()
{
	handle_ = 0;
	memset(&pos_, 0, sizeof(VECTOR));
	player_state_ = PLAYER_STATE_NORMAL;
	jump_time_ = 0.0f;
	hp_ = 0.0f;
	IsCombo_ = false;

	for (int i = 0; i < BLEND_NUM; i++)
	{
		m_animCount[i] = 0.0f;
		m_animSpeed[i] = 0.0f;
		m_animIdx[i] = -1;
	}
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{
	Fin();
}

//�������i�����Ȃ��j
void CPlayer::Init()
{
	//�����Ȃ��Ȃ炷�ׂă[���ɂ���
	handle_ = 0;
	pos_ = VGet(0.0f, 1.0f, 0.0f);
	angle_ = 0.0f;
	player_state_ = PLAYER_STATE_NORMAL;
	jump_time_ = 0.0f;
}

//�������i��������j
void CPlayer::Init(VECTOR pos)
{
	//���W�Ɖ�]��ݒ�
	pos_ = pos;

	//���̓[���ɂ���
	angle_ = 0.0f;
	handle_ = 0;
	player_state_ = PLAYER_STATE_NORMAL;
	jump_time_ = 0.0f;
	hp_ = PLAYER_HP;
}

//�ǂݍ���
void CPlayer::Load()
{
	//���f���̓ǂݍ���
	handle_ = MV1LoadModel("Data/Model/Player/Knight.x");
	MV1SetScale(handle_, VGet(0.25f, 0.25f, 0.25f));

	// �A�j���̍Đ�
	m_animIdx[ANIM_MAIN] = MV1AttachAnim(handle_, WAIT);
	m_animCount[ANIM_MAIN] = 0.0f;
	m_animSpeed[ANIM_MAIN] = ANIM_SPD;
}

//�폜
void CPlayer::Delete()
{
	//���f���j��
	MV1DeleteModel(handle_);

	//�폜������0�������Ă���
	handle_ = 0;
}

//���t���[���Ăԏ����i����j
void CPlayer::Step()
{
	//�ړ��t���O
	bool moveFlg;

	//������Ԃł͈ړ����Ă��Ȃ�
	moveFlg = false;

	//�ړ����x�x�N�g����������
	speed_ = { 0 };

	//�v���C���[�ʏ�
	if(player_state_ == PLAYER_STATE_NORMAL)
	{
		if(g_input.IsPush(KEY_SPACE))
		{
			//��Ԃ��W�����v�㏸����
 			player_state_ = PLAYER_STATE_JUMP_UP;
			jump_time_ = 0.0f;
			//�㏸
			speed_.y = PLAYER_JUMP_VAL;
		}
	}

	//�v���C���[�W�����v�㏸��
 	if(player_state_ == PLAYER_STATE_JUMP_UP)
	{
		//�㏸
		/*speed_.y = PLAYER_JUMP_VAL;*/
		jump_time_ += 1.0f / FRAME_RATE;
		speed_.y -= GRAVITY;

		//�W�����v���Ԃ��߂�����
		/*if (speed_.y <= 0.0f)
		{
			jump_time_ = 0.0f;
			speed_.y = 0.0f;
			player_state_ = PLAYER_STATE_NORMAL;
		}*/
	}

	//�v���C���[�ɏ�ɏd�͂�������
	/*pos_.y -= GRAVITY;*/
	speed_.y -= GRAVITY;
	pos_.y += speed_.y;
	SetPos(pos_);

	//���Ƃ̓����蔻��
	VECTOR vVec;
	vVec = g_map.HitCheck(pos_, PLAYER_RAD);
	pos_ = VAdd(pos_, vVec);

	//�ړ�����
	//CalcMove();
	//��Ԏ擾
	GetState();

	//�U������
	//CalcAttack1();
	//��Ԏ擾
	GetState();

	switch (player_state_)
	{
	case PLAYER_STATE_NORMAL:
		//Request(WAIT, ANIM_SPD);
		//�ړ�����
		CalcMove();
		//�U������
		CalcAttack1();
		break;
	case PLAYER_STATE_WALK:
		//Request(WALK, ANIM_SPD);
		//�ړ�����
		CalcMove();
		//�U������
		CalcAttack1();
		break;
	case PLAYER_STATE_RUN:
		//Request(RUN, ANIM_SPD);
		//�ړ�����
		CalcMove();
		//�U������
		CalcAttack1();
		break;
	case PLAYER_STATE_JUMP_UP:
		break;
	case PLAYER_STATE_ATTACK1:
		//�U������
		CalcAttack2();
		break;
	case PLAYER_STATE_ATTACK2:
		EndCombo();
		break;
	case PLAYER_STATE_DEAD:
		Request(DEAD, ANIM_SPD);
		break;
	default:
		break;
	}
	//�A�j���X�V
	AnimUpdate();

	//���W�ݒ� =====
	//�v���C���[�̍��W
	MV1SetPosition(handle_, pos_);

}

//�`��
void CPlayer::Draw()
{
	//�v���C���[�̕`��
	MV1DrawModel(handle_);

#ifdef DEBUG
	DrawFormatString(10, 74, GetColor(255, 128, 0), "�v���C���[HP�F%d", hp_);
	DrawFormatString(10, 110, GetColor(255, 128, 0), "�v���C���[�U�������蔻����W: X=%.f, Y=%.f, Z=%.f", GetAttackPos().x, GetAttackPos().y, GetAttackPos().z);
	if (IsAttack())
	{
		DrawSphere3D(GetAttackPos(), ATTACK_COL_RAD, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
	}
#endif // DEBUG
}

//�㏈��
void CPlayer::Fin()
{
	//Delete���Ă΂�Ă��Ȃ��Ȃ�
	if(handle_ != 0)
	{
		//�폜���Ă�ł���
		Delete();
	}
}

//�v���C���[�̉�]����
void CPlayer::AngleProcess()
{
	//�ڕW�p�x
	float TargetAngle = 0.0f;
	//�ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�
	float DiffAngle;

	//�ړ����x�x�N�g����0�ȊO�̂Ƃ��Ɍv�Z����
	if (speed_.x != 0 || speed_.z != 0)
	{
		TargetAngle = atan2f(speed_.x, speed_.z);
	}

	// �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
	{
		DiffAngle = TargetAngle - angle_;

		// ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
		// ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
		if (DiffAngle < -DX_PI_F)
		{
			DiffAngle += DX_TWO_PI_F;
		}
		else if (DiffAngle > DX_PI_F)
		{
			DiffAngle -= DX_TWO_PI_F;
		}
	}

	if (DiffAngle > 0.0f)
	{
		// �����v���X�̏ꍇ�͈���
		if (player_state_ == PLAYER_STATE_WALK)
		{
			DiffAngle -= PLAYER_WALK_SPEED;
		}
		else
		{
			DiffAngle -= PLAYER_RUN_SPEED;
		}
		if (DiffAngle < 0.0f)
		{
			DiffAngle = 0.0f;
		}
	}
	else
	{
		// �����}�C�i�X�̏ꍇ�͑���
		if (player_state_ == PLAYER_STATE_WALK)
		{
			DiffAngle += PLAYER_WALK_SPEED;
		}
		else
		{
			DiffAngle += PLAYER_RUN_SPEED;
		}

		if (DiffAngle > 0.0f)
		{
			DiffAngle = 0.0f;
		}
	}
	
	angle_ = TargetAngle - DiffAngle;

	//�v���C���[�̉�]
	MV1SetRotationXYZ(handle_, VGet(0.0f, angle_ + DX_PI_F, 0.0f));
}

//�Q�[���I�[�o�[����
bool CPlayer::Dead()
{
	if (hp_ <= 0)
	{
		player_state_ = PLAYER_STATE_DEAD;

		return true;
	}
	else
	{
		return false;
	}
}

//�A�j���[�V�������N�G�X�g
void CPlayer::Request(int animID, float animSpd)
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
void CPlayer::AnimUpdate()
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

//�ړ�����
bool CPlayer::CalcMove()
{
	//�ړ��t���O
	bool moveFlg = false;

	//�΂߈ړ�
	if (g_input.IsCont(KEY_W) && g_input.IsCont(KEY_A) || g_input.IsCont(KEY_W) && g_input.IsCont(KEY_D))
	{
		VECTOR move_up_sidle = { 0 };

		//�J�������擾
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_up_sidle = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_up_sidle.y = 0;
		//���K��
		move_up_sidle = math->VecNormalize(move_up_sidle);
		//�����������|���Z
		if (g_input.IsCont(KEY_LSHIFT))
		{
			move_up_sidle = math->VecScale(move_up_sidle, PLAYER_RUN_SPEED);
			player_state_ = PLAYER_STATE_RUN;
		}
		else
		{
			move_up_sidle = math->VecScale(move_up_sidle, PLAYER_WALK_SPEED);
			player_state_ = PLAYER_STATE_WALK;
		}

		//���s�ړ��s��擾
		MATRIX m_dir = MGetTranslate(move_up_sidle);
		MATRIX m_rotY;
		//Y����]�s��擾
		if (!g_input.IsCont(KEY_D))
		{
			m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING_HALF);
		}
		else
		{
			m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING_HALF);
		}
		//�s�񓯎m�̊|���Z
		MATRIX m_result = MMult(m_dir, m_rotY);

		//�ړ����x�x�N�g���ɓ����
		speed_.x = m_result.m[3][0];
		speed_.y = m_result.m[3][1];
		speed_.z = m_result.m[3][2];

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		/*pos_ = math->VecAdd(pos_, speed_);*/

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		pos_.x += speed_.x;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.x -= speed_.x;
		}
		pos_.y += speed_.y;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.y -= speed_.y;
		}
		pos_.z += speed_.z;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.z -= speed_.z;
		}

		//�ړ������ɕς���
		moveFlg = true;
		//player_state_ = PLAYER_STATE_WALK;

	}
	else if (g_input.IsCont(KEY_S) && g_input.IsCont(KEY_A) || g_input.IsCont(KEY_S) && g_input.IsCont(KEY_D))
	{
		VECTOR move_up_sidle = { 0 };

		//�J�������擾
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_up_sidle = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_up_sidle.y = 0;
		//���K��
		move_up_sidle = math->VecNormalize(move_up_sidle);
		//�����������|���Z
		if (g_input.IsCont(KEY_LSHIFT))
		{
			move_up_sidle = math->VecScale(move_up_sidle, -PLAYER_RUN_SPEED);
			player_state_ = PLAYER_STATE_RUN;
		}
		else
		{
			move_up_sidle = math->VecScale(move_up_sidle, -PLAYER_WALK_SPEED);
			player_state_ = PLAYER_STATE_WALK;
		}

		//���s�ړ��s��擾
		MATRIX m_dir = MGetTranslate(move_up_sidle);
		MATRIX m_rotY;
		//Y����]�s��擾
		if (!g_input.IsCont(KEY_D))
		{
			m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING_HALF);
		}
		else
		{
			m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING_HALF);
		}
		//�s�񓯎m�̊|���Z
		MATRIX m_result = MMult(m_dir, m_rotY);

		//�ړ����x�x�N�g���ɓ����
		speed_.x = m_result.m[3][0];
		speed_.y = m_result.m[3][1];
		speed_.z = m_result.m[3][2];

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		/*pos_ = math->VecAdd(pos_, speed_);*/

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		pos_.x += speed_.x;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.x -= speed_.x;
		}
		pos_.y += speed_.y;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.y -= speed_.y;
		}
		pos_.z += speed_.z;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.z -= speed_.z;
		}

		//�ړ������ɕς���
		moveFlg = true;
		//player_state_ = PLAYER_STATE_WALK;
	}
	//�J�����������Ă�������ֈړ�
	else if (g_input.IsCont(KEY_W))
	{
		VECTOR move_up = { 0 };

		//�J�������擾
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_up = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_up.y = 0;
		//���K��
		move_up = math->VecNormalize(move_up);
		//�����������|���Z
		if (g_input.IsCont(KEY_LSHIFT))
		{
			move_up = math->VecScale(move_up, PLAYER_RUN_SPEED);
			player_state_ = PLAYER_STATE_RUN;
		}
		else
		{
			move_up = math->VecScale(move_up, PLAYER_WALK_SPEED);
			player_state_ = PLAYER_STATE_WALK;
		}

		//�ړ����x�x�N�g���ɓ����
		speed_ = move_up;

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		pos_.x += speed_.x;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.x -= speed_.x;
		}
		pos_.y += speed_.y;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.y -= speed_.y;
		}
		pos_.z += speed_.z;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.z -= speed_.z;
		}

		//�ړ������ɕς���
		moveFlg = true;
		//player_state_ = PLAYER_STATE_WALK;

	}
	//�J�����������Ă�������Ƃ͋t�ֈړ�
	else if (g_input.IsCont(KEY_S))
	{
		VECTOR move_down = { 0 };

		//�J�������擾
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_down = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_down.y = 0;
		//���K��
		move_down = math->VecNormalize(move_down);
		//�����������|���Z
		if (g_input.IsCont(KEY_LSHIFT))
		{
			move_down = math->VecScale(move_down, -PLAYER_RUN_SPEED);
			player_state_ = PLAYER_STATE_RUN;
		}
		else
		{
			move_down = math->VecScale(move_down, -PLAYER_WALK_SPEED);
			player_state_ = PLAYER_STATE_WALK;
		}

		//�ړ����x�x�N�g���ɓ����
		speed_ = move_down;

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		/*pos_ = math->VecAdd(pos_, speed_);*/

			//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		pos_.x += speed_.x;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.x -= speed_.x;
		}
		pos_.y += speed_.y;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.y -= speed_.y;
		}
		pos_.z += speed_.z;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.z -= speed_.z;
		}

		//�ړ������ɕς���
		moveFlg = true;
		//player_state_ = PLAYER_STATE_WALK;
	}
	//���ֈړ�
	else if (g_input.IsCont(KEY_A))
	{
		VECTOR move_left = { 0 };

		//�J�������擾
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_left = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_left.y = 0;
		//���K��
		move_left = math->VecNormalize(move_left);
		//�����������|���Z
		if (g_input.IsCont(KEY_LSHIFT))
		{
			move_left = math->VecScale(move_left, -PLAYER_RUN_SPEED);
			player_state_ = PLAYER_STATE_RUN;
		}
		else
		{
			move_left = math->VecScale(move_left, -PLAYER_WALK_SPEED);
			player_state_ = PLAYER_STATE_WALK;
		}

		//���s�ړ��s��擾
		MATRIX m_dir = MGetTranslate(move_left);
		//Y����]�s��擾
		MATRIX m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING);
		//�e�s�������
		MATRIX m_result = MMult(m_dir, m_rotY);

		//�ړ����x�x�N�g���ɓ����
		speed_.x = m_result.m[3][0];
		speed_.y = m_result.m[3][1];
		speed_.z = m_result.m[3][2];

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		/*pos_ = math->VecAdd(pos_, speed_);*/

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		pos_.x += speed_.x;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.x -= speed_.x;
		}
		pos_.y += speed_.y;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.y -= speed_.y;
		}
		pos_.z += speed_.z;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.z -= speed_.z;
		}

		//�ړ������ɕς���
		moveFlg = true;
		//player_state_ = PLAYER_STATE_WALK;
	}
	//�E�ֈړ�
	else if (g_input.IsCont(KEY_D))
	{
		VECTOR move_right = { 0 };

		//�J�������擾
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_right = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_right.y = 0;
		//���K��
		move_right = math->VecNormalize(move_right);
		//�����������|���Z
		if (g_input.IsCont(KEY_LSHIFT))
		{
			move_right = math->VecScale(move_right, -PLAYER_RUN_SPEED);
			player_state_ = PLAYER_STATE_RUN;
		}
		else
		{
			move_right = math->VecScale(move_right, -PLAYER_WALK_SPEED);
			player_state_ = PLAYER_STATE_WALK;
		}

		//���s�ړ��s��
		MATRIX m_dir = MGetTranslate(move_right);
		MATRIX m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING);
		MATRIX m_result = MMult(m_dir, m_rotY);

		//�ړ����x�x�N�g���ɓ����
		speed_.x = m_result.m[3][0];
		speed_.y = m_result.m[3][1];
		speed_.z = m_result.m[3][2];

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		/*pos_ = math->VecAdd(pos_, speed_);*/

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		pos_.x += speed_.x;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.x -= speed_.x;
		}
		pos_.y += speed_.y;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.y -= speed_.y;
		}
		pos_.z += speed_.z;
		if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
		{
			pos_.z -= speed_.z;
		}

		//�ړ������ɕς���
		moveFlg = true;
		//player_state_ = PLAYER_STATE_WALK;
	}

	//�ړ����ĂȂ���Ή�]���������Ȃ�
	if (moveFlg)
	{
		//�v���C���[�̉�]
		AngleProcess();
	}
	else
	{
		player_state_ = PLAYER_STATE_NORMAL;
	}

	if (player_state_ == PLAYER_STATE_WALK)
	{
		Request(WALK, ANIM_SPD);
	}
	else if (player_state_ == PLAYER_STATE_RUN)
	{
		Request(RUN, ANIM_SPD);
	}
	else
	{
		Request(WAIT, ANIM_SPD);
	}
	

	return moveFlg;
}

//�W�����v����
void CPlayer::CalcJump()
{
	//�v���C���[�ʏ�
	if (player_state_ == PLAYER_STATE_NORMAL)
	{
		if (g_input.IsPush(KEY_SPACE))
		{
			//��Ԃ��W�����v�㏸����
			player_state_ = PLAYER_STATE_JUMP_UP;
			jump_time_ = 0.0f;
			//�㏸
			speed_.y = PLAYER_JUMP_VAL;
		}
	}

	//�v���C���[�W�����v�㏸��
	if (player_state_ == PLAYER_STATE_JUMP_UP)
	{
		//�㏸
		/*speed_.y = PLAYER_JUMP_VAL;*/
		jump_time_ += 1.0f / FRAME_RATE;
		speed_.y -= GRAVITY;

		//�W�����v���Ԃ��߂�����
		/*if (speed_.y <= 0.0f)
		{
			jump_time_ = 0.0f;
			speed_.y = 0.0f;
			player_state_ = PLAYER_STATE_NORMAL;
		}*/
	}

	if (pos_.y > 0.0f && player_state_ == PLAYER_STATE_JUMP_UP)
	{
		jump_time_ = 0.0f;
		speed_.y = 0.0f;
		player_state_ = PLAYER_STATE_NORMAL;
	}
}

//�U��1
void CPlayer::CalcAttack1()
{
	if (g_input.IsPush(KEY_J))
	{
		player_state_ = PLAYER_STATE_ATTACK1;
		Request(ATTACK_1, ANIM_SPD);
	}
}

//�U��2
void CPlayer::CalcAttack2()
{
	if (GetAnimType() == ATTACK_1)
	{
		//25�t���[���ڍs�͎��̍U�����󂯕t����
		if (m_animCount[ANIM_MAIN] >= 25.0f)
		{
			if (g_input.IsPush(KEY_J))
			{
				IsCombo_ = true;
			}
		}
	}

	//���ݍĐ��̃A�j�����I���Ƃ�
	if (MV1GetAnimTotalTime(handle_, m_animIdx[ANIM_MAIN]) <= m_animCount[ANIM_MAIN])
	{
		if (IsCombo_)
		{
			player_state_ = PLAYER_STATE_ATTACK2;
			Request(ATTACK_2, ANIM_SPD);
			IsCombo_ = false;

		}
		else
		{
			player_state_ = PLAYER_STATE_NORMAL;
			Request(WAIT, ANIM_SPD);
			IsCombo_ = false;
		}

	}
	
}

//�R���{�I��
void CPlayer::EndCombo()
{
	if (GetAnimType() == ATTACK_2)
	{
		//8�t���[���ڍs�͎��̍U�����󂯕t����
		if (m_animCount[ANIM_MAIN] >= 8.0f)
		{
			if (g_input.IsPush(KEY_J))
			{
				IsCombo_ = true;
			}
		}
	}
	if (m_animCount[ANIM_MAIN] >= 26.0f)
	{
		if (IsCombo_ == true)
		{
			player_state_ = PLAYER_STATE_ATTACK1;
			Request(ATTACK_1, ANIM_SPD);
			IsCombo_ = false;
		}
	}
	//���ݍĐ��̃A�j�����I���Ƃ�
	if (MV1GetAnimTotalTime(handle_, m_animIdx[ANIM_MAIN]) <= m_animCount[ANIM_MAIN])
	{
		/*if (IsCombo_)
		{
			player_state_ = PLAYER_STATE_ATTACK1;
			Request(ATTACK_1, ANIM_SPD);
			IsCombo_ = false;
		}
		else*/
		{
			player_state_ = PLAYER_STATE_NORMAL;
			Request(WAIT, ANIM_SPD);
			IsCombo_ = false;
		}
	}
}

//�v���C���[�̍U������
bool CPlayer::IsAttack()
{
	int  state = player_state_;
	if (state == PLAYER_STATE_ATTACK1 || state == PLAYER_STATE_ATTACK2)
	{
		return true;
	}

	return false;
}

//�U���������W���擾
VECTOR CPlayer::GetAttackPos()
{
	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);
	//�U��1�̂Ƃ�
	if (player_state_ == PLAYER_STATE_ATTACK1)
	{
		pos = GetLeftHand();
	}
	//�U��2�̂Ƃ�
	else if (player_state_ == PLAYER_STATE_ATTACK2)
	{
		pos = GetRightHand();
	}
	return pos;
}

//�U�������蔻��̍��蒆�S�ʒu�擾
VECTOR	CPlayer::GetLeftHand()
{
	VECTOR	center = MV1GetFramePosition(handle_, 14);
	return center;
}

//�U�������蔻��̉E�蒆�S�ʒu�擾
VECTOR	CPlayer::GetRightHand()
{
	VECTOR	center = MV1GetFramePosition(handle_, 50);
	return center;
}

void CPlayer::OnEnCollisionEnter(CEnemy* another)
{

}