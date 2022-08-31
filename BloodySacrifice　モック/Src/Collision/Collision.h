#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "DxLib.h"

class CCollision {
public:
	// XY平面上での三角形の当たり判定
	// 引数
	// point	:対象の座標
	// vertexA	:三角形の頂点A
	// vertexB	:三角形の頂点B
	// vertexC	:三角形の頂点C
	static bool IsHitTriangleXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	// XY平面上での三角形の当たり判定
	// 引数
	// point	:対象の座標
	// vertexA	:三角形の頂点A
	// vertexB	:三角形の頂点B
	// vertexC	:三角形の頂点C
	static bool IsHitTriangleXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	// XY平面上での三角形の当たり判定
	// 引数
	// point	:対象の座標
	// vertexA	:三角形の頂点A
	// vertexB	:三角形の頂点B
	// vertexC	:三角形の頂点C
	static bool IsHitTriangleYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

};
#endif