#pragma once

#include "DxLib.h"
#include "../Player/PlayerManager.h"

//敵の行動タイプ
enum
{	
	STATE_WALK,		//歩き中
	STATE_BACK,		//ノックバック中

	STATE_NUM
};

class CEnemy
{
public:
	CEnemy();
	virtual ~CEnemy();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Step() = 0;
	virtual void Draw() = 0;
	virtual void Delete() = 0;
	virtual void Fin() = 0;
	virtual CEnemy* Clone() = 0;

public:
	void SetPos(VECTOR pos) { pos_ = pos; }
	void SetBackPos(VECTOR pos) { back_pos_ = pos; }

	bool IsActive() const { return active_; }
	int  GetHP() const { return hp_; }
	VECTOR GetPos() const { return pos_; }
	VECTOR GetBackPos() const { return back_pos_; }
	int GetEnemyAIState() const { return ai_state_; }
	void Damage(int damage) { hp_ -= damage; }
	void Dead();

	//現在位置に座標加算
	void ReflectCollision(VECTOR addVec);

	//プレイヤーの攻撃がヒットした後の処理
	void HitCalc(VECTOR move);

	//プレイヤーと敵の当たり判定
	void HitCheckEnemyToPlayer(CPlayer* player, CEnemy* enemy);
	//プレイヤーの攻撃と敵の当たり判定
	void HitCheckEnemyToPlayerAttack(CPlayer* player, CEnemy* enemy);

protected:
	void HitMap();

protected:
	bool active_;	// 生存フラグ
	int hp_;			// HP
	int ai_state_;		// AI状態
	VECTOR pos_;		// 座標
	VECTOR rot_;		// 回転
	VECTOR move_;		// 移動量
	VECTOR back_pos_;	// 帰還座標
	float rad_;			// 半径
	int damage;			//受けたダメージ（これをHPから引いていく）

	/*bool is_hit_stonetrap;*/
};
