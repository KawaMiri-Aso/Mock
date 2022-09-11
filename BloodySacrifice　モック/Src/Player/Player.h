
//Player.h
//�v���C���[�֘A

#pragma once

#include "DxLib.h"

//�v���C���[�֘A
#define PLAYER_W	(4.8f)	//�v���C���[�̉���
#define PLAYER_H	(12.8f)	//�v���C���[�̍���
#define PLAYER_D	(3.2f)	//�v���C���[�̉��s��
#define PLAYER_RAD	(6.4f)	//�v���C���[�̔��a
#define PLAYER_JUMP_VAL		(0.3f)	//�W�����v��
#define PLAYER_JUMP_TIME	(0.8f)	//�W�����v�̎���
#define PLAYER_WALK_SPEED	(0.6f)	//��������
#define PLAYER_WALK_SPEED_HALF	(0.3f)		//�≟�����̕�������
#define PLAYER_ROT_SCALING		(0.5f)		//���E���͗p�̐��l
#define PLAYER_ROT_SCALING_HALF	(0.25f)		//�΂ߓ��͗p�̐��l

//�v���C���[���
enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,	//�ʏ�
	PLAYER_STATE_JUMP_UP,	//�W�����v�㏸��
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
	//�v���C���[�̉�]����
	void AngleProcess();
	//��������Ă��邩
	bool IsPushStone();

private:

	int				handle_;		//�n���h��
	VECTOR			pos_;			//���W
	VECTOR			speed_;			//�ړ����x�x�N�g��
	float			angle_;			//�����Ă�������̊p�x
	PLAYER_STATE	player_state_;	//���
	float			jump_time_;		//�W�����v�̎���
	int				hp_;			//HP
	
};
