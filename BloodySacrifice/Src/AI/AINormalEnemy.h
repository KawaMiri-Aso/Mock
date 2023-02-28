#pragma once

#include "AIBase.h"
#include "../Enemy/EnemyManager.h"

class CAINomalEnemy : public CAIBase
{
public:
	CAINomalEnemy();
	~CAINomalEnemy();

public:
	// ‰Šú‰»ˆ—
	void Init(float attack_range, float caution_range, float back_range);
	// Œx‰úó‘Ô‚É‚È‚é”ÍˆÍ‚ğİ’è
	void SetCautionRange(float caution_range) { caution_range_ = caution_range; }
	// UŒ‚ó‘Ô‚É‚È‚é”ÍˆÍ‚ğİ’è
	void SetAttackRange(float attack_range) { attack_range_ = attack_range; }
	// ‹AŠÒó‘Ô‚É‚È‚é”ÍˆÍ‚ğİ’è
	void SetBackRange(float back_range) { back_range_ = back_range; }

		// Šî’êƒNƒ‰ƒX‚©‚ç•K‚¸Œp³‚·‚é
	int GetNextState(CEnemy* enemy) override;

private:
	// ‘Ò‹@ó‘Ô‚©‚çŸ‚É‚Ç‚Ìó‘Ô‚É‚È‚é‚©
	int AINormalkFromIdle(CEnemy* enemy);
	// Œx‰úó‘Ô‚©‚çŸ‚É‚Ç‚Ìó‘Ô‚É‚È‚é‚©
	int AINormalFromCaution(CEnemy* enemy);
	// UŒ‚ó‘Ô‚©‚çŸ‚É‚Ç‚Ìó‘Ô‚É‚È‚é‚©
	int AINormalFromAttack(CEnemy* enemy);
	// ‚Ì‚¯‚¼‚èó‘Ô‚©‚çŸ‚É‚Ç‚Ìó‘Ô‚É‚È‚é‚©
	int AINormalFromHitBack(CEnemy* enemy);
	// €–Só‘Ô‚©‚çÁ‚¦‚é
	int AINormalFromDead(CEnemy* enemy);
	// ‹AŠÒó‘Ô‚©‚çŸ‚É‚Ç‚Ìó‘Ô‚É‚È‚é‚©
	int AIAttackFromBack(CEnemy* enemy);

private:
	float caution_range_;	// Œx‰úó‘Ô‚É‚È‚é”ÍˆÍ
	float attack_range_;	// UŒ‚ó‘Ô‚É‚È‚é”ÍˆÍ
	float back_range_;		// ‹AŠÒó‘Ô‚É‚È‚é”ÍˆÍ
};