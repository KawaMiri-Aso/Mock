
//Player.cpp
//プレイヤー関連

#include <math.h>
#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../MyMath/MyMath.h"

MyMath* math;

//プレイヤー関連
#define PLAYER_W	(2.0f)	//プレイヤーの横幅
#define PLAYER_H	(2.0f)	//プレイヤーの高さ
#define PLAYER_D	(2.0f)	//プレイヤーの奥行き
#define PLAYER_RAD	(1.0f)	//プレイヤーの半径
#define PLAYER_JUMP_VAL		(0.3f)	//ジャンプ量
#define PLAYER_JUMP_TIME	(0.8f)	//ジャンプの時間
#define PLAYER_WALK_SPEED	(0.3f)	//歩く速さ
#define PLAYER_WALK_SPEED_HALF	(0.15f)		//斜め歩き用の速さ
#define PLAYER_ROT_SCALING		(0.5f)		//左右入力用の数値
#define PLAYER_ROT_SCALING_HALF	(0.25f)		//斜め入力用の数値

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
	m_fAngle = 0.0f;
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
	m_fAngle = 0.0f;
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
	//移動フラグ
	bool moveFlg;

	//初期状態では移動していない
	moveFlg = false;

	//プレイヤーに常に重力をかける
	m_vPos.y -= GRAVITY;

	//移動速度ベクトルを初期化
	m_vSpeed = { 0 };

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
		m_vPos.y = PLAYER_RAD;			//めり込まない位置に置く
		m_eState = PLAYER_STATE_NORMAL;	//通常状態にしておく
	}

	//斜め移動
	if (g_input.IsCont(KEY_UP) && g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_UP) && g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_up_sidle = { 0 };

		//カメラ情報取得
		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_up_sidle = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_up_sidle.y = 0;
		//正規化
		move_up_sidle = math->VecNormalize(move_up_sidle);
		m_vRot = move_up_sidle;
		//歩く速さを掛け算
		move_up_sidle = math->VecScale(move_up_sidle, PLAYER_WALK_SPEED);

		//平行移動行列取得
		MATRIX m_dir = MGetTranslate(move_up_sidle);
		MATRIX m_rotY;
		//Y軸回転行列取得
		if (!g_input.IsCont(KEY_RIGHT))
		{
			m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING_HALF);
		}
		else
		{
			m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING_HALF);
		}
		//行列同士の掛け算
		MATRIX m_result = MMult(m_dir, m_rotY);

		//移動速度ベクトルに入れる
		m_vSpeed.x = m_result.m[3][0];
		m_vSpeed.y = m_result.m[3][1];
		m_vSpeed.z = m_result.m[3][2];

		//移動前の座標と足して新たな座標を得る
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//移動したに変える
		moveFlg = true;
	}
	else if (g_input.IsCont(KEY_DOWN) && g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_DOWN) && g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_up_sidle = { 0 };

		//カメラ情報取得
		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_up_sidle = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_up_sidle.y = 0;
		//正規化
		move_up_sidle = math->VecNormalize(move_up_sidle);
		m_vRot = move_up_sidle;
		//歩く速さを掛け算
		move_up_sidle = math->VecScale(move_up_sidle, -PLAYER_WALK_SPEED);

		//平行移動行列取得
		MATRIX m_dir = MGetTranslate(move_up_sidle);
		MATRIX m_rotY;
		//Y軸回転行列取得
		if (!g_input.IsCont(KEY_RIGHT))
		{
			m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING_HALF);
		}
		else
		{
			m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING_HALF);
		}
		//行列同士の掛け算
		MATRIX m_result = MMult(m_dir, m_rotY);

		//移動速度ベクトルに入れる
		m_vSpeed.x = m_result.m[3][0];
		m_vSpeed.y = m_result.m[3][1];
		m_vSpeed.z = m_result.m[3][2];

		//移動前の座標と足して新たな座標を得る
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//移動したに変える
		moveFlg = true;
	}
	//カメラが向いている方向へ移動
	else if(g_input.IsCont(KEY_UP))
	{
		VECTOR move_up = { 0 };

		//カメラ情報取得
		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_up = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_up.y = 0;
		//正規化
		move_up = math->VecNormalize(move_up);
		m_vRot = move_up;
		//歩く速さを掛け算
		move_up = math->VecScale(move_up, PLAYER_WALK_SPEED);

		//移動速度ベクトルに入れる
		m_vSpeed = move_up;

		//移動前の座標と足して新たな座標を得る
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//移動したに変える
		moveFlg = true;

	}
	//カメラが向いている方向とは逆へ移動
	else if(g_input.IsCont(KEY_DOWN))
	{
		VECTOR move_down = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_down = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_down.y = 0;
		//正規化
		move_down = math->VecNormalize(move_down);
		m_vRot = move_down;
		//歩く速さを掛け算
		move_down = math->VecScale(move_down, -PLAYER_WALK_SPEED);

		//移動速度ベクトルに入れる
		m_vSpeed = move_down;
	
		//移動前の座標と足して新たな座標を得る
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//移動したに変える
		moveFlg = true;
	}
	//左へ移動
	else if(g_input.IsCont(KEY_LEFT))
	{
		VECTOR move_left = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_left = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_left.y = 0;
		//正規化
		move_left = math->VecNormalize(move_left);
		m_vRot = move_left;
		//歩く速さを掛け算
		move_left = math->VecScale(move_left, -PLAYER_WALK_SPEED);
		
		//平行移動行列取得
		MATRIX m_dir = MGetTranslate(move_left);
		//Y軸回転行列取得
		MATRIX m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING);
		//各行列を合成
		MATRIX m_result = MMult(m_dir, m_rotY);

		//移動速度ベクトルに入れる
		m_vSpeed.x = m_result.m[3][0];
		m_vSpeed.y = m_result.m[3][1];
		m_vSpeed.z = m_result.m[3][2];

		//移動前の座標と足して新たな座標を得る
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//移動したに変える
		moveFlg = true;
	}
	//右へ移動
	else if(g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_right = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_right = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_right.y = 0;
		//正規化
		move_right = math->VecNormalize(move_right);
		m_vRot = move_right;
		//歩く速さを掛け算
		move_right = math->VecScale(move_right, -PLAYER_WALK_SPEED);

		//平行移動行列
		MATRIX m_dir = MGetTranslate(move_right);
		MATRIX m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING);
		MATRIX m_result = MMult(m_dir, m_rotY);

		//移動速度ベクトルに入れる
		m_vSpeed.x = m_result.m[3][0];
		m_vSpeed.y = m_result.m[3][1];
		m_vSpeed.z = m_result.m[3][2];

		//移動前の座標と足して新たな座標を得る
		m_vPos = math->VecAdd(m_vPos, m_vSpeed);

		//移動したに変える
		moveFlg = true;
	}

	//座標設定 =====
	
	//移動してなければ回転処理をしない
	if (moveFlg)
	{
		//プレイヤーの回転
		AngleProcess();
	}
	
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

//プレイヤーの回転処理
void CPlayer::AngleProcess()
{
	//目標角度
	float TargetAngle = 0.0f;
	//目標角度と現在の角度との差
	float DffrncAngle;

	//移動速度ベクトルが0以外のときに計算する

	if (m_vSpeed.x != 0 || m_vSpeed.z != 0)
	{
		TargetAngle = atan2f(m_vSpeed.x, m_vSpeed.z);
	}

	// 目標の角度と現在の角度との差を割り出す
	{
		DffrncAngle = TargetAngle - m_fAngle;

		// ある方向からある方向の差が１８０度以上になることは無いので
		// 差の値が１８０度以上になっていたら修正する
		if (DffrncAngle < -DX_PI_F)
		{
			DffrncAngle += DX_TWO_PI_F;
		}
		else if (DffrncAngle > DX_PI_F)
		{
			DffrncAngle -= DX_TWO_PI_F;
		}
	}

	if (DffrncAngle > 0.0f)
	{
		// 差がプラスの場合は引く
		DffrncAngle -= PLAYER_WALK_SPEED;
		if (DffrncAngle < 0.0f)
		{
			DffrncAngle = 0.0f;
		}
	}
	else
	{
		// 差がマイナスの場合は足す
		DffrncAngle += PLAYER_WALK_SPEED;
		if (DffrncAngle > 0.0f)
		{
			DffrncAngle = 0.0f;
		}
	}
	
	m_fAngle = TargetAngle - DffrncAngle;

	//プレイヤーの回転
	MV1SetRotationXYZ(m_nHandle, VGet(0.0f, m_fAngle + DX_PI_F, 0.0f));
}