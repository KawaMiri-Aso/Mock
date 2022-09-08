#include "Map.h"

CMap g_map;

CMap::CMap()
{
	// ���f��
	handle_ = -1;
	// �����蔻��p���f��
	col_handle_ = -1;
	pos_ = { 0 };
}

CMap::~CMap()
{
}

//������
void CMap::Init()
{
	// ���f���ǂݍ���
	handle_ = MV1LoadModel("Data/Model/Field/Field.x");
	// �����蔻��p���f���ǂݍ���
	col_handle_ = MV1LoadModel("Data/Model/Field/coll_Field.x");
	// �����蔻��p���f���̃|���S�������Z�b�g�A�b�v
	MV1SetupCollInfo(col_handle_);
	pos_ = { 0 };
}

//�X�e�b�v
void CMap::Step()
{

}

//�X�V
void CMap::Update()
{
	//�}�b�v�̍��W
	MV1SetPosition(handle_, pos_);
	// �|���S�������X�V����
	MV1RefreshReferenceMesh(col_handle_, -1, TRUE);
}

//�`��
void CMap::Draw()
{
	MV1DrawModel(handle_);
}

//�㏈��();
void CMap::Fin()
{
	MV1DeleteModel(handle_);
	MV1DeleteModel(col_handle_);
}

VECTOR CMap::HitCheck(VECTOR vCenter, float fRadius)
{
	VECTOR	vOut = { 0 };	//�@���̂��w�i�ɂ߂荞�񂾋���

	MV1_COLL_RESULT_POLY_DIM	res;	// �����蔻�茋�ʊi�[�\����
	res = MV1CollCheck_Sphere(col_handle_, -1, vCenter, fRadius);	// ���̓����蔻�茋�ʊi�[

	// ���������|���S���̐������J�Ԃ�
	for (int i = 0; i < res.HitNum; i++)
	{
		//	�q�b�g�����|���S���ƃq�b�g�������̂̂߂荞�񂾋��������߂�
		VECTOR	vSub = VSub(res.Dim[i].HitPosition, vCenter);
		float	fLen = VSize(vSub);
		fLen = fRadius - fLen;
		// �߂荞�񂾋����������O�ɉ����o���@�����o�������͖@���̕���
		VECTOR	vLine = VScale(res.Dim[i].Normal, fLen);
		
		vOut = VAdd(vOut, vLine);
	}
	//�������Ă�|���S���������@�����|���Ă�̂ŁA���̕�����
	if (res.HitNum >= 2)
	{
		vOut.x /= res.HitNum;
		vOut.y /= res.HitNum;
		vOut.z /= res.HitNum;
	}
	// �����蔻�茋�ʂ�j������
	MV1CollResultPolyDimTerminate(res);

	return vOut;
}