#include "MyMath.h"
#include <math.h>

VECTOR MyMath::VecCreate(VECTOR vPosA, VECTOR vPosB)
{
	VECTOR result;
	result.x = vPosB.x - vPosA.x;
	result.y = vPosB.y - vPosA.y;
	result.z = vPosB.z - vPosA.z;
	return result;
}

float MyMath::VecLong(VECTOR Vec)
{
	float result;
	result = sqrtf(Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z);
	return result;
}

VECTOR MyMath::VecAdd(VECTOR vecA, VECTOR vecB)
{
	VECTOR result;
	result.x = vecA.x + vecB.x;
	result.y = vecA.y + vecB.y;
	result.z = vecA.z + vecB.z;

	return result;
}

VECTOR MyMath::VecSubtract(VECTOR vecA, VECTOR vecB)
{
	VECTOR result;
	result.x = vecA.x - vecB.x;
	result.y = vecA.y - vecB.y;
	result.z = vecA.z - vecB.z;

	return result;

}

VECTOR MyMath::VecScale(VECTOR vec, float scale)
{
	VECTOR result;
	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;

	return result;
}

float MyMath::VecDot(VECTOR vecA, VECTOR vecB)
{
	float result;
	result = vecA.x * vecB.x + vecA.y * vecB.y + vecA.z * vecB.z;
	return result;
}

VECTOR MyMath::VecCross(VECTOR vecA, VECTOR vecB)
{
	VECTOR result;
	result.x = vecA.y * vecB.z - vecA.z * vecB.y;
	result.y = vecA.z * vecB.x - vecA.x * vecB.z;
	result.z = vecA.x * vecB.y - vecA.y * vecB.x;
	return result;
}

VECTOR MyMath::VecNormalize(VECTOR vec)
{
	float size;
	VECTOR result;
	size = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	size = sqrtf(size);
	result.x = vec.x / size;
	result.y = vec.y / size;
	result.z = vec.z / size;

	return result;
}

VECTOR MyMath::GetPolygonNormalVec(VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);
	VECTOR vecABAC = VecCross(vecAB, vecAC);
	return VecNormalize(vecABAC);
}

MATRIX MyMath::GetldentityMatrix()
{
	MATRIX result = { 0 };
	for(int i = 0; i < 4; i++)	{
		for(int j = 0; j < 4; j++){
			if(i == j){
				result.m[i][j] = 1;
			}
			else{
				result.m[i][j] = 0;
			}
		}
	}

	return result;
}

//平行移動行列の取得
MATRIX MyMath::GetTranslateMatrix(float x, float y, float z)
{
	MATRIX result = GetldentityMatrix();
	result.m[0][3] = x;
	result.m[1][3] = y;
	result.m[2][3] = z;

	return result;
}

//平行移動行列の取得
MATRIX MyMath::GetTranslateMatrix(VECTOR trans)
{
	MATRIX result = GetldentityMatrix();
	result.m[0][3] = trans.x;
	result.m[1][3] = trans.y;
	result.m[2][3] = trans.z;

	return result;
}


//拡縮行列の取得
MATRIX MyMath::GetScaleMatrix(float x, float y, float z)
{
	MATRIX result = GetldentityMatrix();
	result.m[0][0] = x;
	result.m[1][1] = y;
	result.m[2][2] = z;

	return result;
}

//X軸回転行列の取得
MATRIX MyMath::GetPitchMatrix(float rot)
{
	MATRIX result = GetldentityMatrix();
	result.m[1][1] = cosf(rot);
	result.m[1][2] = -sinf(rot);
	result.m[2][1] = sinf(rot);
	result.m[2][2] = cosf(rot);

	return result;
}

//Y軸回転行列の取得
MATRIX MyMath::GetYawMatrix(float rot)
{
	MATRIX result = GetldentityMatrix();
	result.m[0][0] = cosf(rot);
	result.m[0][2] = sinf(rot);
	result.m[2][0] = -sinf(rot);
	result.m[2][2] = cosf(rot);

	return result;
}

//Z軸回転行列の取得
MATRIX MyMath::GetRollMatrix(float rot)
{
	MATRIX result = GetldentityMatrix();
	result.m[0][0] = cosf(rot);
	result.m[0][1] = -sinf(rot);
	result.m[1][0] = sinf(rot);
	result.m[1][1] = cosf(rot);

	return result;
}


MATRIX MyMath::MatAdd(MATRIX matA, MATRIX matB)
{
	MATRIX result = { 0 };
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			result.m[i][j] = matA.m[i][j] + matB.m[i][j];
		}
	}

	return result;
}

MATRIX MyMath::MatMult(MATRIX matA, MATRIX matB)
{
	MATRIX result = { 0 };
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				result.m[i][j] += (matA.m[i][k] * matB.m[k][j]);
			}
		}
	}

	return result;
}

MATRIX MyMath::MatScale(MATRIX mat, float scale)
{
	MATRIX result = { 0 };
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			result.m[i][j] = mat.m[i][j] * scale;
		}
	}

	return result;
}

VECTOR MyMath::MatTransform(MATRIX mat, VECTOR vec)
{
	float work[4] = { 0 };
	float result_buf[4] = { 0 };
	VECTOR result_vec;
	work[0] = vec.x;
	work[1] = vec.y;
	work[2] = vec.z;
	work[3] = 1;
	for(int i = 0; i < 4; i++){
		for(int k = 0; k < 4; k++){
			result_buf[i] += (mat.m[i][k] * work[k]);
		}
	}

	result_vec.x = result_buf[0];
	result_vec.y = result_buf[1];
	result_vec.z = result_buf[2];

	return result_vec;
}

MATRIX MyMath::MatTranspose(MATRIX mat)
{
	MATRIX result = { 0 };
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[x][y] = mat.m[y][x];
		}
	}

	return result;
}

float MyMath::GetTriangleHeightXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// 辺に沿ったベクトルABとACを計算
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);
	// 面法線を計算
	VECTOR vecNorm = VecCross(vecAB, vecAC);
	vecNorm = VecNormalize(vecNorm);
	// 平面の方程式から高さ（Y座標を計算）
	float z = (-vecNorm.x * (point.x - vertexA.x) - vecNorm.y * (point.y - vertexA.y) + vecNorm.z * vertexA.z) / vecNorm.z;

	return z;
}

float MyMath::GetTriangleHeightXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// 辺に沿ったベクトルABとACを計算
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);
	// 面法線を計算
	VECTOR vecNorm = VecCross(vecAB, vecAC);
	vecNorm = VecNormalize(vecNorm);
	// 平面の方程式から高さ（Y座標を計算）
	float y = (-vecNorm.x * (point.x - vertexA.x) - vecNorm.z * (point.z - vertexA.z) + vecNorm.y * vertexA.y) / vecNorm.y;

	return y;
}

float MyMath::GetTriangleHeightYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// 辺に沿ったベクトルABとACを計算
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);
	// 面法線を計算
	VECTOR vecNorm = VecCross(vecAB, vecAC);
	vecNorm = VecNormalize(vecNorm);
	// 平面の方程式から高さ（Y座標を計算）
	float x = (-vecNorm.y * (point.y - vertexA.y) - vecNorm.z * (point.z - vertexA.z) + vecNorm.x * vertexA.x) / vecNorm.x;

	return x;
}


float MyMath::Abs(float val) 
{
	if (val < 0.0f) {
		return -val;
	}
	return val;
}

float MyMath::GetDistance(VECTOR posA, VECTOR posB)
{
	VECTOR vec = VecCreate(posA, posB);
	return VecLong(vec);
}
