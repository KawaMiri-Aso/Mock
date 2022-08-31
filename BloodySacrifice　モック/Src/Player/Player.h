
//Player.h
//プレイヤー関連

#pragma once

#include "DxLib.h"

//プレイヤー状態
enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,	//通常
	PLAYER_STATE_JUMP_UP,	//ジャンプ上昇中
};

class CPlayer
{
public:
	CPlayer();		//コンストラクタ
	~CPlayer();		//デストラクタ

	//初期化
	void Init();
	void Init(VECTOR pos, VECTOR rot);

	//読み込み
	void Load(const char* file_path);

	//削除
	void Delete();

	//毎フレーム呼ぶ処理（操作）
	void Step();

	//描画
	void Draw();

	//後処理
	void Fin();

	//座標を取得
	VECTOR GetPos(){ return m_vPos; }

	//回転を取得
	VECTOR GetRot(){ return m_vRot; }

	//プレイヤーの回転処理
	void AngleProcess();

private:

	int				m_nHandle;		//ハンドル
	VECTOR			m_vPos;			//座標
	VECTOR			m_vSpeed;		//移動速度ベクトル
	VECTOR			m_vRot;			//向くべき方向ベクトル
	float			m_fAngle;		//向いている方向の角度
	PLAYER_STATE	m_eState;		//状態
	float			m_fJumpTime;	//ジャンプの時間
};
