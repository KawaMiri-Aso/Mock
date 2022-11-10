
//Player.h
//プレイヤー関連

#pragma once

#include "DxLib.h"

//プレイヤー関連
#define PLAYER_W	(4.454f)	//プレイヤーの横幅
#define PLAYER_H	(18.6f)	//プレイヤーの高さ
#define PLAYER_D	(5.215f)	//プレイヤーの奥行き
#define PLAYER_RAD	(9.3f)	//プレイヤーの半径
#define PLAYER_JUMP_VAL		(0.8f)	//ジャンプ量
#define PLAYER_JUMP_TIME	(0.8f)	//ジャンプの時間
#define PLAYER_WALK_SPEED	(0.8f)	//歩く速さ
#define PLAYER_WALK_SPEED_HALF	(PLAYER_WALK_SPEED*0.5)	//岩押し中の歩く早さ
#define PLAYER_ROT_SCALING		(0.5f)		//左右入力用の数値
#define PLAYER_ROT_SCALING_HALF	(0.25f)		//斜め入力用の数値

//プレイヤー状態
enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,	//通常
	PLAYER_STATE_JUMP_UP,	//ジャンプ上昇中
	PLAYER_STATE_ATTACK,	//攻撃
	PLAYER_STATE_DEAD,		//ゲームオーバー
};

class CPlayer
{
public:
	CPlayer();		//コンストラクタ
	virtual ~CPlayer();		//デストラクタ

	//初期化
	void Init();
	void Init(VECTOR pos);
	//読み込み
	void Load();
	//毎フレーム呼ぶ処理（操作）
	void Step();
	//描画
	void Draw();
	//削除
	void Delete();
	//後処理
	void Fin();

	//座標を取得
	VECTOR GetPos()const { return pos_; }
	//移動速度ベクトルを取得
	VECTOR GetSpeed()const { return speed_; }

	////岩を押しているか
	//bool IsPushStone();
	//プレイヤーの攻撃処理
	void IsAttack();

	//ゲームオーバー判定
	bool Dead();

private:
	//プレイヤーの回転処理
	void AngleProcess();

private:

	int				handle_;		//ハンドル
	VECTOR			pos_;			//座標
	VECTOR			speed_;			//移動速度ベクトル
	float			angle_;			//向いている方向の角度
	PLAYER_STATE	player_state_;	//状態
	float			jump_time_;		//ジャンプの時間
	int				hp_;			//HP
	int				damage_;		//与えるダメージ
	
};
