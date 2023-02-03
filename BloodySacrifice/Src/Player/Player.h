
//Player.h
//�v���C���[�֘A

#pragma once

#include "DxLib.h"

//�v���C���[�֘A
#define PLAYER_W	(4.454f)	//�v���C���[�̉���
#define PLAYER_H	(18.6f)		//�v���C���[�̍���
#define PLAYER_D	(5.215f)	//�v���C���[�̉��s��
#define PLAYER_RAD	(9.3f)		//�v���C���[�̔��a
#define PLAYER_JUMP_VAL		(30.0f)	//�W�����v��
#define PLAYER_JUMP_TIME	(0.8f)	//�W�����v�̎���
#define PLAYER_WALK_SPEED	(0.8f)	//��������
#define PLAYER_RUN_SPEED	(1.8f)	//���鑬��
#define PLAYER_WALK_SPEED_HALF	(PLAYER_WALK_SPEED * 0.5)	//�≟�����̕�������
#define PLAYER_ROT_SCALING		(0.5f)		//���E���͗p�̐��l
#define PLAYER_ROT_SCALING_HALF	(0.25f)		//�΂ߓ��͗p�̐��l
#define ANIM_SPD (1.0f)
#define CHANGE_SPD (0.05f)	//��ԃX�s�[�h
#define ATTACK_COL_RAD	(15.0f)

//�v���C���[���
enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,	//�ʏ�
	PLAYER_STATE_WALK,		//������
	PLAYER_STATE_RUN,		//���蒆
	PLAYER_STATE_JUMP_UP,	//�W�����v�㏸��
	PLAYER_STATE_ATTACK1,	//�U��1
	PLAYER_STATE_ATTACK2,	//�U��2
	PLAYER_STATE_END_COMBO,	//�R���{�I��
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
	END_COMBO,	//�R���{�I��
	HIT_BACK,	//�̂�����
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

	//******************************
	//�ݒ�֐�
	//******************************
	//void SetCameraRot(VECTOR camRot) { camrot_ = camRot; }

	//���W�ݒ�
	inline void	SetPos(VECTOR pos) { pos_ = pos; }
	//��]�p�x�ݒ�
	inline void SetRot(VECTOR rot) { rot_ = rot; }

	//******************************
	//�擾�֐�
	//******************************

	//���W���擾
	inline VECTOR GetPos() { return pos_; }
	//�ړ����x�x�N�g�����擾
	VECTOR GetSpeed()const { return speed_; }
	//��]�p�x���擾
	inline VECTOR GetRot() { return rot_; }
	//��Ԃ��擾
	inline int GetState() { return player_state_; }

	//�U���̓����蔻��p
	bool IsAttack();
	//�U���������W���擾
	VECTOR GetAttackPos();
	//�U�������蔻��̒��S�ʒu�擾
	VECTOR GetLeftHand();
	//�U�������蔻��̒��S�ʒu�擾
	VECTOR GetRightHand();

	//�Q�[���I�[�o�[����
	bool Dead();

	void Damage(int damage) { hp_ -= damage; }

	//�A�j���[�V�������N�G�X�g
	void Request(int animID, float animSpd);
	//�A�j���X�V
	void AnimUpdate();
	//���ݍĐ����Ă���A�j���^�C�v���擾
	inline int GetAnimType() { return m_animType; }

private:
	//�v���C���[�̉�]����
	void AngleProcess();

	//�ړ�����
	bool CalcMove();
	//�W�����v����
	void CalcJump();
	//�U��1
	void CalcAttack1();
	//�U��2
	void CalcAttack2();
	//�R���{�I��
	void EndCombo();

	// �A�j���Ɋւ���f�[�^
	float	m_animCount[BLEND_NUM];		// ���݂̃A�j���J�E���g
	float	m_animSpeed[BLEND_NUM];		// �A�j���[�V�������x
	int		m_animIdx[BLEND_NUM];		// �A�j���̃C���f�b�N�X�ԍ�
	float	m_animRate;					// �A�j���̃��[�g
	int		m_animType;					// ���ݍĐ����Ă���A�j���^�C�v
	bool	IsCombo_;					// �R���{�t���O

private:

	int				handle_;		//�n���h��
	VECTOR			pos_;			//���W
	VECTOR			speed_;			//�ړ����x�x�N�g��
	VECTOR			camrot_;
	VECTOR			rot_;			//��]�p�x
	float			angle_;			//�����Ă�������̊p�x
	PLAYER_STATE	player_state_;	//���
	float			jump_time_;		//�W�����v�̎���
	int				hp_;			//HP
	int				damage_;		//�^����_���[�W
	ANIM			anim_state_;	//�A�j�����
};
