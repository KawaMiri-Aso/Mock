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

