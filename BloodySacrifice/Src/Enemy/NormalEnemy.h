#pragma once

#include "Enemy.h"
#include "../AI/AIBase.h"

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

private:
	void StepAI();
	void StepIdle();
	void StepCaution();
	void StepAttack();
	void StepBack();

//public:
//	void Reset();

private:
	int handle_;
	CAIBase* enemy_ai_;
	//int posHandle_;		//���W�p�̃��f���n���h��
	//int posID_;			//�t���[���i�{�[���j�̔ԍ�
};
