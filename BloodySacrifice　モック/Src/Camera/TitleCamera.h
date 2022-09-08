
//TitleCamera.h
//タイトルシーンでのカメラ

#pragma once

#include "DxLib.h"

class CTitleCamera
{

public:
	CTitleCamera();	//コンストラクタ
	~CTitleCamera();	//デストラクタ

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
	VECTOR GetPos(){ return pos_; }

	//注視点を取得
	VECTOR GetLook(){ return look_; }

private:
	
	VECTOR	pos_;		//視点
	VECTOR	look_;		//注視点
	VECTOR	up_;		//アップベクトル

};

