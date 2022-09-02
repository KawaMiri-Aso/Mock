#include "Collision.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Player/PlayerManager.h"

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

bool CCollision::IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2)
{
	float w1_half = (w1 / 2);		//対象Aの横幅の半分（中心から端までの長さ）
	float h1_half = (h1 / 2);		//対象Aの高さの半分（中心から端までの長さ）
	float d1_half = (d1 / 2);		//対象Aの奥行きの半分（中心から端までの長さ）

	float x1min = v1.x - w1_half;	//対象Aの最小X
	float x1max = v1.x + w1_half;	//対象Aの最大X
	float y1min = v1.y - h1_half;	//対象Aの最小Y
	float y1max = v1.y + h1_half;	//対象Aの最大Y
	float z1min = v1.z - d1_half;	//対象Aの最小Z
	float z1max = v1.z + d1_half;	//対象Aの最大Z

	float w2_half = (w2 / 2);		//対象Bの横幅の半分（中心から端までの長さ）
	float h2_half = (h2 / 2);		//対象Bの高さの半分（中心から端までの長さ）
	float d2_half = (d2 / 2);		//対象Bの奥行きの半分（中心から端までの長さ）

	float x2min = v2.x - w2_half;		//対象Bの最小X
	float x2max = v2.x + w2_half;		//対象Bの最大X
	float y2min = v2.y - h2_half;		//対象Bの最小Y
	float y2max = v2.y + h2_half;		//対象Bの最大Y
	float z2min = v2.z - d2_half;		//対象Bの最小Z
	float z2max = v2.z + d2_half;		//対象Bの最大Z

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
	// マップとの当たり判定/////////////////////////////////////////

	// ポリゴン情報を取得
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(g_map.GetCol_handle(), -1, TRUE);

	//プレイヤー情報取得
	CPlayer* player = g_player_manager.GetPlayer();
	VECTOR p_pos = player->GetPos();
	VECTOR p_forward = player->GetSpeed();

	// ポリゴンの数だけ繰り返す
	for (int i = 0; i < polygons.PolygonNum; i++)
	{
		// ポリゴン情報を取得する
		MV1_REF_POLYGON polygon = polygons.Polygons[i];
		// ポリゴンを形成する三角形の3頂点を取得する
		VECTOR vertexs[3];
		int index = polygon.VIndex[0];
		vertexs[0] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[1];
		vertexs[1] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[2];
		vertexs[2] = polygons.Vertexs[index].Position;

		// ポリゴン法線を算出する
		VECTOR norm = MyMath::GetPolygonNormalVec(vertexs[0], vertexs[1], vertexs[2]);
		//法線のY成分がMAP_FLOOR_NORM_Y以上であれば床
		if (norm.y >= MAP_FLOOR_NORM_Y) {
			// 三角形の当たり判定
			if (IsHitTriangleXZ(p_pos, vertexs[0], vertexs[1], vertexs[2])) {
				// 面の方程式から床の高さを計算
				float floor_height = MyMath::GetTriangleHeightXZ(p_pos, vertexs[0], vertexs[1], vertexs[2]);
				// プレイヤーの足元の座標を計算
				float player_bottom = p_pos.y - PLAYER_RAD;
				// 床から足元までの距離を計算
				float dist = player_bottom - floor_height;
				// 足元の方が低い　かつ　足元と床との距離が離れすぎていなければ押し上げる
				if (dist < 0.0f && MyMath::Abs(dist) <= PLAYER_RAD) {
					p_pos.y = floor_height + PLAYER_RAD;
				}
			}
		}
		else if (norm.y <= MAP_CEIL_NORM_Y)
		{
			//天井の場合
			//三角形の当たり判定
			if (IsHitTriangleXZ(p_pos, vertexs[0], vertexs[1], vertexs[2]))
			{
				//面の方程式から天井の高さを計算
				float ceil_height = MyMath::GetTriangleHeightXZ(p_pos, vertexs[0], vertexs[1], vertexs[2]);
				//プレイヤーの脳天の座標を計算
				float player_top = p_pos.y + PLAYER_RAD;
				//天井から脳天までの距離を計算
				float dist = player_top - ceil_height;
				//脳天の方が高い　かつ　脳天と天井との距離が離れすぎていなければ押し下げる
				if (dist > 0.0f && MyMath::Abs(dist) <= PLAYER_RAD)
				{
					p_pos.y = ceil_height - PLAYER_RAD;
				}
			}
		}
		else
		{
			//そうでなければ壁
			//法線とプレイヤーの移動ベクトルが向かい合っている場合のみ判定を取る
			if (MyMath::VecDot(p_forward, norm) < 0.0f)
			{
				if (MyMath::Abs(norm.z) >= MAP_WALL_NORM_Z)
				{
					//XY平面の壁
					if (IsHitTriangleXY(p_pos, vertexs[0], vertexs[1], vertexs[2]))
					{
						//平面上の壁の高さを算出
						float wall_height = MyMath::GetTriangleHeightXY(p_pos, vertexs[0], vertexs[1], vertexs[2]);
						//衝突点までの距離を算出
						float player_front = norm.z < 0.0f ? p_pos.z + PLAYER_RAD : p_pos.z - PLAYER_RAD;
						float dist = player_front - wall_height;
						//壁から離れすぎていないかチェック
						if (MyMath::Abs(dist) <= PLAYER_RAD)
						{
							//法線の向きに気を付けてめり込んでいるかチェックする
							if ((norm.z < 0.0f && dist > 0.0f) || (norm.z > 0.0f && dist < 0.0f))
							{
								//法線の方向にめり込んでいる分だけ押し出す
								VECTOR push = MyMath::VecScale(norm, MyMath::Abs(dist));
								p_pos = MyMath::VecAdd(p_pos, push);
							}
						}
					}
				}
				else
				{
					//YZ平面の壁
					if (IsHitTriangleYZ(p_pos, vertexs[0], vertexs[1], vertexs[2]))
					{
						//平面上の壁の高さを算出
						float wall_height = MyMath::GetTriangleHeightYZ(p_pos, vertexs[0], vertexs[1], vertexs[2]);
						//衝突点までの距離を算出
						float player_front = norm.x < 0.0f ? p_pos.x + PLAYER_RAD : p_pos.x - PLAYER_RAD;
						float dist = player_front - wall_height;
						//壁から離れすぎていないかチェック
						if (MyMath::Abs(dist) <= PLAYER_RAD)
						{
							//法線の向きに気を付けてめり込んでいるかチェックする
							if ((norm.x < 0.0f && dist > 0.0f) || (norm.x > 0.0f && dist < 0.0f))
							{
								//法線の方向にめり込んでいる分だけ押し出す
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