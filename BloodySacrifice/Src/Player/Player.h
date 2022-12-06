
//Player.h
//�v���C���[�֘A

#pragma once

#include "DxLib.h"

//�v���C���[�֘A
#define PLAYER_W	(4.454f)	//�v���C���[�̉���
#define PLAYER_H	(18.6f)	//�v���C���[�̍���
#define PLAYER_D	(5.215f)	//�v���C���[�̉��s��
#define PLAYER_RAD	(9.3f)	//�v���C���[�̔��a
#define PLAYER_JUMP_VAL		(0.8f)	//�W�����v��
#define PLAYER_JUMP_TIME	(0.8f)	//�W�����v�̎���
#define PLAYER_WALK_SPEED	(0.8f)	//��������
#define PLAYER_WALK_SPEED_HALF	(PLAYER_WALK_SPEED*0.5)	//�≟�����̕�������
#define PLAYER_ROT_SCALING		(0.5f)		//���E���͗p�̐��l
#define PLAYER_ROT_SCALING_HALF	(0.25f)		//�΂ߓ��͗p�̐��l
#define ANIM_SPD (0.5f)
#define CHANGE_SPD (0.01f)	//��ԃX�s�[�h

//�v���C���[���
enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,	//�ʏ�
	PLAYER_STATE_WALK,		//������
	PLAYER_STATE_JUMP_UP,	//�W�����v�㏸��
	PLAYER_STATE_ATTACK,	//�U��
	PLAYER_STATE_DEAD,		//�Q�[���I�[�o�[
};

//�A�j���Đ�
enum {
	ANIM_MAIN,	//���C���Đ�
	ANIM_SUB,	//�T�u�Đ�

	BLEND_NUM

};

//�A�j�����
enum ANIM
{
	WAIT,		//�ҋ@
	WALK,		//����
	RUN,		//����
	ATTACK_1,	//�U��1
	ATTACK_2,	//�U��2
	HIT_BACK,	//�U���󂯂�
	DEAD,		//���S

	ANIM_NUM
};

class CPlayer
{
public:
	CPlayer();		//�R���X�g���N�^
	virtual ~CPlayer();		//�f�X�g���N�^

	//������
	void Init();
	void Init(VECTOR pos);
	//�ǂݍ���
	void Load();
	//���t���[���Ăԏ����i����j
	void Step();
	//�`��
	void Draw();
	//�폜
	void Delete();
	//�㏈��
	void Fin();

	//���W���擾
	VECTOR GetPos()const { return pos_; }
	//�ړ����x�x�N�g�����擾
	VECTOR GetSpeed()const { return speed_; }

	////��������Ă��邩
	//bool IsPushStone();
	//�v���C���[�̍U������
	void IsAttack();

	//�Q�[���I�[�o�[����
	bool Dead();

	void Damage(int damage) { hp_ -= damage; }

	//�A�j���[�V�������N�G�X�g
	void Request(int animID, float animSpd);
	//�A�j���X�V
	void AnimUpdate();

private:
	//�v���C���[�̉�]����
	void AngleProcess();

	// �A�j���Ɋւ���f�[�^
	float	m_animCount[BLEND_NUM];		// ���݂̃A�j���J�E���g
	float	m_animSpeed[BLEND_NUM];		// �A�j���[�V�������x
	int		m_animIdx[BLEND_NUM];		// �A�j���̃C���f�b�N�X�ԍ�
	float	m_animRate;					// �A�j���̃��[�g
	int		m_animType;					// ���ݍĐ����Ă���A�j���^�C�v

private:

	int				handle_;		//�n���h��
	VECTOR			pos_;			//���W
	VECTOR			speed_;			//�ړ����x�x�N�g��
	float			angle_;			//�����Ă�������̊p�x
	PLAYER_STATE	player_state_;	//���
	float			jump_time_;		//�W�����v�̎���
	int				hp_;			//HP
	int				damage_;		//�^����_���[�W
	
};
