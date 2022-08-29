
//PlayCamera.h
//プレイシーンでのカメラ

#pragma once

#include "DxLib.h"

class CPlayCamera
{

public:
	CPlayCamera();	//コンストラクタ
	~CPlayCamera();	//デストラクタ

	//初期化
	void Init();
	void Init(VECTOR pos, VECTOR look, VECTOR up);

	//毎フレーム呼ぶ処理（操作）
	void Step();

	//カメラ情報の更新処理
	void Update();

	//後処理
	void Fin();

	//視点を取得
	VECTOR GetPos(){ return m_vPos; }

	//注視点を取得
	VECTOR GetLook(){ return m_vLook; }

private:
	
	VECTOR	m_vPos;		//視点
	VECTOR	m_vLook;	//注視点
	VECTOR	m_vUp;		//アップベクトル

};

