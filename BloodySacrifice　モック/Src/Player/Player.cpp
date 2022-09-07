
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

//�d��
#define GRAVITY		(0.15f)

//�R���X�g���N�^
CPlayer::CPlayer()
{
	m_nHandle = 0;
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_eState = PLAYER_STATE_NORMAL;
	m_fJumpTime = 0.0f;
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{
}

//�������i�����Ȃ��j
void CPlayer::Init()
{
	//�����Ȃ��Ȃ炷�ׂă[���ɂ���
	m_nHandle = 0;
	m_vPos = VGet(0.0f, 1.0f, 0.0f);
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_fAngle = 0.0f;
	m_eState = PLAYER_STATE_NORMAL;
	m_fJumpTime = 0.0f;
}

//�������i��������j
void CPlayer::Init(VECTOR pos, VECTOR rot)
{
	//���W�Ɖ�]��ݒ�
	m_vPos = pos;
	m_vRot = rot;

	//���̓[���ɂ���
	m_fAngle = 0.0f;
	m_nHandle = 0;
	m_eState = PLAYER_STATE_NORMAL;
	m_fJumpTime = 0.0f;
}

//�ǂݍ���
void CPlayer::Load(const char* file_path)
{
	//���f���̓ǂݍ���
	m_nHandle = MV1LoadModel(file_path);
}

//�폜
void CPlayer::Delete()
{
	//���f���j��
	MV1DeleteModel(m_nHandle);

	//�폜������0�������Ă���
	m_nHandle = 0;
}

//���t���[���Ăԏ����i����j
void CPlayer::Step()
{
	//�ړ��t���O
	bool moveFlg;

	//������Ԃł͈ړ����Ă��Ȃ�
	moveFlg = false;

	//�v���C���[�ɏ�ɏd�͂�������
	m_vPos.y -= GRAVITY;

	//�ړ����x�x�N�g����������
	m_vSpeed = { 0 };

	//�v���C���[�ʏ�
	if(m_eState == PLAYER_STATE_NORMAL)
	{
		if(g_input.IsPush(KEY_SPACE))
		{
			//��Ԃ��W�����v�㏸����
			m_eState = PLAYER_STATE_JUMP_UP;
			m_fJumpTime = 0.0f;
		}
	}

	//�v���C���[�W�����v�㏸��
	if(m_eState == PLAYER_STATE_JUMP_UP)
	{
		//�㏸
		m_vPos.y += PLAYER_JUMP_VAL;
		m_fJumpTime += 1.0f / FRAME_RATE;

		//�W�����v���Ԃ��߂�����
		if(m_fJumpTime >= PLAYER_JUMP_TIME)
		{
			m_fJumpTime = 0.0f;
			m_eState = PLAYER_STATE_NORMAL;
		}
	}



	//Y�������蔻�� =====
	//�n�ʂƓ�������
	//if(m_vPos.y - PLAYER_RAD < 0.0f)
	//{
	//	m_vPos.y = PLAYER_RAD;			//�߂荞�܂Ȃ��ʒu�ɒu��
	//	m_eState = PLAYER_STATE_NORMAL;	//�ʏ��Ԃɂ��Ă���
	//}

	//�΂߈ړ�
	if (g_input.IsCont(KEY_UP) && g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_UP) && g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_up_sidle = { 0 };

		//�J�������擾
		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_up_sidle = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_up_sidle.y = 0;
		//���K��
		move_up_sidle = math->VecNormalize(move_up_sidle);
		m_vRot = move_up_sidle;
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
		m_vSpeed.x = m_result.m[3][0];
		m_vSpeed.y = m_result.m[3][1];
		m_vSpeed.z = m_result.m[3][2];

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//�ړ������ɕς���
		moveFlg = true;
	}
	else if (g_input.IsCont(KEY_DOWN) && g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_DOWN) && g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_up_sidle = { 0 };

		//�J�������擾
		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_up_sidle = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_up_sidle.y = 0;
		//���K��
		move_up_sidle = math->VecNormalize(move_up_sidle);
		m_vRot = move_up_sidle;
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
		m_vSpeed.x = m_result.m[3][0];
		m_vSpeed.y = m_result.m[3][1];
		m_vSpeed.z = m_result.m[3][2];

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//�ړ������ɕς���
		moveFlg = true;
	}
	//�J�����������Ă�������ֈړ�
	else if(g_input.IsCont(KEY_UP))
	{
		VECTOR move_up = { 0 };

		//�J�������擾
		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_up = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_up.y = 0;
		//���K��
		move_up = math->VecNormalize(move_up);
		m_vRot = move_up;
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
		m_vSpeed = move_up;

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//�ړ������ɕς���
		moveFlg = true;

	}
	//�J�����������Ă�������Ƃ͋t�ֈړ�
	else if(g_input.IsCont(KEY_DOWN))
	{
		VECTOR move_down = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_down = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_down.y = 0;
		//���K��
		move_down = math->VecNormalize(move_down);
		m_vRot = move_down;
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
		m_vSpeed = move_down;
	
		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//�ړ������ɕς���
		moveFlg = true;
	}
	//���ֈړ�
	else if(g_input.IsCont(KEY_LEFT))
	{
		VECTOR move_left = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_left = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_left.y = 0;
		//���K��
		move_left = math->VecNormalize(move_left);
		m_vRot = move_left;
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
		m_vSpeed.x = m_result.m[3][0];
		m_vSpeed.y = m_result.m[3][1];
		m_vSpeed.z = m_result.m[3][2];

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//�ړ������ɕς���
		moveFlg = true;
	}
	//�E�ֈړ�
	else if(g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_right = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_right = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y�����͏�����
		move_right.y = 0;
		//���K��
		move_right = math->VecNormalize(move_right);
		m_vRot = move_right;
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
		m_vSpeed.x = m_result.m[3][0];
		m_vSpeed.y = m_result.m[3][1];
		m_vSpeed.z = m_result.m[3][2];

		//�ړ��O�̍��W�Ƒ����ĐV���ȍ��W�𓾂�
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

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

	CheckCollision();


	
	//�v���C���[�̍��W
	MV1SetPosition(m_nHandle, m_vPos);
}

//�`��
void CPlayer::Draw()
{
	//�v���C���[�̕`��
	MV1DrawModel(m_nHandle);
}

//�㏈��
void CPlayer::Fin()
{
	//Delete���Ă΂�Ă��Ȃ��Ȃ�
	if(m_nHandle != 0)
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
	if (m_vSpeed.x != 0 || m_vSpeed.z != 0)
	{
		TargetAngle = atan2f(m_vSpeed.x, m_vSpeed.z);
	}

	// �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
	{
		DiffAngle = TargetAngle - m_fAngle;

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
	
	m_fAngle = TargetAngle - DiffAngle;

	//�v���C���[�̉�]
	MV1SetRotationXYZ(m_nHandle, VGet(0.0f, m_fAngle + DX_PI_F, 0.0f));
}

void CPlayer::CheckCollision()
{
	// �}�b�v�Ƃ̓����蔻��/////////////////////////////////////////

	// �|���S�������擾
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(g_map.GetCol_handle(), -1, TRUE);

	// �|���S���̐������J��Ԃ�
	for (int i = 0; i < polygons.PolygonNum; i++)
	{
		// �|���S�������擾����
		MV1_REF_POLYGON polygon = polygons.Polygons[i];
		// �|���S�����`������O�p�`��3���_���擾����
		VECTOR vertexs[3];
		int index = polygon.VIndex[0];
		vertexs[0] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[1];
		vertexs[1] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[2];
		vertexs[2] = polygons.Vertexs[index].Position;

		// �|���S���@�����Z�o����
		VECTOR norm = MyMath::GetPolygonNormalVec(vertexs[0], vertexs[1], vertexs[2]);
		//�@����Y������MAP_FLOOR_NORM_Y�ȏ�ł���Ώ�
		if (norm.y >= MAP_FLOOR_NORM_Y) {
			// �O�p�`�̓����蔻��
			if (CCollision::IsHitTriangleXZ(m_vPos, vertexs[0], vertexs[1], vertexs[2])) {
				// �ʂ̕��������珰�̍������v�Z
				float floor_height = MyMath::GetTriangleHeightXZ(m_vPos, vertexs[0], vertexs[1], vertexs[2]);
				// �v���C���[�̑����̍��W���v�Z
				float player_bottom = m_vPos.y - PLAYER_RAD;
				// �����瑫���܂ł̋������v�Z
				float dist = player_bottom - floor_height;
				// �����̕����Ⴂ�@���@�����Ə��Ƃ̋��������ꂷ���Ă��Ȃ���Ή����グ��
				if (dist < 0.0f && MyMath::Abs(dist) <= PLAYER_RAD) {
					m_vPos.y = floor_height + PLAYER_RAD;
				}
			}
		}
		else if (norm.y <= MAP_CEIL_NORM_Y)
		{
			//�V��̏ꍇ
			//�O�p�`�̓����蔻��
			if (CCollision::IsHitTriangleXZ(m_vPos, vertexs[0], vertexs[1], vertexs[2]))
			{
				//�ʂ̕���������V��̍������v�Z
				float ceil_height = MyMath::GetTriangleHeightXZ(m_vPos, vertexs[0], vertexs[1], vertexs[2]);
				//�v���C���[�̔]�V�̍��W���v�Z
				float player_top = m_vPos.y + PLAYER_RAD;
				//�V�䂩��]�V�܂ł̋������v�Z
				float dist = player_top - ceil_height;
				//�]�V�̕��������@���@�]�V�ƓV��Ƃ̋��������ꂷ���Ă��Ȃ���Ή���������
				if (dist > 0.0f && MyMath::Abs(dist) <= PLAYER_RAD)
				{
					m_vPos.y = ceil_height - PLAYER_RAD;
				}
			}
		}
		else
		{
			//�����łȂ���Ε�
			//�@���ƃv���C���[�̈ړ��x�N�g���������������Ă���ꍇ�̂ݔ�������
			if (MyMath::VecDot(m_vSpeed, norm) < 0.0f)
			{
				if (MyMath::Abs(norm.z) >= MAP_WALL_NORM_Z)
				{
					//XY���ʂ̕�
					if (CCollision::IsHitTriangleXY(m_vPos, vertexs[0], vertexs[1], vertexs[2]))
					{
						//���ʏ�̕ǂ̍������Z�o
						float wall_height = MyMath::GetTriangleHeightXY(m_vPos, vertexs[0], vertexs[1], vertexs[2]);
						//�Փ˓_�܂ł̋������Z�o
						float player_front = norm.z < 0.0f ? m_vPos.z + PLAYER_RAD : m_vPos.z - PLAYER_RAD;
						float dist = player_front - wall_height;
						//�ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
						if (MyMath::Abs(dist) <= PLAYER_RAD)
						{
							//�@���̌����ɋC��t���Ă߂荞��ł��邩�`�F�b�N����
							if ((norm.z < 0.0f && dist > 0.0f) || (norm.z > 0.0f && dist < 0.0f))
							{
								//�@���̕����ɂ߂荞��ł��镪���������o��
								VECTOR push = MyMath::VecScale(norm, MyMath::Abs(dist));
								m_vPos = MyMath::VecAdd(m_vPos, push);
							}
						}
					}
				}
				else
				{
					//YZ���ʂ̕�
					if (CCollision::IsHitTriangleYZ(m_vPos, vertexs[0], vertexs[1], vertexs[2]))
					{
						//���ʏ�̕ǂ̍������Z�o
						float wall_height = MyMath::GetTriangleHeightYZ(m_vPos, vertexs[0], vertexs[1], vertexs[2]);
						//�Փ˓_�܂ł̋������Z�o
						float player_front = norm.x < 0.0f ? m_vPos.x + PLAYER_RAD : m_vPos.x - PLAYER_RAD;
						float dist = player_front - wall_height;
						//�ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
						if (MyMath::Abs(dist) <= PLAYER_RAD)
						{
							//�@���̌����ɋC��t���Ă߂荞��ł��邩�`�F�b�N����
							if ((norm.x < 0.0f && dist > 0.0f) || (norm.x > 0.0f && dist < 0.0f))
							{
								//�@���̕����ɂ߂荞��ł��镪���������o��
								VECTOR push = MyMath::VecScale(norm, MyMath::Abs(dist));
								m_vPos = MyMath::VecAdd(m_vPos, push);
							}
						}
					}
				}
			}
		}
	}
}

bool CPlayer::IsPushStone()
{
	if (CCollision::IsHitSphere(m_vPos, PLAYER_RAD, g_stone_trap.GetPos(), STONE_RAD))
	{
		return true;
	}
	else
	{
		return false;
	}
}