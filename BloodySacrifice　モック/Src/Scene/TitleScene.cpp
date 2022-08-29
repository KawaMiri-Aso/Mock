
//TitleScene.cpp
//�^�C�g���V�[��

#include "TitleScene.h"
#include "SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/PlayerManager.h"
#include "../Input/Input.h"

CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
}

//������
void CTitleScene::Init()
{
	//�^�C�g���J�����ɕύX
	g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_TITLE);

	//���̓^�C�g���V�[���̌J��Ԃ���
	g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_TITLE_LOOP);
}

//���t���[���Ăԏ���
void CTitleScene::Step()
{
	//ENTER�����ꂽ
	if(g_input.IsPush(KEY_ENTER))
	{
		g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_TITLE_FIN);
	}

	//�J�������_�E�����_�̑���
	g_camera_manager.Step();

	//�J�������_�E�����_�̔��f
	g_camera_manager.Update();

}

//�`��
void CTitleScene::Draw()
{
	//�J�����̕`��
	g_camera_manager.Draw();

	//������`��
	DrawString(10, 10, "�^�C�g�����", GetColor(255, 255, 255));
	DrawString(10, 26, "Enter��������v���C��", GetColor(255, 255, 0));
}

//�㏈��
void CTitleScene::Fin()
{
	//���̓v���C�V�[���̏�������
	g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_PLAY_INIT);
}

