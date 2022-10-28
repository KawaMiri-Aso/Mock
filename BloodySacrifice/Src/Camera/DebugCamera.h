
//DebugCamera.h
//常時起動できるデバッグカメラ

#pragma once

#include "DxLib.h"

class CDebugCamera
{

public:
	CDebugCamera();
	~CDebugCamera();

	//初期化
	void Init();
	void Init(VECTOR pos, VECTOR look, VECTOR up);

	//毎フレーム呼ぶ処理（操作）
	void Step();

	//描画
	void Draw();

	//カメラ情報の更新処理
	void Update();

	//後処理
	void Fin();

	//視点を設定
	void SetPos(VECTOR pos){ pos_ = pos; }
	
	//注視点を設定
	void SetLook(VECTOR look){ look_ = look; }

private:

	VECTOR	pos_;		//視点
	VECTOR	look_;	//注視点
	VECTOR	up_;		//アップベクトル
};