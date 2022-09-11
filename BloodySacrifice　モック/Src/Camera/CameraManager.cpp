
//CameraManager.cpp
//�J�����Ǘ�
//�e�J�����ւ̃A�N�Z�X�͕K��CCameraManager���o�R

#include "CameraManager.h"

CCameraManager* CCameraManager::instance_ = nullptr;

CCameraManager::CCameraManager()
	:camera_(nullptr)
{
	Init();
}

CCameraManager::~CCameraManager()
{
}

//������
void CCameraManager::Init()
{
	////�S�ẴJ�����̏�����
	//m_PlayCamera.Init(VGet(45.0f, 50.0f, 45.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
	//m_DebugCamera.Init(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
}

//�X�e�b�v
void CCameraManager::Step()

{
	//���݂̃J����ID�ɂ���ăX�e�b�v������U�蕪����
	switch (m_eCurrentCameraID)
	{
		//�v���C�J�����̏���
		case CAMERA_ID_PLAY:
			camera_->Step();
			break;

		//�f�o�b�O�J�����̏���
		case CAMERA_ID_DEBUG:
			camera_->Step();
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
		camera_->Update();
		break;

		//�f�o�b�O�J�����̏���
	case CAMERA_ID_DEBUG:
		camera_->Update();
		break;
	}
}

//�`��
void CCameraManager::Draw()
{
	////���݂̃J����ID�ɂ���ăX�e�b�v������U�蕪����
	//switch (m_eCurrentCameraID)
	//{
	//	//�f�o�b�O�J�����̏���
	//	case CAMERA_ID_DEBUG:
	//		m_DebugCamera.Draw();
	//		break;
	//}
}

//�㏈��
void CCameraManager::Fin()
{
	////�S�ẴJ�����̌㏈��
	//m_PlayCamera.Fin();
	//m_DebugCamera.Fin();
}


void CCameraManager::StartCamera(CAMERA_ID id)
{
	if (camera_) delete camera_;

	switch (id) {
	case CAMERA_ID_PLAY: camera_ = new CPlayCamera; break;
	}
	camera_->Init();
}

//�����̃J�����ɕύX����
//void CCameraManager::ChangeCamera(CAMERA_ID cameraID)
//{
//	//���݂̃J����ID��ύX����
//	m_eCurrentCameraID = cameraID;
//}

//�j�A�N���b�v�E�t�@�[�N���b�v�̐ݒ�
void CCameraManager::SetNearFar(float near_val, float far_val)
{
	SetCameraNearFar(near_val, far_val);
}

