#pragma once

#include "../Enemy/Enemy.h"

class CAIBase
{
public:
	enum EnemyAIState
	{
		ENEMY_AI_STATE_IDLE,	//�ҋ@
		ENEMY_AI_STATE_CAUTION,	//�x��
		ENEMY_AI_STATE_ATTACK,	//�U��
		ENEMY_AI_STATE_HITBACK, //�̂�����
		ENEMY_AI_STATE_BACK,	//�A��
		ENEMY_AI_STATE_DEAD,	//���S
	};
public:
	CAIBase();
	virtual ~CAIBase();

protected:
	static float GetPlayerDist(CEnemy* enemy);
	static float GetBackPosDist(CEnemy* enemy);
	static float GetTotemDist(CEnemy* enemy);

public:
	virtual int GetNextState(CEnemy* enemy) = 0;
};