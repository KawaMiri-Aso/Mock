
//CameraManager.cpp
//�J�����Ǘ�
//�e�J�����ւ̃A�N�Z�X�͕K��CCameraManager���o�R

#include "CameraManager.h"

CCameraManager g_camera_manager;

CCameraManager::CCameraManager()
{
}

CCameraManager::~CCameraManager()
{
}

//������
void CCameraManager::Init()
{
	//�S�ẴJ�����̏�����
	m_PlayCamera.Init(VGet(15.0f, 30.0f, 15.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
	m_TitleCamera.Init(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
	m_DebugCamera.Init(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
}

//�X�e�b�v
void CCameraManager::Step()
{
	//���݂̃J����ID�ɂ���ăX�e�b�v������U�蕪����
	switch (m_eCurrentCameraID)
	{
		//�v���C�J�����̏���
		case CAMERA_ID_PLAY:
			m_PlayCamera.Step();
			break;

		//�^�C�g���J�����̏���
		case CAMERA_ID_TITLE:
			m_TitleCamera.Step();
			break;

		//�f�o�b�O�J�����̏���
		case CAMERA_ID_DEBUG:
			m_DebugCamera.Step();
			break;
	}
}

//�`��
void CCameraManager::Draw()
{
	//���݂̃J����ID�ɂ���ăX�e�b�v������U�蕪����
	switch (m_eCurrentCameraID)
	{
		//�f�o�b�O�J�����̏���
		case CAMERA_ID_DEBUG:
			m_DebugCamera.Draw();
			break;
	}
}

//�X�V
void CCameraManager::Update()
{
	//���݂̃J����ID�ɂ���čX�V������U�蕪����
	switch (m_eCurrentCameraID)
	{
		//�v���C�J�����̏���
		case CAMERA_ID_PLAY:
			m_PlayCamera.Update();
			break;

		//�^�C�g���J�����̏���
		case CAMERA_ID_TITLE:
			m_TitleCamera.Update();
			break;

		//�f�o�b�O�J�����̏���
		case CAMERA_ID_DEBUG:
			m_DebugCamera.Update();
			break;
	}
}

//�㏈��
void CCameraManager::Fin()
{
	//�S�ẴJ�����̌㏈��
	m_PlayCamera.Fin();
	m_TitleCamera.Fin();
	m_DebugCamera.Fin();
}

//�����̃J�����ɕύX����
void CCameraManager::ChangeCamera(CAMERA_ID cameraID)
{
	//���݂̃J����ID��ύX����
	m_eCurrentCameraID = cameraID;
}

//�j�A�N���b�v�E�t�@�[�N���b�v�̐ݒ�
void CCameraManager::SetNearFar(float near_val, float far_val)
{
	SetCameraNearFar(near_val, far_val);
}

