#ifndef __MYMATH_H__
#define __MYMATH_H__

#include "DxLib.h"

class CMyMath
{
public:
	static float GetDistance(float x1, float y1, float x2, float y2);
	static float RadianNormalize(float rad);
	static VECTOR VecCreate(VECTOR start, VECTOR end);
	static VECTOR VecAdd(VECTOR vec1, VECTOR vec2);
	static float VecLong(VECTOR vec);
	static VECTOR VecNormalize(VECTOR vec);
	static VECTOR VecScale(VECTOR vec, float scale);
	static float VecDot(VECTOR vec1, VECTOR vec2);
	static VECTOR VecCross(VECTOR vec1, VECTOR vec2);
	static float VecDir(VECTOR vec);

	static MATRIX GetIdentityMatrix();
	//•½sˆÚ“®s—ñ‚ğæ“¾
	static MATRIX GetTranslateMatrix(float x, float y, float z);
	static MATRIX GetTranslateMatrix(VECTOR translation);
	//Šgks—ñ‚ğæ“¾
	static MATRIX GetScaleMatrix(float x, float y, float z);
	static MATRIX GetScaleMatrix(VECTOR scale);
	//X²‰ñ“]s—ñ‚ğæ“¾
	static MATRIX GetPitchMatrix(float rot);
	//Y²‰ñ“]s—ñ‚ğæ“¾
	static MATRIX GetYawMatrix(float rot);
	//Z²‰ñ“]s—ñ‚ğæ“¾
	static MATRIX GetRollMatrix(float rot);
	static MATRIX MatAdd(MATRIX matA, MATRIX matB);
	static MATRIX MatSub(MATRIX matA, MATRIX matB);
	static MATRIX MatScale(MATRIX mat, float scale);
	static MATRIX MatMult(MATRIX matA, MATRIX matB);
	static VECTOR MatTransform(MATRIX mat, VECTOR pos);
	static MATRIX MatTranspse(MATRIX mat);

private:

};

#endif
