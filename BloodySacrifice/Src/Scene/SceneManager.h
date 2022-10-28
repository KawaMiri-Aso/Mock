
//SceneManager.h
//�V�[���Ǘ�
//�e�V�[���ւ̃A�N�Z�X�͕K��CSceneManager���o�R
#pragma once

#include "Scene.h"

class CSceneManager
{
public:
	//�V�[�����
	enum SCENE_STATE
	{
		SCENE_STATE_INIT,		//������
		SCENE_STATE_LOAD,		//���[�h
		SCENE_STATE_LOAD_END,	//���[�h�I��
		SCENE_STATE_LOOP,		//���[�v
		SCENE_STATE_FIN,		//�㏈��
	};

	//�V�[��ID
	enum SCENE_ID
	{
		SCENE_ID_TITLE,			//�^�C�g���V�[��
		SCENE_ID_PLAY,			//�v���C�V�[��
		SCENE_ID_CLEAR,			//�N���A�V�[��
		SCENE_ID_GAMEOVER,		//�Q�[���I�[�o�[�V�[��
	};

public:

	static void CreateInstance() { if (!instance_)instance_ = new CSceneManager; }
	static CSceneManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

	CSceneManager();
	~CSceneManager();

	//������
	void Init();

	//���[�v
	void Loop();

	//�㏈��
	void Fin();

	//�P�ԍŏ��̃V�[�����J�n����
	void StartFirstScene(SCENE_ID sceneID);

	//�����̃V�[���ɕύX����
	void ChangeScene(SCENE_ID sceneID);

	////�v���C�V�[�����擾
	//CPlayScene* GetPlayScene(){ return &m_PlayScene; }

private:
	//�V�[���𐶐�����
	void CreateScene(SCENE_ID sceneID);

	//���̉�ʂɑJ�ڂ�����
	void ChangeNextScene();

private:
	//�C���X�^���X
	static CSceneManager* instance_;

	//���݂̃V�[��ID
	SCENE_ID m_eCurrentSceneID;
	SCENE_ID m_eNextSceneID;
	SCENE_STATE m_eCurrentSceneState;

	CScene* scene_;

	////�e�V�[���̕ϐ�
	//CPlayScene m_PlayScene;		//�v���C�V�[��
	//CTitleScene m_TitleScene;	//�^�C�g���V�[��

};