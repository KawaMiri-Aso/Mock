
//PlayScene.h
//プレイシーン

#pragma once

#include "DxLib.h"

class CPlayScene
{

public:
	CPlayScene();
	~CPlayScene();

	//初期化
	void Init();

	//毎フレーム呼ぶ処理
	void Step();

	//描画
	void Draw();

	//後処理
	void Fin();

private:

	//天球
	int m_sky_handle;

};
