#pragma once

#include "Enemy.h"
#include "../AI/AIBase.h"

#define EN_ANIM_SPD (1.0f)
#define EN_CHANGE_SPD (0.05f)	//補間スピード

////アニメ再生
//enum {
//	ANIM_MAIN,	//メイン再生
//	ANIM_SUB,	//サブ再生
//
//	BLEND_NUM
//
//};

//アニメ種類
enum EN_ANIM
{
	EN_ATTACK = 0,		//攻撃
	EN_DEAD = 1,		//死亡
	EN_HIT_BACK = 29,	//のけぞり
	EN_WALK = 30,		//歩き

	EN_ANIM_NUM = 4,
};

class CNormalEnemy : public CEnemy
{
public:
	CNormalEnemy();
	~CNormalEnemy();

public:
	void Init() override;
	void Load() override;
	void Step() override;
	void Draw() override;
	void Delete() override;
	void Fin() override;
	CEnemy* Clone() override;

	int GetHandle() { return handle_; }


	//アニメーションリクエスト
	void Request(int animID, float animSpd);
	//アニメ更新
	void AnimUpdate();
	//現在再生しているアニメタイプを取得
	inline int GetAnimType() { return m_animType; }

private:
	void StepAI();
	void StepIdle();		//状態：歩き
	void StepCaution();
	void StepAttack();		//状態：攻撃
	void StepBack();
	void StepHitBack();	//状態：のけぞり
	void StepDead();		//状態：死亡


	// アニメに関するデータ
	float	m_animCount[BLEND_NUM];		// 現在のアニメカウント
	float	m_animSpeed[BLEND_NUM];		// アニメーション速度
	int		m_animIdx[BLEND_NUM];		// アニメのインデックス番号
	float	m_animRate;					// アニメのレート
	int		m_animType;					// 現在再生しているアニメタイプ

//public:
//	void Reset();

private:
	int handle_;
	CAIBase* enemy_ai_;
	float timer_;
	//int posHandle_;		//座標用のモデルハンドル
	//int posID_;			//フレーム（ボーン）の番号
};
