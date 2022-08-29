#include "MyMath.h"
#include <math.h>

// �_P(x1, y1)����_Q(x2, y2)�܂ł̋�����Ԃ�
float CMyMath::GetDistance(float x1, float y1, float x2, float y2)
{
	// �_P����_Q�܂ł̒������ΕӂƂ��钼�p�O�p�`�����A
	// �s�^�S���X�̒藝����Εӂ̒������v�Z����B
	// �@�܂��͒�ӂ̒������v�Z����
	float a = x2 - x1;

	// �A�������v�Z����
	float b = y2 - y1;

	// �B�Εӂ�2��̒l���v�Z����
	float double_c = a * a + b * b;

	// �C2��̒l�Ȃ̂ŕ��������v�Z���Ē����Ƃ���
	// �@��������<math.h>��sqrtf�֐��Ŏ擾�ł���
	return sqrtf(double_c);
}

// ��]�l��0�`2�΂̒l�ɂ���
float CMyMath::RadianNormalize(float rad)
{
	float result = rad;
	if (result < 0.0f) {
		while (result < 0.0f) {
			result += DX_TWO_PI_F;
		}
	}
	else if (result > DX_TWO_PI_F) {
		while (result <= DX_TWO_PI_F) {
			result -= DX_TWO_PI_F;
		}
	}

	return result;
}

// �n�_�ƏI�_����x�N�g�����쐬
VECTOR CMyMath::VecCreate(VECTOR start, VECTOR end)
{
	VECTOR result;

	// �@�x�N�g���́u�I�_ - �n�_�v�ŋ��߂���
	result.x = end.x - start.x;
	result.y = end.y - start.y;
	result.z = end.z - start.z;

	return result;
}

// �x�N�g���̑����Z
VECTOR CMyMath::VecAdd(VECTOR vec1, VECTOR vec2)
{
	VECTOR result;

	// �@�e�����𑫂��Z����
	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;

	return result;
}

// �x�N�g���̒���
float CMyMath::VecLong(VECTOR vec)
{
	// �@�s�^�S���X�̒藝����x�N�g���̒��������߂�
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}


// �x�N�g���̐��K��
VECTOR CMyMath::VecNormalize(VECTOR vec)
{
	VECTOR result;

	// �@�x�N�g���̒��������߂�
	float vec_long = VecLong(vec);

	// �A�e�����𒷂��Ŋ��邱�Ƃɂ�萳�K������
	result.x = vec.x / vec_long;
	result.y = vec.y / vec_long;
	result.z = vec.z / vec_long;

	return result;
}

// �x�N�g���̃X�J���[�{
VECTOR CMyMath::VecScale(VECTOR vec, float scale)
{
	VECTOR result;

	// �@�e�������X�J���[�{����
	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;

	return result;
}

// �x�N�g���̓���
float CMyMath::VecDot(VECTOR vec1, VECTOR vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

// �x�N�g���̌��������W�A���l�Ŏ擾
float CMyMath::VecDir(VECTOR vec)
{
	return atan2f(vec.y, vec.x);
}

//�P�ʍs����擾
MATRIX CMyMath::GetIdentityMatrix()
{
	MATRIX result = { 0.0f };

	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	return result;
}

//���s�ړ��s����擾
MATRIX CMyMath::GetTranslateMatrix(float x, float y, float z)
{
	MATRIX result = GetIdentityMatrix();

	result.m[0][3] = x;
	result.m[1][3] = y;
	result.m[2][3] = z;

	return result;
}

MATRIX CMyMath::GetTranslateMatrix(VECTOR translation)
{
	return GetTranslateMatrix(translation.x, translation.y, translation.z);
}

//�g�k�s����擾
MATRIX CMyMath::GetScaleMatrix(float x, float y, float z)
{
	MATRIX result = GetIdentityMatrix();

	result.m[0][0] = x;
	result.m[1][1] = y;
	result.m[2][2] = z;

	return result;
}

MATRIX CMyMath::GetScaleMatrix(VECTOR scale)
{
	return GetScaleMatrix(scale.x, scale.y, scale.z);
}

//X����]�s����擾
MATRIX CMyMath::GetPitchMatrix(float rot)
{
	MATRIX result = GetIdentityMatrix();
	result.m[1][1] = cosf(rot);
	result.m[1][2] = -sinf(rot);
	result.m[2][1] = sinf(rot);
	result.m[2][2] = cosf(rot);

	return result;
}

//Y����]�s����擾
MATRIX CMyMath::GetYawMatrix(float rot)
{
	MATRIX result = GetIdentityMatrix();
	result.m[0][0] = cosf(rot);
	result.m[0][2] = sinf(rot);
	result.m[2][0] = -sinf(rot);
	result.m[2][2] = cosf(rot);

	return result;
}

//Z����]�s����擾
MATRIX CMyMath::GetRollMatrix(float rot)
{
	MATRIX result = GetIdentityMatrix();
	result.m[0][0] = cosf(rot);
	result.m[0][1] = -sinf(rot);
	result.m[1][0] = sinf(rot);
	result.m[1][1] = cosf(rot);

	return result;
}

//�s��̑����Z
MATRIX CMyMath::MatAdd(MATRIX matA, MATRIX matB)
{
	MATRIX result = { 0.0f };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = matA.m[i][j] + matB.m[i][j];
		}
	}

	return result;
}

//�s��̈����Z
MATRIX CMyMath::MatSub(MATRIX matA, MATRIX matB)
{
	MATRIX result = { 0.0f };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = matA.m[i][j] - matB.m[i][j];
		}
	}

	return result;
}

//�s����X�J���[�{����
MATRIX CMyMath::MatScale(MATRIX mat, float scale)
{
	MATRIX result = { 0.0f };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = mat.m[i][j] * scale;
		}
	}

	return result;
}

//2�̍s��̊|���Z
MATRIX CMyMath::MatMult(MATRIX matA, MATRIX matB)
{
	MATRIX result = { 0.0f };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result.m[i][j] += matA.m[i][k] * matB.m[k][j];
			}
		}
	}

	return result;
}

//�s��~�x�N�g��
VECTOR CMyMath::MatTransform(MATRIX mat, VECTOR pos)
{
	float work[4] = { pos.x,pos.y,pos.z,1.0f };
	float transform[4] = { 0.0f };
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			transform[i] += mat.m[i][j] * work[j];
		}
	}

	return VGet(transform[0], transform[1], transform[2]);
}

//�s��]�u
MATRIX CMyMath::MatTranspse(MATRIX mat)
{
	MATRIX result = { 0.0f };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = result.m[j][i];
		}
	}

	return result;
}