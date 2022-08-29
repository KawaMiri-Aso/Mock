
//PlayScene.cpp
//�v���C�V�[��

#include "PlayScene.h"
#include "SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/PlayerManager.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
}

//������
void CPlayScene::Init()
{
	//�V���ǂݍ���
	m_sky_handle = MV1LoadModel("Data/Model/Sky/Sky.x");

	//�V���̃T�C�Y��傫������
	MV1SetScale(m_sky_handle, VGet(100.0f, 100.0f, 100.0f));

	//�v���C�J�����ɕύX
	g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);

	//���̓v���C�V�[���̌J��Ԃ���
	g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_PLAY_LOOP);
}

//���t���[���Ăԏ���
void CPlayScene::Step()
{
	//�v���C�J�������Ȃ�
	if(g_camera_manager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
	{
		//�v���C���[�Ǘ��X�e�b�v
		g_player_manager.Step();
	}

	//�J�������_�E�����_�̑���
	g_camera_manager.Step();

	//�J�����̍��W���I�������ɓV���̏���
	//�v���C�J�������擾���āA�J�����̍��W�ɓV����u��
	CPlayCamera *play_camera = g_camera_manager.GetPlayCamera();
	MV1SetPosition(m_sky_handle, play_camera->GetPos());

	//�J�������_�E�����_�̔��f
	g_camera_manager.Update();

}

//�`��
void CPlayScene::Draw()
{
	//�v���C���[�Ǘ��`��
	g_player_manager.Draw();

	//�V���`��
	MV1DrawModel(m_sky_handle);

	//�J�����̕`��
	g_camera_manager.Draw();

	//������`��
	DrawString(10, 10, "���E�L�[�ŉ�]�A�㉺�L�[�ňړ�", GetColor(255, 255, 255));
	DrawString(10, 26, "�X�y�[�X�ŃW�����v", GetColor(255, 255, 255));
	DrawString(10, 42, "�S�[���ɓ�����Ə����ꏊ�ɖ߂�", GetColor(255, 255, 255));
	DrawString(10, 58, " <�S�[���Ƃ͋��̓����蔻��>", GetColor(255, 255, 128));
	DrawString(10, 74, " <���Ƃ͒����̂̓����蔻��>", GetColor(255, 255, 128));
}

//�㏈��
void CPlayScene::Fin()
{
	MV1DeleteModel(m_sky_handle);
}

