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

	// XY���ʏ�ł̎O�p�`�̓����蔻��
	// ����
	// point	:�Ώۂ̍��W
	// vertexA	:�O�p�`�̒��_A
	// vertexB	:�O�p�`�̒��_B
	// vertexC	:�O�p�`�̒��_C
	static bool IsHitTriangleXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	// XY���ʏ�ł̎O�p�`�̓����蔻��
	// ����
	// point	:�Ώۂ̍��W
	// vertexA	:�O�p�`�̒��_A
	// vertexB	:�O�p�`�̒��_B
	// vertexC	:�O�p�`�̒��_C
	static bool IsHitTriangleYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

};
#endif