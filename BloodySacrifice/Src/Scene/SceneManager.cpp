
//SceneManager.cpp
//�V�[���Ǘ�
//�e�V�[���ւ̃A�N�Z�X�͕K��CSceneManager���o�R

#include "SceneManager.h"
#include "PlayScene.h"

CSceneManager* CSceneManager::instance_ = nullptr;

CSceneManager::CSceneManager()
{
	scene_ = nullptr;
	m_eCurrentSceneState = SCENE_STATE_INIT;
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
	switch(m_eCurrentSceneState)
	{

	//�V�[��������
	case SCENE_STATE_INIT:
		scene_->Init();
		m_eCurrentSceneState = SCENE_STATE_LOAD;
		break;

	//�V�[���J��Ԃ�
	case SCENE_STATE_LOAD:
		scene_->Load();
		m_eCurrentSceneState = SCENE_STATE_LOAD_END;
		break;

	//�V�[�����[�h����
	case SCENE_STATE_LOAD_END:
		scene_->OnLoadEnd();
		m_eCurrentSceneState = SCENE_STATE_LOOP;
		break;

	//�V�[���J��Ԃ�
	case SCENE_STATE_LOOP:
		scene_->Step();
		scene_->Draw();	//�`��̓X�e�b�v�̌�ɌĂ�
		break;

	//�^�C�g���V�[���㏈��
	case SCENE_STATE_FIN:
		scene_->Fin();
		ChangeNextScene();
		break;

	}

}


//�㏈��
void CSceneManager::Fin()
{
	if (scene_)
	{
		delete scene_;
	}
}

//�P�ԍŏ��̃V�[�����J�n����
void CSceneManager::StartFirstScene(SCENE_ID sceneID)
{
	//���ɉ����V�[���������Ă�̂ł���Α��I��
	if (scene_) return;

	//�V�[���𐶐����ď���������J�n����
	CreateScene(sceneID);
	m_eCurrentSceneID = sceneID;
	m_eCurrentSceneState = SCENE_STATE_INIT;
}

//�����̃V�[���ɕύX����
void CSceneManager::ChangeScene(SCENE_ID sceneID)
{
	//���ɑJ�ڂ���V�[�����o���Ă����A�I��������
	m_eNextSceneID = sceneID;
	m_eCurrentSceneState = SCENE_STATE_FIN;
}

//�V�[���𐶐�����
void CSceneManager::CreateScene(SCENE_ID sceneID)
{
	//�V�[���𐶐�
	switch (sceneID) {
	case SCENE_ID_PLAY: scene_ = new CPlayScene; break;
	}
}

//���̉�ʂɑJ�ڂ�����
void CSceneManager::ChangeNextScene()
{
}
