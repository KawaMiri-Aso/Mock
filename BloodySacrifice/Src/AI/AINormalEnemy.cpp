#include "AINormalEnemy.h"

CAINomalEnemy::CAINomalEnemy()
{
}

CAINomalEnemy::~CAINomalEnemy()
{
}

// ����������
void CAINomalEnemy::Init(float attack_range, float caution_range, float back_range)
{
	// �e�����o��ݒ�
	SetAttackRange(attack_range);
	SetCautionRange(caution_range);
	SetBackRange(back_range);
}

int CAINomalEnemy::GetNextState(CEnemy* enemy)
{
	//�ԋp�p�ϐ�next
	int next = ENEMY_AI_STATE_IDLE;
	//���݂̏�Ԃ��擾
	int now_state = enemy->GetEnemyAIState();

	//���݂̏�Ԃ��ƂɁA�������֐�����
	switch (now_state)
	{
	case ENEMY_AI_STATE_IDLE: //�ҋ@��Ԃ���̑J��
		next = AINormalkFromIdle(enemy);
		break;
		
	//case ENEMY_AI_STATE_CAUTION: //�x����Ԃ���̑J��
	//	next = AINormalFromCaution(enemy);
	//	break;

	case ENEMY_AI_STATE_ATTACK: //�U����Ԃ���̑J��
		next = AINormalFromAttack(enemy);
		break;

	//case ENEMY_AI_STATE_BACK: //�A�ҏ�Ԃ���̑J��
	//	next = AIAttackFromBack(enemy);
	//	break;
	}

	//���̏�Ԃ�ԋp
	return next;
}

// �ҋ@��Ԃ���̑J��
int CAINomalEnemy::AINormalkFromIdle(CEnemy* enemy)
{
	//�g�[�e���܂ł̋������Z�o
	float totem_dis = GetTotemDist(enemy);
	//�v���C���[�܂ł̋������擾
	float player_dis = GetPlayerDist(enemy);

	if (totem_dis <= attack_range_)
	{
		//�g�[�e���ɒH�蒅������U�����
		return ENEMY_AI_STATE_ATTACK;
	}
	//else if(player_dis <= caution_range_)
	//{
	//	//�x���͈͈ȓ��Ƀv���C���[������Όx�����
	//	return ENEMY_AI_STATE_CAUTION;
	//}

	//�����Ȃ���Αҋ@�̂܂�
	return ENEMY_AI_STATE_IDLE;
}

//// �x����Ԃ���̑J��
//int CAINomalEnemy::AINormalFromCaution(CEnemy* enemy)
//{
//	//�g�[�e���܂ł̋������Z�o
//	float totem_dis = GetTotemDist(enemy);
//	//�v���C���[�܂ł̋������擾
//	float player_dis = GetPlayerDist(enemy);
//
//	if (player_dis <= attack_range_)
//	{
//		//�U���͈͈ȓ��Ƀv���C���[������΍U�����
//		return ENEMY_AI_STATE_ATTACK;
//	}
//	else if (player_dis <= back_range_)
//	{
//		//�x���͈͊O�Ƀv���C���[������΋A��
//		return ENEMY_AI_STATE_BACK;
//	}
//
//	//�����Ȃ���Όx���̂܂�
//	return ENEMY_AI_STATE_CAUTION;
//}

// �U����Ԃ���̑J��
int CAINomalEnemy::AINormalFromAttack(CEnemy* enemy)
{
	////�v���C���[�܂ł̋������擾
	//float player_dis = GetPlayerDist(enemy);

	//if (player_dis >= caution_range_)
	//{
	//	//�x���͈͓��Ƀv���C���[������Όx��
	//	return ENEMY_AI_STATE_CAUTION;
	//}
	//else if (player_dis >= back_range_)
	//{
	//	//�x���͈͊O�Ƀv���C���[������΋A��
	//	return ENEMY_AI_STATE_BACK;
	//}

	//�����Ȃ���΍U���̂܂�
	return ENEMY_AI_STATE_ATTACK;
}

// �̂������Ԃ���̑J��
int CAINomalEnemy::AINormalFromHitBack(CEnemy* enemy)
{
	return 0;
}

// ���S��Ԃ��������
int CAINomalEnemy::AINormalFromDead(CEnemy* enemy)
{
	return 0;
}

//// �A�ҏ�Ԃ���̑J��
//int CAINomalEnemy::AIAttackFromBack(CEnemy* enemy)
//{
//	// �v���C���[�܂ł̋������擾
//	float player_dist = GetPlayerDist(enemy);
//
//	if (player_dist <= attack_range_) {
//		// �U���͈͓��Ƀv���C���[������΍U��
//		return ENEMY_AI_STATE_ATTACK;
//	}
//	else if (player_dist <= caution_range_) {
//		// �x���͈͓��Ƀv���C���[������Όx��
//		return ENEMY_AI_STATE_CAUTION;
//	}
//
//	//���̈ʒu�܂ł̋������擾
//	float back_pos_dist = GetBackPosDist(enemy);
//	if (back_pos_dist <= 1.0f) {
//		// ���̈ʒu����1m�ȓ��ł���Αҋ@
//		return ENEMY_AI_STATE_IDLE;
//	}
//
//	//�����Ȃ���΋A�҂̂܂�
//	return ENEMY_AI_STATE_BACK;
//}