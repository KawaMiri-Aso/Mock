
//Player.h
//プレイヤー関連

#pragma once

#include "DxLib.h"

//プレイヤー関連
#define PLAYER_W	(4.8f)	//プレイヤーの横幅
#define PLAYER_H	(12.8f)	//プレイヤーの高さ
#define PLAYER_D	(3.2f)	//プレイヤーの奥行き
#define PLAYER_RAD	(6.4f)	//プレイヤーの半径
#define PLAYER_JUMP_VAL		(0.3f)	//ジャンプ量
#define PLAYER_JUMP_TIME	(0.8f)	//ジャンプの時間
#define PLAYER_WALK_SPEED	(0.3f)	//歩く速さ
#define PLAYER_WALK_SPEED_HALF	(0.15f)		//岩押し中の歩く早さ
#define PLAYER_ROT_SCALING		(0.5f)		//左右入力用の数値
#define PLAYER_ROT_SCALING_HALF	(0.25f)		//斜め入力用の数値

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

	//移動速度ベクトルを取得
	VECTOR GetSpeed() { return m_vSpeed; }

	//プレイヤーの回転処理
	void AngleProcess();

	//ステージとの当たり判定
	void CheckCollision();

	//岩を押しているか
	bool IsPushStone();

private:

	int				m_nHandle;		//ハンドル
	VECTOR			m_vPos;			//座標
	VECTOR			m_vSpeed;		//移動速度ベクトル
	VECTOR			m_vRot;			//向くべき方向ベクトル
	float			m_fAngle;		//向いている方向の角度
	PLAYER_STATE	m_eState;		//状態
	float			m_fJumpTime;	//ジャンプの時間
	
};
