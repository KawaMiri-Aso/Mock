
//PlayScene.cpp
//�v���C�V�[��

#include "PlayScene.h"
#include "SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/PlayerManager.h"
#include "../Map/Map.h"
#include "../Collision/Collision.h"
#include "../Trap/Stone.h"

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

	//�t�B�[���h������
	g_map.Init();

	//��㩏�����
	g_stone_trap.Init(VGet(-30.0f, 12.0f, 0.0f));

	//�V���̃T�C�Y��傫������
	MV1SetScale(m_sky_handle, VGet(150.0f, 150.0f, 150.0f));

	//�v���C�J�����ɕύX
	g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);

	//���̓v���C�V�[���̌J��Ԃ���
	g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_PLAY_LOOP);
}

//���t���[���Ăԏ���
void CPlayScene::Step()
{
	// �}�b�v�X�e�b�v
	g_map.Step();
	// �v���C���[�̓����蔻�����邽�ߍX�V���Ă�
	g_map.Update();

	g_stone_trap.Step();

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
	//�t�B�[���h�̕`��
	g_map.Draw();

	g_stone_trap.Draw();

	//�v���C���[�Ǘ��`��
	g_player_manager.Draw();

	//�V���`��
	MV1DrawModel(m_sky_handle);

	//�J�����̕`��
	g_camera_manager.Draw();

	//������`��
	DrawString(10, 10, "�㉺���E�ňړ�", GetColor(255, 255, 255));
	DrawString(10, 26, "�X�y�[�X�ŃW�����v", GetColor(255, 255, 255));
	DrawString(10, 42, " <���Ƃ͒����̂̓����蔻��>", GetColor(255, 255, 128));
}

//�㏈��
void CPlayScene::Fin()
{
	//�t�B�[���h�폜
	g_map.Fin();

	g_stone_trap.Fin();

	MV1DeleteModel(m_sky_handle);
}

