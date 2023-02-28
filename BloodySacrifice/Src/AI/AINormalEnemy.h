#pragma once

#include "AIBase.h"
#include "../Enemy/EnemyManager.h"

class CAINomalEnemy : public CAIBase
{
public:
	CAINomalEnemy();
	~CAINomalEnemy();

public:
	// ����������
	void Init(float attack_range, float caution_range, float back_range);
	// �x����ԂɂȂ�͈͂�ݒ�
	void SetCautionRange(float caution_range) { caution_range_ = caution_range; }
	// �U����ԂɂȂ�͈͂�ݒ�
	void SetAttackRange(float attack_range) { attack_range_ = attack_range; }
	// �A�ҏ�ԂɂȂ�͈͂�ݒ�
	void SetBackRange(float back_range) { back_range_ = back_range; }

		// ���N���X����K���p������
	int GetNextState(CEnemy* enemy) override;

private:
	// �ҋ@��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AINormalkFromIdle(CEnemy* enemy);
	// �x����Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AINormalFromCaution(CEnemy* enemy);
	// �U����Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AINormalFromAttack(CEnemy* enemy);
	// �̂������Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AINormalFromHitBack(CEnemy* enemy);
	// ���S��Ԃ��������
	int AINormalFromDead(CEnemy* enemy);
	// �A�ҏ�Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIAttackFromBack(CEnemy* enemy);

private:
	float caution_range_;	// �x����ԂɂȂ�͈�
	float attack_range_;	// �U����ԂɂȂ�͈�
	float back_range_;		// �A�ҏ�ԂɂȂ�͈�
};