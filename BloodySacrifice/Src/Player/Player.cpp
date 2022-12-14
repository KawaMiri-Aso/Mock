
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

	//�v���C���[�ɏ�ɏd�͂�������
	/*pos_.y -= GRAVITY;*/
	speed_.y -= GRAVITY;
	pos_.y += speed_.y;

	////�ړ����x�x�N�g����������
	//speed_ = { 0 };

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

	//�ړ�����
	CalcMove();

	////�΂߈ړ�
	//if (g_input.IsCont(KEY_W) && g_input.IsCont(KEY_A) || g_input.IsCont(KEY_W) && g_input.IsCont(KEY_D))
	//{
	//	VECTOR move_up_sidle = { 0 };

	//	//�J�������擾
	//	CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

	//	//�J�����̎��_�A�����_����x�N�g�����쐬
	//	move_up_sidle = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
	//	//Y�����͏�����
	//	move_up_sidle.y = 0;
	//	//���K��
	//	move_up_sidle = math->VecNormalize(move_up_sidle);
	//	//�����������|���Z
	//	if (g_input.IsCont(KEY_LSHIFT))
	//	{
	//		move_up_sidle = math->VecScale(move_up_sidle, PLAYER_RUN_SPEED);
	//		player_state_ = PLAYER_STATE_RUN;
	//	}
	//	else
	//	{
	//		move_up_sidle = math->VecScale(move_up_sidle, PLAYER_WALK_SPEED);
	//		player_state_ = PLAYER_STATE_WALK;
	//	}
	//	
	//	//���s�ړ��s��擾
	//	MATRIX m_dir = MGetTranslate(move_up_sidle);
	//	MATRIX m_rotY;
	//	//Y����]�s��擾
	//	if (!g_input.IsCont(KEY_D))
	//	{
	//		m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING_HALF);
	//	}
	//	else
	//	{
	//		m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING_HALF);
	//	}
	//	//�s�񓯎m�̊|���Z
	//	MATRIX m_result = MMult(m_dir, m_rotY);

	//	//�ړ����x�x�N�g���ɓ����
	//	speed_.x = m_result.m[3][0];
	//	speed_.y = m_result.m[3][1];
	//	speed_.z = m_result.m[3][2];

	//	//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	/*pos_ = math->VecAdd(pos_, speed_);*/

	//	//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	pos_.x += speed_.x;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.x -= speed_.x;
	//	}
	//	pos_.y += speed_.y;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.y -= speed_.y;
	//	}
	//	pos_.z += speed_.z;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.z -= speed_.z;
	//	}

	//	//�ړ������ɕς���
	//	moveFlg = true;
	//	//player_state_ = PLAYER_STATE_WALK;
	//	
	//}
	//else if (g_input.IsCont(KEY_S) && g_input.IsCont(KEY_A) || g_input.IsCont(KEY_S) && g_input.IsCont(KEY_D))
	//{
	//	VECTOR move_up_sidle = { 0 };

	//	//�J�������擾
	//	CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

	//	//�J�����̎��_�A�����_����x�N�g�����쐬
	//	move_up_sidle = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
	//	//Y�����͏�����
	//	move_up_sidle.y = 0;
	//	//���K��
	//	move_up_sidle = math->VecNormalize(move_up_sidle);
	//	//�����������|���Z
	//	if (g_input.IsCont(KEY_LSHIFT))
	//	{
	//		move_up_sidle = math->VecScale(move_up_sidle, -PLAYER_RUN_SPEED);
	//		player_state_ = PLAYER_STATE_RUN;
	//	}
	//	else
	//	{
	//		move_up_sidle = math->VecScale(move_up_sidle, -PLAYER_WALK_SPEED);
	//		player_state_ = PLAYER_STATE_WALK;
	//	}

	//	//���s�ړ��s��擾
	//	MATRIX m_dir = MGetTranslate(move_up_sidle);
	//	MATRIX m_rotY;
	//	//Y����]�s��擾
	//	if (!g_input.IsCont(KEY_D))
	//	{
	//		m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING_HALF);
	//	}
	//	else
	//	{
	//		m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING_HALF);
	//	}
	//	//�s�񓯎m�̊|���Z
	//	MATRIX m_result = MMult(m_dir, m_rotY);

	//	//�ړ����x�x�N�g���ɓ����
	//	speed_.x = m_result.m[3][0];
	//	speed_.y = m_result.m[3][1];
	//	speed_.z = m_result.m[3][2];

	//	//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	/*pos_ = math->VecAdd(pos_, speed_);*/

	//	//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	pos_.x += speed_.x;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.x -= speed_.x;
	//	}
	//	pos_.y += speed_.y;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.y -= speed_.y;
	//	}
	//	pos_.z += speed_.z;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.z -= speed_.z;
	//	}

	//	//�ړ������ɕς���
	//	moveFlg = true;
	//	//player_state_ = PLAYER_STATE_WALK;
	//}
	////�J�����������Ă�������ֈړ�
	//else if(g_input.IsCont(KEY_W))
	//{
	//	VECTOR move_up = { 0 };

	//	//�J�������擾
	//	CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

	//	//�J�����̎��_�A�����_����x�N�g�����쐬
	//	move_up = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
	//	//Y�����͏�����
	//	move_up.y = 0;
	//	//���K��
	//	move_up = math->VecNormalize(move_up);
	//	//�����������|���Z
	//	if (g_input.IsCont(KEY_LSHIFT))
	//	{
	//		move_up = math->VecScale(move_up, PLAYER_RUN_SPEED);
	//		player_state_ = PLAYER_STATE_RUN;
	//	}
	//	else
	//	{
	//		move_up = math->VecScale(move_up, PLAYER_WALK_SPEED);
	//		player_state_ = PLAYER_STATE_WALK;
	//	}

	//	//�ړ����x�x�N�g���ɓ����
	//	speed_ = move_up;

	//	//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	pos_.x += speed_.x;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.x -= speed_.x;
	//	}
	//	pos_.y += speed_.y;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.y -= speed_.y;
	//	}
	//	pos_.z += speed_.z;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.z -= speed_.z;
	//	}

	//	//�ړ������ɕς���
	//	moveFlg = true;
	//	//player_state_ = PLAYER_STATE_WALK;

	//}
	////�J�����������Ă�������Ƃ͋t�ֈړ�
	//else if(g_input.IsCont(KEY_S))
	//{
	//	VECTOR move_down = { 0 };

	//	//�J�������擾
	//	CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

	//	//�J�����̎��_�A�����_����x�N�g�����쐬
	//	move_down = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
	//	//Y�����͏�����
	//	move_down.y = 0;
	//	//���K��
	//	move_down = math->VecNormalize(move_down);
	//	//�����������|���Z
	//	if (g_input.IsCont(KEY_LSHIFT))
	//	{
	//		move_down = math->VecScale(move_down, -PLAYER_RUN_SPEED);
	//		player_state_ = PLAYER_STATE_RUN;
	//	}
	//	else
	//	{
	//		move_down = math->VecScale(move_down, -PLAYER_WALK_SPEED);
	//		player_state_ = PLAYER_STATE_WALK;
	//	}

	//	//�ړ����x�x�N�g���ɓ����
	//	speed_ = move_down;
	//
	//	//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	/*pos_ = math->VecAdd(pos_, speed_);*/

	//		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	pos_.x += speed_.x;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.x -= speed_.x;
	//	}
	//	pos_.y += speed_.y;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.y -= speed_.y;
	//	}
	//	pos_.z += speed_.z;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.z -= speed_.z;
	//	}

	//	//�ړ������ɕς���
	//	moveFlg = true;
	//	//player_state_ = PLAYER_STATE_WALK;
	//}
	////���ֈړ�
	//else if(g_input.IsCont(KEY_A))
	//{
	//	VECTOR move_left = { 0 };

	//	//�J�������擾
	//	CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

	//	//�J�����̎��_�A�����_����x�N�g�����쐬
	//	move_left = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
	//	//Y�����͏�����
	//	move_left.y = 0;
	//	//���K��
	//	move_left = math->VecNormalize(move_left);
	//	//�����������|���Z
	//	if (g_input.IsCont(KEY_LSHIFT))
	//	{
	//		move_left = math->VecScale(move_left, -PLAYER_RUN_SPEED);
	//		player_state_ = PLAYER_STATE_RUN;
	//	}
	//	else
	//	{
	//		move_left = math->VecScale(move_left, -PLAYER_WALK_SPEED);
	//		player_state_ = PLAYER_STATE_WALK;
	//	}
	//	
	//	//���s�ړ��s��擾
	//	MATRIX m_dir = MGetTranslate(move_left);
	//	//Y����]�s��擾
	//	MATRIX m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING);
	//	//�e�s�������
	//	MATRIX m_result = MMult(m_dir, m_rotY);

	//	//�ړ����x�x�N�g���ɓ����
	//	speed_.x = m_result.m[3][0];
	//	speed_.y = m_result.m[3][1];
	//	speed_.z = m_result.m[3][2];

	//	//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	/*pos_ = math->VecAdd(pos_, speed_);*/

	//	//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	pos_.x += speed_.x;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.x -= speed_.x;
	//	}
	//	pos_.y += speed_.y;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.y -= speed_.y;
	//	}
	//	pos_.z += speed_.z;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.z -= speed_.z;
	//	}

	//	//�ړ������ɕς���
	//	moveFlg = true;
	//	//player_state_ = PLAYER_STATE_WALK;
	//}
	////�E�ֈړ�
	//else if(g_input.IsCont(KEY_D))
	//{
	//	VECTOR move_right = { 0 };

	//	//�J�������擾
	//	CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

	//	//�J�����̎��_�A�����_����x�N�g�����쐬
	//	move_right = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
	//	//Y�����͏�����
	//	move_right.y = 0;
	//	//���K��
	//	move_right = math->VecNormalize(move_right);
	//	//�����������|���Z
	//	if (g_input.IsCont(KEY_LSHIFT))
	//	{
	//		move_right = math->VecScale(move_right, -PLAYER_RUN_SPEED);
	//		player_state_ = PLAYER_STATE_RUN;
	//	}
	//	else
	//	{
	//		move_right = math->VecScale(move_right, -PLAYER_WALK_SPEED);
	//		player_state_ = PLAYER_STATE_WALK;
	//	}

	//	//���s�ړ��s��
	//	MATRIX m_dir = MGetTranslate(move_right);
	//	MATRIX m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING);
	//	MATRIX m_result = MMult(m_dir, m_rotY);

	//	//�ړ����x�x�N�g���ɓ����
	//	speed_.x = m_result.m[3][0];
	//	speed_.y = m_result.m[3][1];
	//	speed_.z = m_result.m[3][2];

	//	//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	/*pos_ = math->VecAdd(pos_, speed_);*/

	//	//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
	//	pos_.x += speed_.x;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.x -= speed_.x;
	//	}
	//	pos_.y += speed_.y;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.y -= speed_.y;
	//	}
	//	pos_.z += speed_.z;
	//	if (CCollision::IsHitSphere(pos_, PLAYER_RAD, g_totem.GetPos(), TOTEM_RAD))
	//	{
	//		pos_.z -= speed_.z;
	//	}

	//	//�ړ������ɕς���
	//	moveFlg = true;
	//	//player_state_ = PLAYER_STATE_WALK;
	//}

	//���W�ݒ� =====
	
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

	//�v���C���[�̍��W
	MV1SetPosition(handle_, pos_);



	//�v���C���[�ɏ�ɏd�͂�������
	/*pos_.y -= GRAVITY;*/
	speed_.y -= GRAVITY;
	pos_.y += speed_.y;
	SetPos(pos_);

	//���Ƃ̓����蔻��
	VECTOR vVec;
	vVec = g_map.HitCheck(pos_, PLAYER_RAD);
	pos_ = VAdd(pos_, vVec);
	/*if (vVec.y > 0.0f && player_state_ == PLAYER_STATE_JUMP_UP)
	{
		jump_time_ = 0.0f;
		speed_.y = 0.0f;
		player_state_ = PLAYER_STATE_NORMAL;
	}*/

	switch (player_state_)
	{
	case PLAYER_STATE_NORMAL:
		Request(WAIT, ANIM_SPD);
		break;
	case PLAYER_STATE_WALK:
		Request(WALK, ANIM_SPD);
		break;
	case PLAYER_STATE_RUN:
		Request(RUN, ANIM_SPD);
		break;
	case PLAYER_STATE_JUMP_UP:
		break;
	case PLAYER_STATE_ATTACK:
		Request(ATTACK_1, ANIM_SPD);
		break;
	case PLAYER_STATE_DEAD:
		Request(DEAD, ANIM_SPD);
		break;
	default:
		break;
	}

	AnimUpdate();
}

//�`��
void CPlayer::Draw()
{
	//�v���C���[�̕`��
	MV1DrawModel(handle_);

#ifdef DEBUG
	DrawFormatString(10, 74, GetColor(255, 128, 0), "�v���C���[HP�F%d", hp_);
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


//�v���C���[�̍U������
void CPlayer::IsAttack()
{
	if (speed_.x == 0.0f && speed_.y == 0.0f && speed_.z == 0.0f)
	{
		if (g_input.IsCont(KEY_LSHIFT))
		{

		}
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

////�ҋ@����
//void CPlayer::ExecWait()
//{
//	//�ʏ�U��
//	if (g_input.IsPush(KEY_Z))
//	{
//		Request(ATTACK_1, ANIM_SPD);
//	}
//	//�W�����v
//	else if (g_input.IsPush(KEY_SPACE))
//	{
//		//�W�����v�A�j���̃��N�G�X�g
//	}
//	//�����E����
//	else
//	{
//		VECTOR spd = GetSpeed();
//		//�ړ����ĂȂ���Αҋ@
//		if (speed_.x == 0.0f && speed_.y == 0.0f && speed_.z == 0.0f)
//		{
//			Request(WAIT, ANIM_SPD);
//		}
//		else
//		{
//			//�V�t�g�L�[�������Ă����瑖��
//			if (g_input.IsCont(KEY_LSHIFT))
//			{
//				Request(RUN, ANIM_SPD);
//				spd = math->VecScale(spd, PLAYER_RUN_SPEED);
//			}
//			//�����Ȃ���Ε���
//			else
//			{
//				Request(WALK, ANIM_SPD);
//				spd = math->VecScale(spd, PLAYER_WALK_SPEED);
//			}
//			CalcSpeed(spd);
//		}
//	}
//}
//
////��������
//void CPlayer::ExecWalk()
//{
//	//�ʏ�U��
//	if (g_input.IsPush(KEY_Z))
//	{
//		Request(ATTACK_1, ANIM_SPD);
//	}
//	//�W�����v
//	else if (g_input.IsPush(KEY_SPACE))
//	{
//		//�W�����v�A�j���̃��N�G�X�g
//	}
//	//�����E����
//	else
//	{
//		VECTOR spd = GetSpeed();
//		//�ړ����ĂȂ���Αҋ@
//		if (speed_.x == 0.0f && speed_.y == 0.0f && speed_.z == 0.0f)
//		{
//			Request(WAIT, ANIM_SPD);
//		}
//		else
//		{
//			//�V�t�g�L�[�������Ă����瑖��
//			if (g_input.IsCont(KEY_LSHIFT))
//			{
//				Request(RUN, ANIM_SPD);
//				spd = math->VecScale(spd, PLAYER_RUN_SPEED);
//			}
//			//�����Ȃ���Ε���
//			else
//			{
//				spd = math->VecScale(spd, PLAYER_WALK_SPEED);
//			}
//			CalcSpeed(spd);
//		}
//	}
//}
//
////���菈��
//void CPlayer::ExecRun()
//{
//	//�ʏ�U��
//	if (g_input.IsPush(KEY_Z))
//	{
//		Request(ATTACK_1, ANIM_SPD);
//	}
//	//�W�����v
//	else if (g_input.IsPush(KEY_SPACE))
//	{
//		//�W�����v�A�j���̃��N�G�X�g
//	}
//	//�����E����
//	else
//	{
//		VECTOR spd = GetSpeed();
//		//�ړ����ĂȂ���Αҋ@
//		if (speed_.x == 0.0f && speed_.y == 0.0f && speed_.z == 0.0f)
//		{
//			Request(WAIT, ANIM_SPD);
//		}
//		else
//		{
//			//�V�t�g�L�[�������Ă����瑖��
//			if (g_input.IsCont(KEY_LSHIFT))
//			{
//				spd = math->VecScale(spd, PLAYER_RUN_SPEED);
//			}
//			//�����Ȃ���Ε���
//			else
//			{
//				Request(WALK, ANIM_SPD);
//				spd = math->VecScale(spd, PLAYER_WALK_SPEED);
//			}
//			CalcSpeed(spd);
//		}
//	}
//}

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

