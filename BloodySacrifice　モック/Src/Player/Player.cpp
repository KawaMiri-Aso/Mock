
//Player.cpp
//�v���C���[�֘A

#include <math.h>
#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../MyMath/MyMath.h"
#include "../Collision/Collision.h"
#include "../Map/Map.h"
#include "../Trap/Stone.h"

MyMath* math;

//�R���X�g���N�^
CPlayer::CPlayer()
{
	handle_ = 0;
	memset(&pos_, 0, sizeof(VECTOR));
	player_state_ = PLAYER_STATE_NORMAL;
	jump_time_ = 0.0f;
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
}

//�ǂݍ���
void CPlayer::Load()
{
	//���f���̓ǂݍ���
	handle_ = MV1LoadModel("Data/Model/Player/player-mock.x");
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

	//�v���C���[�ɏ�ɏd�͂�������
	pos_.y -= GRAVITY;

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
		}
	}

	//�v���C���[�W�����v�㏸��
	if(player_state_ == PLAYER_STATE_JUMP_UP)
	{
		//�㏸
		pos_.y += PLAYER_JUMP_VAL;
		jump_time_ += 1.0f / FRAME_RATE;

		//�W�����v���Ԃ��߂�����
		if(jump_time_ >= PLAYER_JUMP_TIME)
		{
			jump_time_ = 0.0f;
			player_state_ = PLAYER_STATE_NORMAL;
		}
	}

	//�΂߈ړ�
	if (g_input.IsCont(KEY_UP) && g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_UP) && g_input.IsCont(KEY_RIGHT))
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
		if (!IsPushStone())
		{
			move_up_sidle = math->VecScale(move_up_sidle, PLAYER_WALK_SPEED);
		}
		else
		{
			move_up_sidle = math->VecScale(move_up_sidle, PLAYER_WALK_SPEED_HALF);
		}

		//���s�ړ��s��擾
		MATRIX m_dir = MGetTranslate(move_up_sidle);
		MATRIX m_rotY;
		//Y����]�s��擾
		if (!g_input.IsCont(KEY_RIGHT))
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
		pos_ = math->VecAdd(pos_, speed_);

		//�ړ������ɕς���
		moveFlg = true;
	}
	else if (g_input.IsCont(KEY_DOWN) && g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_DOWN) && g_input.IsCont(KEY_RIGHT))
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
		if (!IsPushStone())
		{
			move_up_sidle = math->VecScale(move_up_sidle, -PLAYER_WALK_SPEED);
		}
		else
		{
			move_up_sidle = math->VecScale(move_up_sidle, -PLAYER_WALK_SPEED_HALF);
		}

		//���s�ړ��s��擾
		MATRIX m_dir = MGetTranslate(move_up_sidle);
		MATRIX m_rotY;
		//Y����]�s��擾
		if (!g_input.IsCont(KEY_RIGHT))
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
		pos_ = math->VecAdd(pos_, speed_);

		//�ړ������ɕς���
		moveFlg = true;
	}
	//�J�����������Ă�������ֈړ�
	else if(g_input.IsCont(KEY_UP))
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
		if (!IsPushStone())
		{
			move_up = math->VecScale(move_up, PLAYER_WALK_SPEED);
		}
		else
		{
			move_up = math->VecScale(move_up, PLAYER_WALK_SPEED_HALF);
		}

		//�ړ����x�x�N�g���ɓ����
		speed_ = move_up;

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		pos_ = math->VecAdd(pos_, speed_);

		//�ړ������ɕς���
		moveFlg = true;

	}
	//�J�����������Ă�������Ƃ͋t�ֈړ�
	else if(g_input.IsCont(KEY_DOWN))
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
		if (!IsPushStone())
		{
			move_down = math->VecScale(move_down, -PLAYER_WALK_SPEED);
		}
		else
		{
			move_down = math->VecScale(move_down, -PLAYER_WALK_SPEED_HALF);
		}

		//�ړ����x�x�N�g���ɓ����
		speed_ = move_down;
	
		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		pos_ = math->VecAdd(pos_, speed_);

		//�ړ������ɕς���
		moveFlg = true;
	}
	//���ֈړ�
	else if(g_input.IsCont(KEY_LEFT))
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
		if (!IsPushStone())
		{
			move_left = math->VecScale(move_left, -PLAYER_WALK_SPEED);
		}
		else
		{
			move_left = math->VecScale(move_left, -PLAYER_WALK_SPEED_HALF);
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
		pos_ = math->VecAdd(pos_, speed_);

		//�ړ������ɕς���
		moveFlg = true;
	}
	//�E�ֈړ�
	else if(g_input.IsCont(KEY_RIGHT))
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
		if (!IsPushStone())
		{
			move_right = math->VecScale(move_right, -PLAYER_WALK_SPEED);
		}
		else
		{
			move_right = math->VecScale(move_right, -PLAYER_WALK_SPEED_HALF);
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
		pos_ = math->VecAdd(pos_, speed_);

		//�ړ������ɕς���
		moveFlg = true;
	}

	//���W�ݒ� =====
	
	//�ړ����ĂȂ���Ή�]���������Ȃ�
	if (moveFlg)
	{
		//�v���C���[�̉�]
		AngleProcess();
	}

	VECTOR vVec;
	vVec = g_map.HitCheck(pos_, PLAYER_RAD);
	pos_ = VAdd(pos_, vVec);

	//�v���C���[�̍��W
	MV1SetPosition(handle_, pos_);
}

//�`��
void CPlayer::Draw()
{
	//�v���C���[�̕`��
	MV1DrawModel(handle_);
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
		DiffAngle -= PLAYER_WALK_SPEED;
		if (DiffAngle < 0.0f)
		{
			DiffAngle = 0.0f;
		}
	}
	else
	{
		// �����}�C�i�X�̏ꍇ�͑���
		DiffAngle += PLAYER_WALK_SPEED;
		if (DiffAngle > 0.0f)
		{
			DiffAngle = 0.0f;
		}
	}
	
	angle_ = TargetAngle - DiffAngle;

	//�v���C���[�̉�]
	MV1SetRotationXYZ(handle_, VGet(0.0f, angle_ + DX_PI_F, 0.0f));
}

bool CPlayer::IsPushStone()
{
	//�₪���ŏ�ԂłȂ�������
	if (g_stone_trap.GetState() != STONE_TRAP_STATE_OUT)
	{
		//�v���C���[�Ɗ₪����������
		if (CCollision::IsHitSphere(pos_, PLAYER_W * 0.5f, g_stone_trap.GetPos(), STONE_RAD))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}
