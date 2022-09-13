#pragma once

#include "../Enemy/Enemy.h"

class CAIBase
{
public:
	enum EnemyAIState
	{
		ENEMY_AI_STATE_IDLE,	//‘Ò‹@
		ENEMY_AI_STATE_CAUTION,	//Œx‰ú
		ENEMY_AI_STATE_ATTACK,	//UŒ‚
		ENEMY_AI_STATE_BACK,	//‹AŠÒ
	};
public:
	CAIBase();
	virtual ~CAIBase();

protected:
	// •Ö—˜‚ÈŠÖ”‚ğ—pˆÓ
	static float GetPlayerDist(CEnemy* enemy);
	//static float GetBackPosDist(CEnemy* enemy);

public:
	virtual int GetNextState(CEnemy* enemy) = 0;
};