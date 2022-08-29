
//CameraManager.h
//�J�����Ǘ�
//�e�J�����ւ̃A�N�Z�X�͕K��CCameraManager���o�R

#include "PlayCamera.h"
#include "TitleCamera.h"
#include "DebugCamera.h"

class CCameraManager
{
public:

	//enum��class�̒�`���ɏ������Ƃ��o����
	enum CAMERA_ID
	{
		CAMERA_ID_PLAY,		//CPlayCamera
		CAMERA_ID_TITLE,	//CTitleCamera
		CAMERA_ID_DEBUG,	//������CDebugCamera
	};

public:

	CCameraManager();
	~CCameraManager();

	//������
	void Init();

	//�X�e�b�v
	void Step();

	//�`��
	void Draw();

	//�X�V
	void Update();

	//�㏈��
	void Fin();

	//�����̃J�����ɕύX����
	void ChangeCamera(CAMERA_ID cameraID);

	//���݂̃J����ID�擾
	CAMERA_ID GetCameraID(){ return m_eCurrentCameraID; }

	//�j�A�N���b�v�E�t�@�[�N���b�v�̐ݒ�
	void SetNearFar(float near_val, float far_val);

	//�v���C�J�������擾
	CPlayCamera* GetPlayCamera(){ return &m_PlayCamera; }

	//�f�o�b�O�J�������擾
	CDebugCamera* GetDebugCamera(){ return &m_DebugCamera; }

private:

	//���݂̃J����ID
	CAMERA_ID m_eCurrentCameraID;

	//�e�J�����̕ϐ�
	CPlayCamera m_PlayCamera;	//�v���C�J����
	CTitleCamera m_TitleCamera;	//�^�C�g���J����
	CDebugCamera m_DebugCamera;	//�f�o�b�O�J����

};

extern CCameraManager g_camera_manager;
