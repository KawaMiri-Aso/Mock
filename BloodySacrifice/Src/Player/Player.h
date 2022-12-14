
//Player.h
//プレイヤー関連

#pragma once

#include "DxLib.h"

//プレイヤー関連
#define PLAYER_W	(4.454f)	//プレイヤーの横幅
#define PLAYER_H	(18.6f)		//プレイヤーの高さ
#define PLAYER_D	(5.215f)	//プレイヤーの奥行き
#define PLAYER_RAD	(9.3f)		//プレイヤーの半径
#define PLAYER_JUMP_VAL		(30.0f)	//ジャンプ量
#define PLAYER_JUMP_TIME	(0.8f)	//ジャンプの時間
#define PLAYER_WALK_SPEED	(0.8f)	//歩く速さ
#define PLAYER_RUN_SPEED	(1.5f)	//走る速さ
#define PLAYER_WALK_SPEED_HALF	(PLAYER_WALK_SPEED*0.5)	//岩押し中の歩く早さ
#define PLAYER_ROT_SCALING		(0.5f)		//左右入力用の数値
#define PLAYER_ROT_SCALING_HALF	(0.25f)		//斜め入力用の数値
#define ANIM_SPD (1.0f)
#define CHANGE_SPD (0.05f)	//補間スピード

//プレイヤー状態
enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,	//通常
	PLAYER_STATE_WALK,		//歩き中
	PLAYER_STATE_RUN,		//走り中
	PLAYER_STATE_JUMP_UP,	//ジャンプ上昇中
	PLAYER_STATE_ATTACK,	//攻撃
	PLAYER_STATE_DEAD,		//ゲームオーバー
};

//アニメ再生
enum {
	ANIM_MAIN,	//メイン再生
	ANIM_SUB,	//サブ再生

	BLEND_NUM

};

//アニメ種類
enum ANIM
{
	WAIT,		//待機
	WALK,		//歩き
	RUN,		//走り
	ATTACK_1,	//攻撃1
	ATTACK_2,	//攻撃2
	HIT_BACK,	//攻撃受けた
	DEAD,		//死亡

	ANIM_NUM
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

	//******************************
	//取得関数
	//******************************
	
	//座標を取得
	inline VECTOR GetPos() { return pos_; }
	//移動速度ベクトルを取得
	VECTOR GetSpeed()const { return speed_; }
	//回転角度を取得
	inline VECTOR GetRot() { return rot_; }
	//状態を取得
	inline int GetState() { return player_state_; }

	//******************************
	//設定関数
	//******************************
	void SetCameraRot(VECTOR camRot) { camrot_ = camRot; }

	//座標設定
	inline void	SetPos(VECTOR pos) { pos_ = pos; }
	//回転角度設定
	inline void SetRot(VECTOR rot) { rot_ = rot; }

	////岩を押しているか
	//bool IsPushStone();
	//プレイヤーの攻撃処理
	void IsAttack();

	//ゲームオーバー判定
	bool Dead();

	void Damage(int damage) { hp_ -= damage; }

	//アニメーションリクエスト
	void Request(int animID, float animSpd);
	//アニメ更新
	void AnimUpdate();

private:
	//プレイヤーの回転処理
	void AngleProcess();
	//待機処理
	void ExecWait();
	//歩き処理
	void ExecWalk();
	//走り処理
	void ExecRun();
	//移動処理
	bool CalcMove();

	//ジャンプ処理
	void CalcJump();

	//十字キーによる移動方向取得
	VECTOR GetSpeed();
	//速度をプレイヤーに反映させる
	void CalcSpeed(VECTOR speed);

	// アニメに関するデータ
	float	m_animCount[BLEND_NUM];		// 現在のアニメカウント
	float	m_animSpeed[BLEND_NUM];		// アニメーション速度
	int		m_animIdx[BLEND_NUM];		// アニメのインデックス番号
	float	m_animRate;					// アニメのレート
	int		m_animType;					// 現在再生しているアニメタイプ

private:

	int				handle_;		//ハンドル
	VECTOR			pos_;			//座標
	VECTOR			speed_;			//移動速度ベクトル
	VECTOR			camrot_;
	VECTOR			rot_;			//回転角度
	float			angle_;			//向いている方向の角度
	PLAYER_STATE	player_state_;	//状態
	float			jump_time_;		//ジャンプの時間
	int				hp_;			//HP
	int				damage_;		//与えるダメージ
	
};
