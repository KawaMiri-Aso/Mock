
//SceneManager.cpp
//�V�[���Ǘ�
//�e�V�[���ւ̃A�N�Z�X�͕K��CSceneManager���o�R

#include "SceneManager.h"

CSceneManager g_scene_manager;

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
}

//������
void CSceneManager::Init()
{
	//�����̓V�[���Ǘ��̏������ł����āA
	//�e�V�[���̏������ł͂Ȃ�
}

//���[�v
void CSceneManager::Loop()
{
	switch(m_eCurrentSceneID)
	{

	//�v���C�V�[��������
	case SCENE_ID_PLAY_INIT:
		m_PlayScene.Init();
		break;

	//�v���C�V�[���J��Ԃ�
	case SCENE_ID_PLAY_LOOP:
		m_PlayScene.Step();
		m_PlayScene.Draw();	//�`��̓X�e�b�v�̌�ɌĂ�
		break;

	//�v���C�V�[���㏈��
	case SCENE_ID_PLAY_FIN:
		m_PlayScene.Fin();
		break;

	//�^�C�g���V�[��������
	case SCENE_ID_TITLE_INIT:
		m_TitleScene.Init();
		break;

	//�^�C�g���V�[���J��Ԃ�
	case SCENE_ID_TITLE_LOOP:
		m_TitleScene.Step();
		m_TitleScene.Draw();
		break;

	//�^�C�g���V�[���㏈��
	case SCENE_ID_TITLE_FIN:
		m_TitleScene.Fin();
		break;

	}

}


//�㏈��
void CSceneManager::Fin()
{
}

//�����̃V�[���ɕύX����
void CSceneManager::ChangeScene(SCENE_ID sceneID)
{
	//�V�[��ID��ύX
	m_eCurrentSceneID = sceneID;
}
