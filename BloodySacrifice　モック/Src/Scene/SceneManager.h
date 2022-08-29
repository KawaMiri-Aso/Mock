
//SceneManager.h
//�V�[���Ǘ�
//�e�V�[���ւ̃A�N�Z�X�͕K��CSceneManager���o�R

#include "PlayScene.h"
#include "TitleScene.h"

class CSceneManager
{
public:

	//�V�[��ID
	enum SCENE_ID
	{
		SCENE_ID_PLAY_INIT,		//�v���C�V�[��������
		SCENE_ID_PLAY_LOOP,		//�v���C�V�[���J��Ԃ�
		SCENE_ID_PLAY_FIN,		//�v���C�V�[���㏈��

		SCENE_ID_TITLE_INIT,	//�^�C�g���V�[��������
		SCENE_ID_TITLE_LOOP,	//�^�C�g���V�[���J��Ԃ�
		SCENE_ID_TITLE_FIN,		//�^�C�g���V�[���㏈��
	};

public:

	CSceneManager();
	~CSceneManager();

	//������
	void Init();

	//���[�v
	void Loop();

	//�㏈��
	void Fin();

	//�����̃V�[���ɕύX����
	void ChangeScene(SCENE_ID sceneID);

	//�v���C�V�[�����擾
	CPlayScene* GetPlayScene(){ return &m_PlayScene; }

private:

	//���݂̃V�[��ID
	SCENE_ID m_eCurrentSceneID;

	//�e�V�[���̕ϐ�
	CPlayScene m_PlayScene;		//�v���C�V�[��
	CTitleScene m_TitleScene;	//�^�C�g���V�[��

};

extern CSceneManager g_scene_manager;
