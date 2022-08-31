#ifndef _MYMATH_H_
#define _MYMATH_H_

#include "DxLib.h"

//�x�N�g����s��̌v�Z�������܂Ƃ߂��N���X
class MyMath
{
public:
	static VECTOR VecCreate(VECTOR PosA, VECTOR PosB);//�x�N�g���쐬
	static float VecLong(VECTOR Vec);//�x�N�g���̒���
	static VECTOR VecAdd(VECTOR vecA, VECTOR vecB);//�x�N�g���̑����Z
	static VECTOR VecSubtract(VECTOR vecA, VECTOR vecB);//�x�N�g���̈����Z
	static VECTOR VecScale(VECTOR vec, float scale);//�x�N�g���̃X�J���[�{
	static float VecDot(VECTOR vecA, VECTOR vecB);//�x�N�g���̓���
	static VECTOR VecCross(VECTOR vecA, VECTOR vecB);//�x�N�g���̊O��
	static VECTOR VecNormalize(VECTOR vec);//�x�N�g���̐��K��
	static VECTOR GetPolygonNormalVec(VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);//�|���S���̖@���x�N�g��
	static MATRIX GetldentityMatrix();//�P�ʍs��̎擾
	static MATRIX GetTranslateMatrix(float x, float y, float z);//�ړ��s��̎擾
	static MATRIX GetTranslateMatrix(VECTOR trans);//�ړ��s��̎擾
	static MATRIX GetScaleMatrix(float x, float y, float z);//�g�k�s��̎擾
	static MATRIX GetPitchMatrix(float rot);//X����]�s��̎擾
	static MATRIX GetYawMatrix(float rot);//Y����]�s��̎擾
	static MATRIX GetRollMatrix(float rot);//Z����]�s��̎擾
	static MATRIX MatAdd(MATRIX matA, MATRIX matB);//�s��̑����Z
	static MATRIX MatMult(MATRIX matA, MATRIX matB);//�s��̊|���Z
	static MATRIX MatScale(MATRIX mat, float scale);//�s��̃X�J���[�{
	static VECTOR MatTransform(MATRIX mat, VECTOR vec);//�x�N�g���~�s��
	static MATRIX MatTranspose(MATRIX mat);//�s��̓]�u
	static float GetTriangleHeightXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static float GetTriangleHeightXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static float GetTriangleHeightYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	static float Abs(float val);
	static float GetDistance(VECTOR posA, VECTOR posB);
};
#endif