
//Player.cpp
//プレイヤー関連

#include <math.h>
#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../MyMath/MyMath.h"
#include "../Collision/Collision.h"
#include "../Map/Map.h"
#include "../Trap/Stone.h"

MyMath* math;

//コンストラクタ
CPlayer::CPlayer()
{
	handle_ = 0;
	memset(&pos_, 0, sizeof(VECTOR));
	player_state_ = PLAYER_STATE_NORMAL;
	jump_time_ = 0.0f;
}

//デストラクタ
CPlayer::~CPlayer()
{
	Fin();
}

//初期化（引数なし）
void CPlayer::Init()
{
	//引数なしならすべてゼロにする
	handle_ = 0;
	pos_ = VGet(0.0f, 1.0f, 0.0f);
	angle_ = 0.0f;
	player_state_ = PLAYER_STATE_NORMAL;
	jump_time_ = 0.0f;
}

//初期化（引数あり）
void CPlayer::Init(VECTOR pos)
{
	//座標と回転を設定
	pos_ = pos;

	//他はゼロにする
	angle_ = 0.0f;
	handle_ = 0;
	player_state_ = PLAYER_STATE_NORMAL;
	jump_time_ = 0.0f;
}

//読み込み
void CPlayer::Load()
{
	//モデルの読み込み
	handle_ = MV1LoadModel("Data/Model/Player/player-mock.x");
}

//削除
void CPlayer::Delete()
{
	//モデル破棄
	MV1DeleteModel(handle_);

	//削除したら0を代入しておく
	handle_ = 0;
}

//毎フレーム呼ぶ処理（操作）
void CPlayer::Step()
{
	//移動フラグ
	bool moveFlg;

	//初期状態では移動していない
	moveFlg = false;

	//プレイヤーに常に重力をかける
	pos_.y -= GRAVITY;

	//移動速度ベクトルを初期化
	speed_ = { 0 };

	//プレイヤー通常
	if(player_state_ == PLAYER_STATE_NORMAL)
	{
		if(g_input.IsPush(KEY_SPACE))
		{
			//状態をジャンプ上昇中へ
			player_state_ = PLAYER_STATE_JUMP_UP;
			jump_time_ = 0.0f;
		}
	}

	//プレイヤージャンプ上昇中
	if(player_state_ == PLAYER_STATE_JUMP_UP)
	{
		//上昇
		pos_.y += PLAYER_JUMP_VAL;
		jump_time_ += 1.0f / FRAME_RATE;

		//ジャンプ時間が過ぎたら
		if(jump_time_ >= PLAYER_JUMP_TIME)
		{
			jump_time_ = 0.0f;
			player_state_ = PLAYER_STATE_NORMAL;
		}
	}

	//斜め移動
	if (g_input.IsCont(KEY_UP) && g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_UP) && g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_up_sidle = { 0 };

		//カメラ情報取得
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_up_sidle = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_up_sidle.y = 0;
		//正規化
		move_up_sidle = math->VecNormalize(move_up_sidle);
		//歩く速さを掛け算
		if (!IsPushStone())
		{
			move_up_sidle = math->VecScale(move_up_sidle, PLAYER_WALK_SPEED);
		}
		else
		{
			move_up_sidle = math->VecScale(move_up_sidle, PLAYER_WALK_SPEED_HALF);
		}

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
		speed_.x = m_result.m[3][0];
		speed_.y = m_result.m[3][1];
		speed_.z = m_result.m[3][2];

		//移動前の座標と足して新たな座標を得る
		pos_ = math->VecAdd(pos_, speed_);

		//移動したに変える
		moveFlg = true;
	}
	else if (g_input.IsCont(KEY_DOWN) && g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_DOWN) && g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_up_sidle = { 0 };

		//カメラ情報取得
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_up_sidle = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_up_sidle.y = 0;
		//正規化
		move_up_sidle = math->VecNormalize(move_up_sidle);
		//歩く速さを掛け算
		if (!IsPushStone())
		{
			move_up_sidle = math->VecScale(move_up_sidle, -PLAYER_WALK_SPEED);
		}
		else
		{
			move_up_sidle = math->VecScale(move_up_sidle, -PLAYER_WALK_SPEED_HALF);
		}

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
		speed_.x = m_result.m[3][0];
		speed_.y = m_result.m[3][1];
		speed_.z = m_result.m[3][2];

		//移動前の座標と足して新たな座標を得る
		pos_ = math->VecAdd(pos_, speed_);

		//移動したに変える
		moveFlg = true;
	}
	//カメラが向いている方向へ移動
	else if(g_input.IsCont(KEY_UP))
	{
		VECTOR move_up = { 0 };

		//カメラ情報取得
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_up = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_up.y = 0;
		//正規化
		move_up = math->VecNormalize(move_up);
		//歩く速さを掛け算
		if (!IsPushStone())
		{
			move_up = math->VecScale(move_up, PLAYER_WALK_SPEED);
		}
		else
		{
			move_up = math->VecScale(move_up, PLAYER_WALK_SPEED_HALF);
		}

		//移動速度ベクトルに入れる
		speed_ = move_up;

		//移動前の座標と足して新たな座標を得る
		pos_ = math->VecAdd(pos_, speed_);

		//移動したに変える
		moveFlg = true;

	}
	//カメラが向いている方向とは逆へ移動
	else if(g_input.IsCont(KEY_DOWN))
	{
		VECTOR move_down = { 0 };

		//カメラ情報取得
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_down = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_down.y = 0;
		//正規化
		move_down = math->VecNormalize(move_down);
		//歩く速さを掛け算
		if (!IsPushStone())
		{
			move_down = math->VecScale(move_down, -PLAYER_WALK_SPEED);
		}
		else
		{
			move_down = math->VecScale(move_down, -PLAYER_WALK_SPEED_HALF);
		}

		//移動速度ベクトルに入れる
		speed_ = move_down;
	
		//移動前の座標と足して新たな座標を得る
		pos_ = math->VecAdd(pos_, speed_);

		//移動したに変える
		moveFlg = true;
	}
	//左へ移動
	else if(g_input.IsCont(KEY_LEFT))
	{
		VECTOR move_left = { 0 };

		//カメラ情報取得
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_left = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_left.y = 0;
		//正規化
		move_left = math->VecNormalize(move_left);
		//歩く速さを掛け算
		if (!IsPushStone())
		{
			move_left = math->VecScale(move_left, -PLAYER_WALK_SPEED);
		}
		else
		{
			move_left = math->VecScale(move_left, -PLAYER_WALK_SPEED_HALF);
		}
		
		//平行移動行列取得
		MATRIX m_dir = MGetTranslate(move_left);
		//Y軸回転行列取得
		MATRIX m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING);
		//各行列を合成
		MATRIX m_result = MMult(m_dir, m_rotY);

		//移動速度ベクトルに入れる
		speed_.x = m_result.m[3][0];
		speed_.y = m_result.m[3][1];
		speed_.z = m_result.m[3][2];

		//移動前の座標と足して新たな座標を得る
		pos_ = math->VecAdd(pos_, speed_);

		//移動したに変える
		moveFlg = true;
	}
	//右へ移動
	else if(g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_right = { 0 };

		//カメラ情報取得
		CPlayCamera* play_camera = CCameraManager::GetInstance()->GetPlayCamera();

		//カメラの視点、注視点からベクトルを作成
		move_right = math->VecCreate(play_camera->GetPos(), play_camera->GetLook());
		//Y成分は初期化
		move_right.y = 0;
		//正規化
		move_right = math->VecNormalize(move_right);
		//歩く速さを掛け算
		if (!IsPushStone())
		{
			move_right = math->VecScale(move_right, -PLAYER_WALK_SPEED);
		}
		else
		{
			move_right = math->VecScale(move_right, -PLAYER_WALK_SPEED_HALF);
		}

		//平行移動行列
		MATRIX m_dir = MGetTranslate(move_right);
		MATRIX m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING);
		MATRIX m_result = MMult(m_dir, m_rotY);

		//移動速度ベクトルに入れる
		speed_.x = m_result.m[3][0];
		speed_.y = m_result.m[3][1];
		speed_.z = m_result.m[3][2];

		//移動前の座標と足して新たな座標を得る
		pos_ = math->VecAdd(pos_, speed_);

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

	VECTOR vVec;
	vVec = g_map.HitCheck(pos_, PLAYER_RAD);
	pos_ = VAdd(pos_, vVec);

	//プレイヤーの座標
	MV1SetPosition(handle_, pos_);
}

//描画
void CPlayer::Draw()
{
	//プレイヤーの描画
	MV1DrawModel(handle_);
}

//後処理
void CPlayer::Fin()
{
	//Deleteが呼ばれていないなら
	if(handle_ != 0)
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
	float DiffAngle;

	//移動速度ベクトルが0以外のときに計算する
	if (speed_.x != 0 || speed_.z != 0)
	{
		TargetAngle = atan2f(speed_.x, speed_.z);
	}

	// 目標の角度と現在の角度との差を割り出す
	{
		DiffAngle = TargetAngle - angle_;

		// ある方向からある方向の差が１８０度以上になることは無いので
		// 差の値が１８０度以上になっていたら修正する
		if (DiffAngle < -DX_PI_F)
		{
			DiffAngle += DX_TWO_PI_F;
		}
		else if (DiffAngle > DX_PI_F)
		{
			DiffAngle -= DX_TWO_PI_F;
		}
	}

	if (DiffAngle > 0.0f)
	{
		// 差がプラスの場合は引く
		DiffAngle -= PLAYER_WALK_SPEED;
		if (DiffAngle < 0.0f)
		{
			DiffAngle = 0.0f;
		}
	}
	else
	{
		// 差がマイナスの場合は足す
		DiffAngle += PLAYER_WALK_SPEED;
		if (DiffAngle > 0.0f)
		{
			DiffAngle = 0.0f;
		}
	}
	
	angle_ = TargetAngle - DiffAngle;

	//プレイヤーの回転
	MV1SetRotationXYZ(handle_, VGet(0.0f, angle_ + DX_PI_F, 0.0f));
}

bool CPlayer::IsPushStone()
{
	//岩が消滅状態でなかったら
	if (g_stone_trap.GetState() != STONE_TRAP_STATE_OUT)
	{
		//プレイヤーと岩が当たったら
		if (CCollision::IsHitSphere(pos_, PLAYER_W * 0.5f, g_stone_trap.GetPos(), STONE_RAD))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}
