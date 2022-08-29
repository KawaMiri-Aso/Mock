#include "MyMath.h"
#include <math.h>

// 点P(x1, y1)から点Q(x2, y2)までの距離を返す
float CMyMath::GetDistance(float x1, float y1, float x2, float y2)
{
	// 点Pから点Qまでの直線を斜辺とする直角三角形を作り、
	// ピタゴラスの定理から斜辺の長さを計算する。
	// ①まずは底辺の長さを計算する
	float a = x2 - x1;

	// ②高さを計算する
	float b = y2 - y1;

	// ③斜辺の2乗の値を計算する
	float double_c = a * a + b * b;

	// ④2乗の値なので平方根を計算して長さとする
	// 　平方根は<math.h>のsqrtf関数で取得できる
	return sqrtf(double_c);
}

// 回転値を0～2πの値にする
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

// 始点と終点からベクトルを作成
VECTOR CMyMath::VecCreate(VECTOR start, VECTOR end)
{
	VECTOR result;

	// ①ベクトルは「終点 - 始点」で求められる
	result.x = end.x - start.x;
	result.y = end.y - start.y;
	result.z = end.z - start.z;

	return result;
}

// ベクトルの足し算
VECTOR CMyMath::VecAdd(VECTOR vec1, VECTOR vec2)
{
	VECTOR result;

	// ①各成分を足し算する
	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;

	return result;
}

// ベクトルの長さ
float CMyMath::VecLong(VECTOR vec)
{
	// ①ピタゴラスの定理からベクトルの長さを求める
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}


// ベクトルの正規化
VECTOR CMyMath::VecNormalize(VECTOR vec)
{
	VECTOR result;

	// ①ベクトルの長さを求める
	float vec_long = VecLong(vec);

	// ②各成分を長さで割ることにより正規化する
	result.x = vec.x / vec_long;
	result.y = vec.y / vec_long;
	result.z = vec.z / vec_long;

	return result;
}

// ベクトルのスカラー倍
VECTOR CMyMath::VecScale(VECTOR vec, float scale)
{
	VECTOR result;

	// ①各成分をスカラー倍する
	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;

	return result;
}

// ベクトルの内積
float CMyMath::VecDot(VECTOR vec1, VECTOR vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

// ベクトルの向きをラジアン値で取得
float CMyMath::VecDir(VECTOR vec)
{
	return atan2f(vec.y, vec.x);
}

//単位行列を取得
MATRIX CMyMath::GetIdentityMatrix()
{
	MATRIX result = { 0.0f };

	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	return result;
}

//平行移動行列を取得
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

//拡縮行列を取得
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

//X軸回転行列を取得
MATRIX CMyMath::GetPitchMatrix(float rot)
{
	MATRIX result = GetIdentityMatrix();
	result.m[1][1] = cosf(rot);
	result.m[1][2] = -sinf(rot);
	result.m[2][1] = sinf(rot);
	result.m[2][2] = cosf(rot);

	return result;
}

//Y軸回転行列を取得
MATRIX CMyMath::GetYawMatrix(float rot)
{
	MATRIX result = GetIdentityMatrix();
	result.m[0][0] = cosf(rot);
	result.m[0][2] = sinf(rot);
	result.m[2][0] = -sinf(rot);
	result.m[2][2] = cosf(rot);

	return result;
}

//Z軸回転行列を取得
MATRIX CMyMath::GetRollMatrix(float rot)
{
	MATRIX result = GetIdentityMatrix();
	result.m[0][0] = cosf(rot);
	result.m[0][1] = -sinf(rot);
	result.m[1][0] = sinf(rot);
	result.m[1][1] = cosf(rot);

	return result;
}

//行列の足し算
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

//行列の引き算
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

//行列をスカラー倍する
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

//2つの行列の掛け算
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

//行列×ベクトル
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

//行列転置
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