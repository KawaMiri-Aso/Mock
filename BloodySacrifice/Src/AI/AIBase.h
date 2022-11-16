#pragma once

#include "../Enemy/Enemy.h"

class CAIBase
{
public:
	enum EnemyAIState
	{
		ENEMY_AI_STATE_IDLE,	//ë“ã@
		ENEMY_AI_STATE_CAUTION,	//åxâ˙
		ENEMY_AI_STATE_ATTACK,	//çUåÇ
		ENEMY_AI_STATE_BACK,	//ãAä“
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