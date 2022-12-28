
//PlayScene.h
//�v���C�V�[��

#pragma once

#include "DxLib.h"
#include "Scene.h"
#include "../Player/PlayerManager.h"
#include "../Enemy/EnemyManager.h"

class CPlayScene : public CScene
{
private:
	enum PlayState
	{
		PLAY_STATE_NONE,
		PLAY_STATE_FADE,
	};

public:
	CPlayScene();
	virtual ~CPlayScene();

	////������
	//void Init();

	////���[�h
	//void Load();

	////���t���[���Ăԏ���
	//void Step();

	////�`��
	//void Draw();

	////�㏈��
	//void Fin();

	//������
	void Init()override;
	//���[�h
	void Load();
	//���[�h����
	void OnLoadEnd()override;
	//���t���[���Ăԏ���
	void Step()override;
	//�`��
	void Draw()override;
	//�㏈��
	void Fin()override;

private:
	void InitPlayer();
	void InitMap();
	void InitEnemy();
	void InitCamera();
	void InitStoneTrap();
	void InitTotem();

	void LoadPlayer();
	void LoadMap();
	void LoadEnemy();
	void LoadCamera();
	void LoadStoneTrap();
	void LoadTotem();

	void StepPlayState();

	//�v���C���[�ƓG�̓����蔻��
	void HitCheckEnemyToPlayer(CPlayer* player, CEnemy* enemy);
	//�v���C���[�̍U���ƓG�̓����蔻��
	void HitCheckEnemyToPlayerAttack(CPlayer* player, CEnemy* enemy);

private:

	PlayState state_;

};
