#include "Collision.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Player/PlayerManager.h"

bool CCollision::IsHitTriangleXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// �O�p�`�̕ӂɉ������x�N�g��
	VECTOR vecAB = MyMath::VecCreate(vertexA, vertexB); vecAB.z = 0.0f;
	VECTOR vecBC = MyMath::VecCreate(vertexB, vertexC); vecBC.z = 0.0f;
	VECTOR vecCA = MyMath::VecCreate(vertexC, vertexA); vecCA.z = 0.0f;

	// �e���_����Ώۂ܂ł̃x�N�g��
	VECTOR vecAP = MyMath::VecCreate(vertexA, point); vecAP.z = 0.0f;
	VECTOR vecBP = MyMath::VecCreate(vertexB, point); vecBP.z = 0.0f;
	VECTOR vecCP = MyMath::VecCreate(vertexC, point); vecCP.z = 0.0f;

	// �Ή�����x�N�g���ǂ����ĊO�ς��v�Z����
	VECTOR vecABAP = MyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = MyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = MyMath::VecCross(vecCA, vecCP);

	// �e�O�ς�Z������0�ȉ��ł���Γ������Ă���
	if (vecABAP.z >= 0 && vecBCBP.z >= 0 && vecCACP.z >= 0) {
		return true;
	}

	if (vecABAP.z <= 0 && vecBCBP.z <= 0 && vecCACP.z <= 0) {
		return true;
	}

	return false;
}

bool CCollision::IsHitTriangleXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// �O�p�`�̕ӂɉ������x�N�g��
	VECTOR vecAB = MyMath::VecCreate(vertexA, vertexB); vecAB.y = 0.0f;
	VECTOR vecBC = MyMath::VecCreate(vertexB, vertexC); vecBC.y = 0.0f;
	VECTOR vecCA = MyMath::VecCreate(vertexC, vertexA); vecCA.y = 0.0f;

	// �e���_����Ώۂ܂ł̃x�N�g��
	VECTOR vecAP = MyMath::VecCreate(vertexA, point); vecAP.y = 0.0f;
	VECTOR vecBP = MyMath::VecCreate(vertexB, point); vecBP.y = 0.0f;
	VECTOR vecCP = MyMath::VecCreate(vertexC, point); vecCP.y = 0.0f;

	// �Ή�����x�N�g���ǂ����ĊO�ς��v�Z����
	VECTOR vecABAP = MyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = MyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = MyMath::VecCross(vecCA, vecCP);

	// �e�O�ς�Y������0�ȉ��ł���Γ������Ă���
	if (vecABAP.y >= 0 && vecBCBP.y >= 0 && vecCACP.y >= 0) {
		return true;
	}

	if (vecABAP.y <= 0 && vecBCBP.y <= 0 && vecCACP.y <= 0) {
		return true;
	}


	return false;
}

bool CCollision::IsHitTriangleYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// �O�p�`�̕ӂɉ������x�N�g��
	VECTOR vecAB = MyMath::VecCreate(vertexA, vertexB); vecAB.x = 0.0f;
	VECTOR vecBC = MyMath::VecCreate(vertexB, vertexC); vecBC.x = 0.0f;
	VECTOR vecCA = MyMath::VecCreate(vertexC, vertexA); vecCA.x = 0.0f;

	// �e���_����Ώۂ܂ł̃x�N�g��
	VECTOR vecAP = MyMath::VecCreate(vertexA, point); vecAP.x = 0.0f;
	VECTOR vecBP = MyMath::VecCreate(vertexB, point); vecBP.x = 0.0f;
	VECTOR vecCP = MyMath::VecCreate(vertexC, point); vecCP.x = 0.0f;

	// �Ή�����x�N�g���ǂ����ĊO�ς��v�Z����
	VECTOR vecABAP = MyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = MyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = MyMath::VecCross(vecCA, vecCP);

	// �e�O�ς�X������0�ȉ��ł���Γ������Ă���
	if (vecABAP.x >= 0 && vecBCBP.x >= 0 && vecCACP.x >= 0) {
		return true;
	}

	if (vecABAP.x <= 0 && vecBCBP.x <= 0 && vecCACP.x <= 0) {
		return true;
	}

	return false;
}

bool CCollision::IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2)
{
	float w1_half = (w1 / 2);		//�Ώ�A�̉����̔����i���S����[�܂ł̒����j
	float h1_half = (h1 / 2);		//�Ώ�A�̍����̔����i���S����[�܂ł̒����j
	float d1_half = (d1 / 2);		//�Ώ�A�̉��s���̔����i���S����[�܂ł̒����j

	float x1min = v1.x - w1_half;	//�Ώ�A�̍ŏ�X
	float x1max = v1.x + w1_half;	//�Ώ�A�̍ő�X
	float y1min = v1.y - h1_half;	//�Ώ�A�̍ŏ�Y
	float y1max = v1.y + h1_half;	//�Ώ�A�̍ő�Y
	float z1min = v1.z - d1_half;	//�Ώ�A�̍ŏ�Z
	float z1max = v1.z + d1_half;	//�Ώ�A�̍ő�Z

	float w2_half = (w2 / 2);		//�Ώ�B�̉����̔����i���S����[�܂ł̒����j
	float h2_half = (h2 / 2);		//�Ώ�B�̍����̔����i���S����[�܂ł̒����j
	float d2_half = (d2 / 2);		//�Ώ�B�̉��s���̔����i���S����[�܂ł̒����j

	float x2min = v2.x - w2_half;		//�Ώ�B�̍ŏ�X
	float x2max = v2.x + w2_half;		//�Ώ�B�̍ő�X
	float y2min = v2.y - h2_half;		//�Ώ�B�̍ŏ�Y
	float y2max = v2.y + h2_half;		//�Ώ�B�̍ő�Y
	float z2min = v2.z - d2_half;		//�Ώ�B�̍ŏ�Z
	float z2max = v2.z + d2_half;		//�Ώ�B�̍ő�Z

	if (x1min < x2max && x1max > x2min && y1min < y2max && y1max > y2min && z1min < z2max && z1max > z2min)
		return true;

	return false;
}


bool CCollision::IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2)
{
	float len_x = (v2.x - v1.x) * (v2.x - v1.x);
	float len_y = (v2.y - v1.y) * (v2.y - v1.y);
	float len_z = (v2.z - v1.z) * (v2.z - v1.z);
	float len_r = (r2 + r1) * (r2 + r1);

	if (len_x + len_y + len_z <= len_r)
	{
		return true;
	}

	return false;
}

void CCollision::CheckCollision()
{
	// �}�b�v�Ƃ̓����蔻��/////////////////////////////////////////

	// �|���S�������擾
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(g_map.GetCol_handle(), -1, TRUE);

	//�v���C���[���擾
	CPlayer* player = g_player_manager.GetPlayer();
	VECTOR p_pos = player->GetPos();
	VECTOR p_forward = player->GetSpeed();

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
			if (IsHitTriangleXZ(p_pos, vertexs[0], vertexs[1], vertexs[2])) {
				// �ʂ̕��������珰�̍������v�Z
				float floor_height = MyMath::GetTriangleHeightXZ(p_pos, vertexs[0], vertexs[1], vertexs[2]);
				// �v���C���[�̑����̍��W���v�Z
				float player_bottom = p_pos.y - PLAYER_RAD;
				// �����瑫���܂ł̋������v�Z
				float dist = player_bottom - floor_height;
				// �����̕����Ⴂ�@���@�����Ə��Ƃ̋��������ꂷ���Ă��Ȃ���Ή����グ��
				if (dist < 0.0f && MyMath::Abs(dist) <= PLAYER_RAD) {
					p_pos.y = floor_height + PLAYER_RAD;
				}
			}
		}
		else if (norm.y <= MAP_CEIL_NORM_Y)
		{
			//�V��̏ꍇ
			//�O�p�`�̓����蔻��
			if (IsHitTriangleXZ(p_pos, vertexs[0], vertexs[1], vertexs[2]))
			{
				//�ʂ̕���������V��̍������v�Z
				float ceil_height = MyMath::GetTriangleHeightXZ(p_pos, vertexs[0], vertexs[1], vertexs[2]);
				//�v���C���[�̔]�V�̍��W���v�Z
				float player_top = p_pos.y + PLAYER_RAD;
				//�V�䂩��]�V�܂ł̋������v�Z
				float dist = player_top - ceil_height;
				//�]�V�̕��������@���@�]�V�ƓV��Ƃ̋��������ꂷ���Ă��Ȃ���Ή���������
				if (dist > 0.0f && MyMath::Abs(dist) <= PLAYER_RAD)
				{
					p_pos.y = ceil_height - PLAYER_RAD;
				}
			}
		}
		else
		{
			//�����łȂ���Ε�
			//�@���ƃv���C���[�̈ړ��x�N�g���������������Ă���ꍇ�̂ݔ�������
			if (MyMath::VecDot(p_forward, norm) < 0.0f)
			{
				if (MyMath::Abs(norm.z) >= MAP_WALL_NORM_Z)
				{
					//XY���ʂ̕�
					if (IsHitTriangleXY(p_pos, vertexs[0], vertexs[1], vertexs[2]))
					{
						//���ʏ�̕ǂ̍������Z�o
						float wall_height = MyMath::GetTriangleHeightXY(p_pos, vertexs[0], vertexs[1], vertexs[2]);
						//�Փ˓_�܂ł̋������Z�o
						float player_front = norm.z < 0.0f ? p_pos.z + PLAYER_RAD : p_pos.z - PLAYER_RAD;
						float dist = player_front - wall_height;
						//�ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
						if (MyMath::Abs(dist) <= PLAYER_RAD)
						{
							//�@���̌����ɋC��t���Ă߂荞��ł��邩�`�F�b�N����
							if ((norm.z < 0.0f && dist > 0.0f) || (norm.z > 0.0f && dist < 0.0f))
							{
								//�@���̕����ɂ߂荞��ł��镪���������o��
								VECTOR push = MyMath::VecScale(norm, MyMath::Abs(dist));
								p_pos = MyMath::VecAdd(p_pos, push);
							}
						}
					}
				}
				else
				{
					//YZ���ʂ̕�
					if (IsHitTriangleYZ(p_pos, vertexs[0], vertexs[1], vertexs[2]))
					{
						//���ʏ�̕ǂ̍������Z�o
						float wall_height = MyMath::GetTriangleHeightYZ(p_pos, vertexs[0], vertexs[1], vertexs[2]);
						//�Փ˓_�܂ł̋������Z�o
						float player_front = norm.x < 0.0f ? p_pos.x + PLAYER_RAD : p_pos.x - PLAYER_RAD;
						float dist = player_front - wall_height;
						//�ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
						if (MyMath::Abs(dist) <= PLAYER_RAD)
						{
							//�@���̌����ɋC��t���Ă߂荞��ł��邩�`�F�b�N����
							if ((norm.x < 0.0f && dist > 0.0f) || (norm.x > 0.0f && dist < 0.0f))
							{
								//�@���̕����ɂ߂荞��ł��镪���������o��
								VECTOR push = MyMath::VecScale(norm, MyMath::Abs(dist));
								p_pos = MyMath::VecAdd(p_pos, push);
							}
						}
					}
				}
			}
		}
	}
}