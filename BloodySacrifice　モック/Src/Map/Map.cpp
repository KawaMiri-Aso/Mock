#include "Map.h"

CMap g_map;

CMap::CMap()
{
	// ���f��
	handle = -1;
	// �����蔻��p���f��
	col_handle = -1;
	pos = { 0 };
}

CMap::~CMap()
{
}

//������
void CMap::Init()
{
	// ���f���ǂݍ���
	handle = MV1LoadModel("Data/Model/Field/Field.x");
	// �����蔻��p���f���ǂݍ���
	col_handle = MV1LoadModel("Data/Model/Field/coll_Field.x");
	// �����蔻��p���f���̃|���S�������Z�b�g�A�b�v
	MV1SetupReferenceMesh(col_handle, -1, TRUE);
	pos = { 0 };
}

//�X�e�b�v
void CMap::Step()
{

}

//�X�V
void CMap::Update()
{
	//�}�b�v�̍��W
	MV1SetPosition(handle, pos);
	// �|���S�������X�V����
	MV1RefreshReferenceMesh(col_handle, -1, TRUE);
}

//�`��
void CMap::Draw()
{
	MV1DrawModel(handle);
}

//�㏈��();
void CMap::Fin()
{
	MV1DeleteModel(handle);
	MV1DeleteModel(col_handle);
}