#include "Collision.h"
#include "../MyMath/MyMath.h"

bool CCollision::IsHitTriangleXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// 三角形の辺に沿ったベクトル
	VECTOR vecAB = MyMath::VecCreate(vertexA, vertexB); vecAB.z = 0.0f;
	VECTOR vecBC = MyMath::VecCreate(vertexB, vertexC); vecBC.z = 0.0f;
	VECTOR vecCA = MyMath::VecCreate(vertexC, vertexA); vecCA.z = 0.0f;

	// 各頂点から対象までのベクトル
	VECTOR vecAP = MyMath::VecCreate(vertexA, point); vecAP.z = 0.0f;
	VECTOR vecBP = MyMath::VecCreate(vertexB, point); vecBP.z = 0.0f;
	VECTOR vecCP = MyMath::VecCreate(vertexC, point); vecCP.z = 0.0f;

	// 対応するベクトルどうして外積を計算する
	VECTOR vecABAP = MyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = MyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = MyMath::VecCross(vecCA, vecCP);

	// 各外積のZ成分が0以下であれば当たっている
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
	// 三角形の辺に沿ったベクトル
	VECTOR vecAB = MyMath::VecCreate(vertexA, vertexB); vecAB.y = 0.0f;
	VECTOR vecBC = MyMath::VecCreate(vertexB, vertexC); vecBC.y = 0.0f;
	VECTOR vecCA = MyMath::VecCreate(vertexC, vertexA); vecCA.y = 0.0f;

	// 各頂点から対象までのベクトル
	VECTOR vecAP = MyMath::VecCreate(vertexA, point); vecAP.y = 0.0f;
	VECTOR vecBP = MyMath::VecCreate(vertexB, point); vecBP.y = 0.0f;
	VECTOR vecCP = MyMath::VecCreate(vertexC, point); vecCP.y = 0.0f;

	// 対応するベクトルどうして外積を計算する
	VECTOR vecABAP = MyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = MyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = MyMath::VecCross(vecCA, vecCP);

	// 各外積のY成分が0以下であれば当たっている
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
	// 三角形の辺に沿ったベクトル
	VECTOR vecAB = MyMath::VecCreate(vertexA, vertexB); vecAB.x = 0.0f;
	VECTOR vecBC = MyMath::VecCreate(vertexB, vertexC); vecBC.x = 0.0f;
	VECTOR vecCA = MyMath::VecCreate(vertexC, vertexA); vecCA.x = 0.0f;

	// 各頂点から対象までのベクトル
	VECTOR vecAP = MyMath::VecCreate(vertexA, point); vecAP.x = 0.0f;
	VECTOR vecBP = MyMath::VecCreate(vertexB, point); vecBP.x = 0.0f;
	VECTOR vecCP = MyMath::VecCreate(vertexC, point); vecCP.x = 0.0f;

	// 対応するベクトルどうして外積を計算する
	VECTOR vecABAP = MyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = MyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = MyMath::VecCross(vecCA, vecCP);

	// 各外積のX成分が0以下であれば当たっている
	if (vecABAP.x >= 0 && vecBCBP.x >= 0 && vecCACP.x >= 0) {
		return true;
	}

	if (vecABAP.x <= 0 && vecBCBP.x <= 0 && vecCACP.x <= 0) {
		return true;
	}

	return false;
}
