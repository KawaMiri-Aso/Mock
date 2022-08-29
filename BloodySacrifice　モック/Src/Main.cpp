
#include <math.h>
#include "DxLib.h"
#include "Common.h"
#include "Input/Input.h"
#include "Player/PlayerManager.h"
#include "Camera/CameraManager.h"
#include "Scene/SceneManager.h"

//------------------------------
// �萔
//------------------------------

//���֘A
#define BOX_NUM		(4)		//���̐�
#define BOX_W		(2.0f)	//���̉���
#define BOX_H		(2.0f)	//���̍���
#define BOX_D		(2.0f)	//���̉��s��

//�S�[���֘A
#define GOAL_RAD	(2.0f)	//�S�[�����a

//�t�B�[���h���
struct FieldInfo
{
	int		handle;		//�n���h��
	VECTOR	pos;		//���W
};

//�����
struct BoxInfo
{
	int		handle;		//�n���h��
	VECTOR	pos;		//���W
};

//�S�[�����
struct GoalInfo
{
	int		handle;		//�n���h��
	VECTOR	pos;		//���W
	VECTOR	rot;		//�p�x
};

//------------------------------
// �O���[�o���ϐ�
//------------------------------

//�t���[�����[�g�֘A
int g_nCurrentTime = 0;			//���݂̎���
int g_nLastFrameTime = 0;		//�O��̃t���[�����s���̎���
int g_nFrameCnt = 0;			//�t���[���J�E���g�p
int g_nUpdateFrameRateTime = 0;	//�t���[�����[�g���X�V��������
float g_fFrameRate = 0.f;		//�t���[�����[�g�i�\���p�j


//------------------------------
// �O���[�o���֐�
//------------------------------

//�t���[�����[�g�v�Z
void CalcFrameRate();

//�t���[�����[�g�\���i�f�o�b�O�p�j
void DrawFrameRate();

//�����̂̓����蔻��iAABB�j
bool IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2);

//���̓����蔻��
bool IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2);

//�v���O������ WinMain ����n�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
#ifdef _DEBUG
	SetUseDirectInputFlag(FALSE);
#endif

	ChangeWindowMode(true);	//�E�B���h�E�̏�Ԃ�ݒ肷��

	//-----------------------------------------
	//��ԍŏ��ɂP�񂾂���鏈���������ɏ���

	//DX���C�u�����̏�����
	if(DxLib_Init() == -1)
	{
		return -1;
	}

	//�E�B���h�E�T�C�Y��ύX
	SetGraphMode(WINDOW_W, WINDOW_H, 32);
	
	//�`�悷��X�N���[����ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//���ߐF��ݒ�
	SetTransColor(0, 127, 127);

	//�L�[���͏�����
	g_input.Init();

	//���f���֘A =====

	//�v���C���[�Ǘ�������
	g_player_manager.Init();

	//�v���C���[�ǂݍ���
	CPlayer *player = g_player_manager.GetPlayer();
	player->Load("Data/Model/Player/player-mock.x");

	//�t�B�[���h������
	FieldInfo field_info;
	field_info.handle = MV1LoadModel("Data/Model/Field/Field.x");
	field_info.pos = VGet(0.0f, 0.0f, 0.0f);

	//��������
	BoxInfo box_info[BOX_NUM];

	{
		VECTOR box_pos[BOX_NUM] = {
			{ -7.0f, 1.0f, 7.0f },
			{ 7.0f, 1.0f, 7.0f },
			{ -7.0f, 1.0f, -7.0f },
			{ 7.0f, 1.0f, -7.0f }
		};

		int box_original_handle = MV1LoadModel("Data/Model/Box/Box.x");

		for(int box_index = 0; box_index < BOX_NUM; box_index++)
		{
			box_info[box_index].handle = MV1DuplicateModel(box_original_handle);
			box_info[box_index].pos = box_pos[box_index];
		}

		//�R�s�[�����f���͍폜
		MV1DeleteModel(box_original_handle);
	} 

	//�S�[��������
	GoalInfo goal_info;
	goal_info.handle = MV1LoadModel("Data/Model/Goal/Goal.x");
	goal_info.pos = VGet(0.0f, 2.0f, 10.0f);
	goal_info.rot = VGet(0.0f, 0.0f, 0.0f);

	//�V�[���Ǘ�������
	g_scene_manager.Init();

	//�ŏ��̓^�C�g���V�[����
	g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_TITLE_INIT);

	//�J�����Ǘ�������
	g_camera_manager.Init();
	g_camera_manager.SetNearFar(0.1f, 150.0f);

	//-----------------------------------------

	//=====================================
	//�Q�[�����C�����[�v
	while(ProcessMessage() != -1)
	{
		Sleep(1);	//�V�X�e���ɏ�����Ԃ�

		//���݂̎������擾
		g_nCurrentTime = GetNowCount();

		// ���݂̎������A�O��̃t���[�������
		// 1/60�b�o�߂��Ă����珈�������s����

		if(g_nCurrentTime - g_nLastFrameTime >= 1000 / FRAME_RATE)
		{
			//�t���[�����s���̎��Ԃ��X�V
			g_nLastFrameTime = g_nCurrentTime;

			//�t���[�������J�E���g
			g_nFrameCnt++;

			if(CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//�G�X�P�[�v�L�[�������ꂽ��I��
				break;
			}

			//��ʂɕ\�����ꂽ���̂�������
			ClearDrawScreen();

			//�L�[���̓X�e�b�v
			g_input.Step();

			//====================
			//���f���֘A
			//====================

			//�S�[���̉�]
			goal_info.rot.y += 0.01f;

			//�V�[���Ǘ��̃��[�v
			g_scene_manager.Loop();

			//�t�B�[���h�̍��W
			MV1SetPosition(field_info.handle, field_info.pos);

			//���̍��W
			for(int box_index = 0; box_index < BOX_NUM; box_index++)
			{
				MV1SetPosition(box_info[box_index].handle, box_info[box_index].pos);
			}

			//�S�[���̉�]�ƍ��W
			MV1SetRotationXYZ(goal_info.handle, goal_info.rot);
			MV1SetPosition(goal_info.handle, goal_info.pos);

			
			//�J�����֘A =====

			//C�L�[�����ꂽ
			if(g_input.IsPush(KEY_C))
			{
				//�v���C�J�������Ȃ�
				if(g_camera_manager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
				{
					//�f�o�b�O�J�����ɕύX
					g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);

					//�f�o�b�O�J�����Ƀv���C�J�����̏���ݒ�
					CPlayCamera *play_camera = g_camera_manager.GetPlayCamera();
					CDebugCamera *debug_camera = g_camera_manager.GetDebugCamera();

					debug_camera->SetPos(play_camera->GetPos());
					debug_camera->SetLook(play_camera->GetLook());
				}
				//�f�o�b�O�J�������Ȃ�
				else
				{
					//�v���C�J�����ɕύX
					g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
				}
			}

			//�`�� =====

			//�t�B�[���h�̕`��
			MV1DrawModel(field_info.handle);

			//���̕`��
			for(int box_index = 0; box_index < BOX_NUM; box_index++)
			{
				MV1DrawModel(box_info[box_index].handle);
			}

			//�S�[���̕`��
			MV1DrawModel(goal_info.handle);

			//�t���[�����[�g�v�Z
			CalcFrameRate();

			//�t���[�����[�g�\���i�f�o�b�O�p�j
			DrawFrameRate();

			//�t���b�v�֐��i���[�v�̏I���ɂP�x�����s���j
			ScreenFlip();
		}
	}

	//-----------------------------------------
	//�Ō�ɂP�񂾂���鏈���������ɏ���

	//�J�����̌㏈��
	g_camera_manager.Fin();

	//�v���C���[�Ǘ��̌㏈��
	g_player_manager.Delete();	//�����I�ɍ폜���Ă�
	g_player_manager.Fin();		//�㏈��

	//�V�[���Ǘ��̌㏈��
	g_scene_manager.Fin();

	MV1DeleteModel(field_info.handle);	//�t�B�[���h�폜

	//���̍폜
	for(int box_index = 0; box_index < BOX_NUM; box_index++)
	{
		MV1DeleteModel(box_info[box_index].handle);
	}

	MV1DeleteModel(goal_info.handle);	//�S�[���폜

	
	//�g�p�������ׂẲ摜��j��
	InitGraph();

	//DX���C�u�����̌㏈��
	DxLib_End();

	//-----------------------------------------

	return 0;
}

//�t���[�����[�g�v�Z
void CalcFrameRate()
{
	//�O��̃t���[�����[�g�X�V����̌o�ߎ��Ԃ����߂�
	int nDifTime = g_nCurrentTime - g_nUpdateFrameRateTime;

	//�O��̃t���[�����[�g�X�V����
	//�P�b�ȏ�o�߂��Ă�����t���[�����[�g���X�V����
	if(nDifTime > 1000)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		//�����܂ŏo�������̂�float�ɃL���X�g
		float fFrameCnt = (float)(g_nFrameCnt * 1000);

		//�t���[�����[�g�����߂�
		//���z�ǂ���Ȃ� 60000 / 1000 �� 60 �ƂȂ�
		g_fFrameRate = fFrameCnt / nDifTime;

		//�t���[���J�E���g���N���A
		g_nFrameCnt = 0;

		//�t���[�����[�g�X�V���Ԃ��X�V
		g_nUpdateFrameRateTime = g_nCurrentTime;
	}
}

//�t���[�����[�g�\���i�f�o�b�O�p�j
void DrawFrameRate()
{
	DrawFormatString(695, 580, GetColor(255, 30, 30), "FPS[%.2f]", g_fFrameRate);	
}

//�����̂̓����蔻��iAABB�j
// v1			�c �Ώ�A��X,Y,Z���W�i���f���̒��S���W�j
// w1, h1, d1	�c �Ώ�A��W,H,D�i�����A�����A���s���j
// v2			�c �Ώ�B��X,Y,Z���W�i���f���̒��S���W�j
// w2, h2, d2	�c �Ώ�B��W,H�i�����A�����A���s���j
bool IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2)
{
	float w1_half = (w1 / 2);		//�Ώ�A�̉����̔����i���S����[�܂ł̒����j
	float h1_half = (h1 / 2);		//�Ώ�A�̍����̔����i���S����[�܂ł̒����j
	float d1_half = (d1 / 2);		//�Ώ�A�̉��s���̔����i���S����[�܂ł̒����j

	float x1min = v1.x - w1_half;	//�Ώ�A�̍ŏ�X
	float x1max = v1.x + w1_half;	//�Ώ�A�̍ő�X
	float y1min = v1.y - h1_half;	//�Ώ�A�̍ŏ�Y
	float y1max = v1.y + h1_half;	//�Ώ�A�̍ő�Y
	float z1min = v1.z - d1_half;	//�Ώ�A�̍ŏ�Z
	float z1max = v1.z + d1_half;	//�Ώ�A�̍ő�Z

	float w2_half = (w2 / 2);		//�Ώ�B�̉����̔����i���S����[�܂ł̒����j
	float h2_half = (h2 / 2);		//�Ώ�B�̍����̔����i���S����[�܂ł̒����j
	float d2_half = (d2 / 2);		//�Ώ�B�̉��s���̔����i���S����[�܂ł̒����j

	float x2min = v2.x - w2_half;		//�Ώ�B�̍ŏ�X
	float x2max = v2.x + w2_half;		//�Ώ�B�̍ő�X
	float y2min = v2.y - h2_half;		//�Ώ�B�̍ŏ�Y
	float y2max = v2.y + h2_half;		//�Ώ�B�̍ő�Y
	float z2min = v2.z - d2_half;		//�Ώ�B�̍ŏ�Z
	float z2max = v2.z + d2_half;		//�Ώ�B�̍ő�Z

	if(x1min < x2max && x1max > x2min && y1min < y2max && y1max > y2min && z1min < z2max && z1max > z2min )
		return true;

	return false;
}

//���Ƌ�
// v1	�c �Ώ�A�̍��W
// r1	�c �Ώ�A�̔��a
// v2	�c �Ώ�B�̍��W
// r2	�c �Ώ�B�̔��a
bool IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2)
{
	float len_x = (v2.x - v1.x) * (v2.x - v1.x);
	float len_y = (v2.y - v1.y) * (v2.y - v1.y);
	float len_z = (v2.z - v1.z) * (v2.z - v1.z);
	float len_r = (r2 + r1) * (r2 + r1);

	if (len_x + len_y + len_z <= len_r)
	{
		return true;
	}

	return false;
}
