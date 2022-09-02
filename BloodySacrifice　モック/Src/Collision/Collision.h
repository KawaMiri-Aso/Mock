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

	// XZ平面上での三角形の当たり判定
	// 引数
	// point	:対象の座標
	// vertexA	:三角形の頂点A
	// vertexB	:三角形の頂点B
	// vertexC	:三角形の頂点C
	static bool IsHitTriangleXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	// YZ平面上での三角形の当たり判定
	// 引数
	// point	:対象の座標
	// vertexA	:三角形の頂点A
	// vertexB	:三角形の頂点B
	// vertexC	:三角形の頂点C
	static bool IsHitTriangleYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	//直方体の当たり判定（AABB）
	// v1			… 対象AのX,Y,Z座標（モデルの中心座標）
	// w1, h1, d1	… 対象AのW,H,D（横幅、高さ、奥行き）
	// v2			… 対象BのX,Y,Z座標（モデルの中心座標）
	// w2, h2, d2	… 対象BのW,H（横幅、高さ、奥行き）
	static bool IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2);

	//球と球
	// v1	… 対象Aの座標
	// r1	… 対象Aの半径
	// v2	… 対象Bの座標
	// r2	… 対象Bの半径
	static bool IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2);

	static void CheckCollision();

};
#endif