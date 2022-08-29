
//Player.cpp
//プレイヤー関連

#include <math.h>
#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../MyMath/MyMath.h"

CMyMath* math;

//プレイヤー関連
#define PLAYER_W	(2.0f)	//プレイヤーの横幅
#define PLAYER_H	(2.0f)	//プレイヤーの高さ
#define PLAYER_D	(2.0f)	//プレイヤーの奥行き
#define PLAYER_RAD	(1.0f)	//プレイヤーの半径
#define PLAYER_JUMP_VAL		(0.3f)	//ジャンプ量
#define PLAYER_JUMP_TIME	(0.8f)	//ジャンプの時間
#define PLAYER_WALK_SPEED	(3.0f)	//歩く速さ

//重力
#define GRAVITY		(0.15f)

//コンストラクタ
CPlayer::CPlayer()
{
	m_nHandle = 0;
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_eState = PLAYER_STATE_NORMAL;
	m_fJumpTime = 0.0f;
}

//デストラクタ
CPlayer::~CPlayer()
{
}

//初期化（引数なし）
void CPlayer::Init()
{
	//引数なしならすべてゼロにする
	m_nHandle = 0;
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_eState = PLAYER_STATE_NORMAL;
	m_fJumpTime = 0.0f;
}

//初期化（引数あり）
void CPlayer::Init(VECTOR pos, VECTOR rot)
{
	//座標と回転を設定
	m_vPos = pos;
	m_vRot = rot;

	//他はゼロにする
	m_nHandle = 0;
	m_eState = PLAYER_STATE_NORMAL;
	m_fJumpTime = 0.0f;

}

//読み込み
void CPlayer::Load(const char* file_path)
{
	//モデルの読み込み
	m_nHandle = MV1LoadModel(file_path);
}

//削除
void CPlayer::Delete()
{
	//モデル破棄
	MV1DeleteModel(m_nHandle);

	//削除したら0を代入しておく
	m_nHandle = 0;
}

//毎フレーム呼ぶ処理（操作）
void CPlayer::Step()
{
	//注意：箱とゴールの当たり判定は消しています

	//移動前の座標を格納
	VECTOR player_pre_pos = m_vPos;

	//プレイヤーに常に重力をかける
	m_vPos.y -= GRAVITY;

	//プレイヤー通常
	if(m_eState == PLAYER_STATE_NORMAL)
	{
		if(g_input.IsPush(KEY_SPACE))
		{
			//状態をジャンプ上昇中へ
			m_eState = PLAYER_STATE_JUMP_UP;
			m_fJumpTime = 0.0f;
		}
	}

	//プレイヤージャンプ上昇中
	if(m_eState == PLAYER_STATE_JUMP_UP)
	{
		//上昇
		m_vPos.y += PLAYER_JUMP_VAL;
		m_fJumpTime += 1.0f / FRAME_RATE;

		//ジャンプ時間が過ぎたら
		if(m_fJumpTime >= PLAYER_JUMP_TIME)
		{
			m_fJumpTime = 0.0f;
			m_eState = PLAYER_STATE_NORMAL;
		}
	}

	//Y軸当たり判定 =====

	//地面と当たった
	if(m_vPos.y - PLAYER_RAD < 0.0f)
	{
		m_vPos.y = PLAYER_RAD;				//めり込まない位置に置く
		m_eState = PLAYER_STATE_NORMAL;	//通常状態にしておく
	}


	//向いている方向へ移動
	if(g_input.IsCont(KEY_UP))
	{
		//VECTOR move = {0};

		////向きベクトルを求める
		//move.x = sinf(m_vRot.y);
		//move.z = cosf(m_vRot.y);

		////向きベクトルを適切な大きさに変更して座標に加算
		//m_vPos.x += move.x * -0.1f;
		//m_vPos.z += move.z * -0.1f;

		VECTOR move_up = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		move_up = CMyMath::VecCreate(play_camera->GetLook(), play_camera->GetPos());
		move_up = CMyMath::VecNormalize(move_up);
		move_up = CMyMath::VecScale(move_up, PLAYER_WALK_SPEED);

		m_vPos.x += move_up.x * -0.1f;
		m_vPos.z += move_up.z * -0.1f;

		move_up = { 0 };
	}

	//向いている方向とは逆へ移動
	if(g_input.IsCont(KEY_DOWN))
	{
		//VECTOR move = {0};

		////向きベクトルを求める
		//move.x = sinf(m_vRot.y);
		//move.z = cosf(m_vRot.y);

		////向きベクトルを適切な大きさ・向きに変更して座標に加算
		//m_vPos.x += move.x * 0.1f;
		//m_vPos.z += move.z * 0.1f;

		VECTOR move_down = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		move_down = CMyMath::VecCreate(play_camera->GetLook(), play_camera->GetPos());
		move_down = CMyMath::VecNormalize(move_down);
		move_down = CMyMath::VecScale(move_down, PLAYER_WALK_SPEED);

		m_vPos.x += move_down.x * 0.1f;
		m_vPos.z += move_down.z * 0.1f;
	}

	//左回転
	if(g_input.IsCont(KEY_LEFT))
	{
		m_vRot.y -= 0.1f;
	}
	//右回転
	if(g_input.IsCont(KEY_RIGHT))
	{
		m_vRot.y += 0.1f;
	}

	//座標設定 =====

	//プレイヤーの回転
	MV1SetRotationXYZ(m_nHandle, m_vRot);

	//プレイヤーの座標
	MV1SetPosition(m_nHandle, m_vPos);
}

//描画
void CPlayer::Draw()
{
	//プレイヤーの描画
	MV1DrawModel(m_nHandle);
}

//後処理
void CPlayer::Fin()
{
	//Deleteが呼ばれていないなら
	if(m_nHandle != 0)
	{
		//削除を呼んでおく
		Delete();
	}
}

