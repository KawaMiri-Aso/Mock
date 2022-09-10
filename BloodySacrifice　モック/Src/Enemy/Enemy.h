#pragma once

#include "DxLib.h"

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

	bool IsActive() const { return is_active_; }
	int  GetHP() const { return hp_; }
	VECTOR GetPos() const { return pos_; }
	VECTOR GetBackPos() const { return back_pos_; }
	int GetEnemyAIState() const { return ai_state_; }

protected:
	void HitMap();

protected:
	bool is_active_;	// 生存フラグ
	int hp_;			// HP
	int ai_state_;		// AI状態
	VECTOR pos_;		// 座標
	VECTOR rot_;		// 回転
	VECTOR move_;		// 移動量
	VECTOR back_pos_;	// 帰還座標
	float rad_;			// 半径
};
