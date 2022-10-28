
//CameraManager.h
//�J�����Ǘ�
//�e�J�����ւ̃A�N�Z�X�͕K��CCameraManager���o�R
#pragma once

class CCameraBase;
class CPlayCamera;
class CDebugCamera;

class CCameraManager
{
public:

	//enum��class�̒�`���ɏ������Ƃ��o����
	enum CAMERA_ID
	{
		CAMERA_ID_PLAY,		//CPlayCamera
		CAMERA_ID_DEBUG,	//������CDebugCamera
	};

public:

	CCameraManager();
	~CCameraManager();

	static void CreateInstance() { if (!instance_) instance_ = new CCameraManager; }
	static CCameraManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

	//������
	void Init();
	//�X�e�b�v
	void Step();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�㏈��
	void Fin();

	void StartCamera(CAMERA_ID id);

	//�����̃J�����ɕύX����
	void ChangeCamera(CAMERA_ID cameraID);

	//�j�A�N���b�v�E�t�@�[�N���b�v�̐ݒ�
	void SetNearFar(float near_val, float far_val);

	//�v���C�J�������擾
	CPlayCamera* GetPlayCamera() { return m_PlayCamera; }

	//�f�o�b�O�J�������擾
	CDebugCamera* GetDebugCamera() { return m_DebugCamera; }

private:

	//�e�J�����̕ϐ�
	CPlayCamera* m_PlayCamera;	//�v���C�J����
	CDebugCamera* m_DebugCamera;	//�f�o�b�O�J����

	//���݂̃J����ID
	CAMERA_ID m_eCurrentCameraID;

	static CCameraManager* instance_;
	//CCameraBase* camera_;
};