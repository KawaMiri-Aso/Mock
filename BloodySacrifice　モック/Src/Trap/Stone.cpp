#include "Stone.h"
#include "../Collision/Collision.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Player/PlayerManager.h"

//�d��
#define GRAVITY		(2.15f)

CStoneTrap g_stone_trap;

CStoneTrap::CStoneTrap()
{
	m_nHandle = 0;
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_eState = STONE_TRAP_STATE_BEFORE;
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
}

void CStoneTrap::Init(VECTOR pos)
{
	m_nHandle = MV1LoadModel("Data/Model/Trap/Stone/Stone.x");
	m_vPos = pos;
	m_eState = STONE_TRAP_STATE_BEFORE;
}

void CStoneTrap::Step()
{
	//��ɏd�͂�������
	m_vPos.y -= GRAVITY;
	CheckCollision();

	CPlayer* player = g_player_manager.GetPlayer();
	if (m_eState == STONE_TRAP_STATE_BEFORE)
	{
		float bottom = m_vPos.y - STONE_RAD;

		if (bottom > 0)
		{
			if (CCollision::IsHitRect(m_vPos, STONE_W, STONE_H, STONE_D, player->GetPos(), PLAYER_W, PLAYER_H, PLAYER_D))
			{
				m_vPos = MyMath::VecAdd(m_vPos, player->GetSpeed());
			}
		}
		else
		{
			m_eState = STONE_TRAP_STATE_AFTER;
		}
	}
	

	//���W�ݒ� =====

	MV1SetPosition(m_nHandle, m_vPos);
}

void CStoneTrap::Draw()
{
	MV1DrawModel(m_nHandle);
}

void CStoneTrap::Fin()
{
	MV1DeleteModel(m_nHandle);
}

void CStoneTrap::CheckCollision()
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
				float player_bottom = m_vPos.y - STONE_RAD;
				// �����瑫���܂ł̋������v�Z
				float dist = player_bottom - floor_height;
				// �����̕����Ⴂ�@���@�����Ə��Ƃ̋��������ꂷ���Ă��Ȃ���Ή����グ��
				if (dist < 0.0f && MyMath::Abs(dist) <= STONE_RAD) {
					m_vPos.y = floor_height + STONE_RAD;
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
				float player_top = m_vPos.y + STONE_RAD;
				//�V�䂩��]�V�܂ł̋������v�Z
				float dist = player_top - ceil_height;
				//�]�V�̕��������@���@�]�V�ƓV��Ƃ̋��������ꂷ���Ă��Ȃ���Ή���������
				if (dist > 0.0f && MyMath::Abs(dist) <= STONE_RAD)
				{
					m_vPos.y = ceil_height - STONE_RAD;
				}
			}
		}
		else
		{
			//�����łȂ���Ε�
			//�@���ƃv���C���[�̈ړ��x�N�g���������������Ă���ꍇ�̂ݔ�������
			if (MyMath::VecDot(m_vRot, norm) < 0.0f)
			{
				if (MyMath::Abs(norm.z) >= MAP_WALL_NORM_Z)
				{
					//XY���ʂ̕�
					if (CCollision::IsHitTriangleXY(m_vPos, vertexs[0], vertexs[1], vertexs[2]))
					{
						//���ʏ�̕ǂ̍������Z�o
						float wall_height = MyMath::GetTriangleHeightXY(m_vPos, vertexs[0], vertexs[1], vertexs[2]);
						//�Փ˓_�܂ł̋������Z�o
						float player_front = norm.z < 0.0f ? m_vPos.z + STONE_RAD : m_vPos.z - STONE_RAD;
						float dist = player_front - wall_height;
						//�ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
						if (MyMath::Abs(dist) <= STONE_RAD)
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
						float player_front = norm.x < 0.0f ? m_vPos.x + STONE_RAD : m_vPos.x - STONE_RAD;
						float dist = player_front - wall_height;
						//�ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
						if (MyMath::Abs(dist) <= STONE_RAD)
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