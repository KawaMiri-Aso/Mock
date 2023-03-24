#include "AINormalEnemy.h"

CAINomalEnemy::CAINomalEnemy()
{
}

CAINomalEnemy::~CAINomalEnemy()
{
}

// 初期化処理
void CAINomalEnemy::Init(float attack_range, float caution_range, float back_range)
{
	// 各メンバを設定
	SetAttackRange(attack_range);
	SetCautionRange(caution_range);
	SetBackRange(back_range);
}

int CAINomalEnemy::GetNextState(CEnemy* enemy)
{
	//返却用変数next
	int next = ENEMY_AI_STATE_IDLE;
	//現在の状態を取得
	int now_state = enemy->GetEnemyAIState();

	//現在の状態ごとに、処理を関数分け
	switch (now_state)
	{
	case ENEMY_AI_STATE_IDLE: //待機状態からの遷移
		next = AINormalkFromIdle(enemy);
		break;
		
	//case ENEMY_AI_STATE_CAUTION: //警戒状態からの遷移
	//	next = AINormalFromCaution(enemy);
	//	break;

	case ENEMY_AI_STATE_ATTACK: //攻撃状態からの遷移
		next = AINormalFromAttack(enemy);
		break;

	//case ENEMY_AI_STATE_BACK: //帰還状態からの遷移
	//	next = AIAttackFromBack(enemy);
	//	break;
	}

	//次の状態を返却
	return next;
}

// 待機状態からの遷移
int CAINomalEnemy::AINormalkFromIdle(CEnemy* enemy)
{
	//トーテムまでの距離を算出
	float totem_dis = GetTotemDist(enemy);
	//プレイヤーまでの距離を取得
	float player_dis = GetPlayerDist(enemy);

	if (totem_dis <= attack_range_)
	{
		//トーテムに辿り着いたら攻撃状態
		return ENEMY_AI_STATE_ATTACK;
	}
	//else if(player_dis <= caution_range_)
	//{
	//	//警戒範囲以内にプレイヤーがいれば警戒状態
	//	return ENEMY_AI_STATE_CAUTION;
	//}

	//何もなければ待機のまま
	return ENEMY_AI_STATE_IDLE;
}

//// 警戒状態からの遷移
//int CAINomalEnemy::AINormalFromCaution(CEnemy* enemy)
//{
//	//トーテムまでの距離を算出
//	float totem_dis = GetTotemDist(enemy);
//	//プレイヤーまでの距離を取得
//	float player_dis = GetPlayerDist(enemy);
//
//	if (player_dis <= attack_range_)
//	{
//		//攻撃範囲以内にプレイヤーがいれば攻撃状態
//		return ENEMY_AI_STATE_ATTACK;
//	}
//	else if (player_dis <= back_range_)
//	{
//		//警戒範囲外にプレイヤーがいれば帰還
//		return ENEMY_AI_STATE_BACK;
//	}
//
//	//何もなければ警戒のまま
//	return ENEMY_AI_STATE_CAUTION;
//}

// 攻撃状態からの遷移
int CAINomalEnemy::AINormalFromAttack(CEnemy* enemy)
{
	////プレイヤーまでの距離を取得
	//float player_dis = GetPlayerDist(enemy);

	//if (player_dis >= caution_range_)
	//{
	//	//警戒範囲内にプレイヤーがいれば警戒
	//	return ENEMY_AI_STATE_CAUTION;
	//}
	//else if (player_dis >= back_range_)
	//{
	//	//警戒範囲外にプレイヤーがいれば帰還
	//	return ENEMY_AI_STATE_BACK;
	//}

	//何もなければ攻撃のまま
	return ENEMY_AI_STATE_ATTACK;
}

// のけぞり状態からの遷移
int CAINomalEnemy::AINormalFromHitBack(CEnemy* enemy)
{
	return 0;
}

// 死亡状態から消える
int CAINomalEnemy::AINormalFromDead(CEnemy* enemy)
{
	return 0;
}

//// 帰還状態からの遷移
//int CAINomalEnemy::AIAttackFromBack(CEnemy* enemy)
//{
//	// プレイヤーまでの距離を取得
//	float player_dist = GetPlayerDist(enemy);
//
//	if (player_dist <= attack_range_) {
//		// 攻撃範囲内にプレイヤーがいれば攻撃
//		return ENEMY_AI_STATE_ATTACK;
//	}
//	else if (player_dist <= caution_range_) {
//		// 警戒範囲内にプレイヤーがいれば警戒
//		return ENEMY_AI_STATE_CAUTION;
//	}
//
//	//元の位置までの距離を取得
//	float back_pos_dist = GetBackPosDist(enemy);
//	if (back_pos_dist <= 1.0f) {
//		// 元の位置から1m以内であれば待機
//		return ENEMY_AI_STATE_IDLE;
//	}
//
//	//何もなければ帰還のまま
//	return ENEMY_AI_STATE_BACK;
//}