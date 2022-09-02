#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "DxLib.h"

class CCollision {
public:
	// XY���ʏ�ł̎O�p�`�̓����蔻��
	// ����
	// point	:�Ώۂ̍��W
	// vertexA	:�O�p�`�̒��_A
	// vertexB	:�O�p�`�̒��_B
	// vertexC	:�O�p�`�̒��_C
	static bool IsHitTriangleXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	// XZ���ʏ�ł̎O�p�`�̓����蔻��
	// ����
	// point	:�Ώۂ̍��W
	// vertexA	:�O�p�`�̒��_A
	// vertexB	:�O�p�`�̒��_B
	// vertexC	:�O�p�`�̒��_C
	static bool IsHitTriangleXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	// YZ���ʏ�ł̎O�p�`�̓����蔻��
	// ����
	// point	:�Ώۂ̍��W
	// vertexA	:�O�p�`�̒��_A
	// vertexB	:�O�p�`�̒��_B
	// vertexC	:�O�p�`�̒��_C
	static bool IsHitTriangleYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	//�����̂̓����蔻��iAABB�j
	// v1			�c �Ώ�A��X,Y,Z���W�i���f���̒��S���W�j
	// w1, h1, d1	�c �Ώ�A��W,H,D�i�����A�����A���s���j
	// v2			�c �Ώ�B��X,Y,Z���W�i���f���̒��S���W�j
	// w2, h2, d2	�c �Ώ�B��W,H�i�����A�����A���s���j
	static bool IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2);

	//���Ƌ�
	// v1	�c �Ώ�A�̍��W
	// r1	�c �Ώ�A�̔��a
	// v2	�c �Ώ�B�̍��W
	// r2	�c �Ώ�B�̔��a
	static bool IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2);

	static void CheckCollision();

};
#endif