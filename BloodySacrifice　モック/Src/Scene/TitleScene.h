
//TitleScene.h
//タイトルシーン

#pragma once

#include "DxLib.h"

class CTitleScene
{

public:
	CTitleScene();
	~CTitleScene();

	//初期化
	void Init();

	//毎フレーム呼ぶ処理
	void Step();

	//描画
	void Draw();

	//後処理
	void Fin();
};
