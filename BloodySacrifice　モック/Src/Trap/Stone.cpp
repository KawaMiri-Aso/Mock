#include "Stone.h"
#include "../Collision/Collision.h"
#include "../MyMath/MyMath.h"
#include "../Map/Map.h"
#include "../Player/PlayerManager.h"

//重力
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
	//常に重力をかける
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
	

	//座標設定 =====

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
	// マップとの当たり判定/////////////////////////////////////////

// ポリゴン情報を取得
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(g_map.GetCol_handle(), -1, TRUE);

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
			if (CCollision::IsHitTriangleXZ(m_vPos, vertexs[0], vertexs[1], vertexs[2])) {
				// 面の方程式から床の高さを計算
				float floor_height = MyMath::GetTriangleHeightXZ(m_vPos, vertexs[0], vertexs[1], vertexs[2]);
				// プレイヤーの足元の座標を計算
				float player_bottom = m_vPos.y - STONE_RAD;
				// 床から足元までの距離を計算
				float dist = player_bottom - floor_height;
				// 足元の方が低い　かつ　足元と床との距離が離れすぎていなければ押し上げる
				if (dist < 0.0f && MyMath::Abs(dist) <= STONE_RAD) {
					m_vPos.y = floor_height + STONE_RAD;
				}
			}
		}
		else if (norm.y <= MAP_CEIL_NORM_Y)
		{
			//天井の場合
			//三角形の当たり判定
			if (CCollision::IsHitTriangleXZ(m_vPos, vertexs[0], vertexs[1], vertexs[2]))
			{
				//面の方程式から天井の高さを計算
				float ceil_height = MyMath::GetTriangleHeightXZ(m_vPos, vertexs[0], vertexs[1], vertexs[2]);
				//プレイヤーの脳天の座標を計算
				float player_top = m_vPos.y + STONE_RAD;
				//天井から脳天までの距離を計算
				float dist = player_top - ceil_height;
				//脳天の方が高い　かつ　脳天と天井との距離が離れすぎていなければ押し下げる
				if (dist > 0.0f && MyMath::Abs(dist) <= STONE_RAD)
				{
					m_vPos.y = ceil_height - STONE_RAD;
				}
			}
		}
		else
		{
			//そうでなければ壁
			//法線とプレイヤーの移動ベクトルが向かい合っている場合のみ判定を取る
			if (MyMath::VecDot(m_vRot, norm) < 0.0f)
			{
				if (MyMath::Abs(norm.z) >= MAP_WALL_NORM_Z)
				{
					//XY平面の壁
					if (CCollision::IsHitTriangleXY(m_vPos, vertexs[0], vertexs[1], vertexs[2]))
					{
						//平面上の壁の高さを算出
						float wall_height = MyMath::GetTriangleHeightXY(m_vPos, vertexs[0], vertexs[1], vertexs[2]);
						//衝突点までの距離を算出
						float player_front = norm.z < 0.0f ? m_vPos.z + STONE_RAD : m_vPos.z - STONE_RAD;
						float dist = player_front - wall_height;
						//壁から離れすぎていないかチェック
						if (MyMath::Abs(dist) <= STONE_RAD)
						{
							//法線の向きに気を付けてめり込んでいるかチェックする
							if ((norm.z < 0.0f && dist > 0.0f) || (norm.z > 0.0f && dist < 0.0f))
							{
								//法線の方向にめり込んでいる分だけ押し出す
								VECTOR push = MyMath::VecScale(norm, MyMath::Abs(dist));
								m_vPos = MyMath::VecAdd(m_vPos, push);
							}
						}
					}
				}
				else
				{
					//YZ平面の壁
					if (CCollision::IsHitTriangleYZ(m_vPos, vertexs[0], vertexs[1], vertexs[2]))
					{
						//平面上の壁の高さを算出
						float wall_height = MyMath::GetTriangleHeightYZ(m_vPos, vertexs[0], vertexs[1], vertexs[2]);
						//衝突点までの距離を算出
						float player_front = norm.x < 0.0f ? m_vPos.x + STONE_RAD : m_vPos.x - STONE_RAD;
						float dist = player_front - wall_height;
						//壁から離れすぎていないかチェック
						if (MyMath::Abs(dist) <= STONE_RAD)
						{
							//法線の向きに気を付けてめり込んでいるかチェックする
							if ((norm.x < 0.0f && dist > 0.0f) || (norm.x > 0.0f && dist < 0.0f))
							{
								//法線の方向にめり込んでいる分だけ押し出す
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