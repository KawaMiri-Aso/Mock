#pragma once

#include "AIBase.h"

class CAINomalEnemy : public CAIBase
{
public:
	CAINomalEnemy();
	~CAINomalEnemy();

public:
	// 初期化処理
	void Init(float attack_range, float caution_range, float back_range);
	// 警戒状態になる範囲を設定
	void SetCautionRange(float caution_range) { caution_range_ = caution_range; }
	// 攻撃状態になる範囲を設定
	void SetAttackRange(float attack_range) { attack_range_ = attack_range; }
	// 帰還状態になる範囲を設定
	void SetBackRange(float back_range) { back_range_ = back_range; }

		// 基底クラスから必ず継承する
	int GetNextState(CEnemy* enemy) override;

private:
	// 待機状態から次にどの状態になるか
	int AINormalkFromIdle(CEnemy* enemy);
	// 警戒状態から次にどの状態になるか
	int AINormalFromCaution(CEnemy* enemy);
	// 攻撃状態から次にどの状態になるか
	int AINormalFromAttack(CEnemy* enemy);
	// 帰還状態から次にどの状態になるか
	int AIAttackFromBack(CEnemy* enemy);

private:
	float caution_range_;	// 警戒状態になる範囲
	float attack_range_;	// 攻撃状態になる範囲
	float back_range_;		// 帰還状態になる範囲
};