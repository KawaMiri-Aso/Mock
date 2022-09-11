
//PlayScene.h
//プレイシーン

#pragma once

#include "DxLib.h"
#include "Scene.h"

class CPlayScene : public CScene
{
private:
	enum PlayState
	{
		PLAY_STATE_NONE,
		PLAY_STATE_FADE,
	};

public:
	CPlayScene();
	virtual ~CPlayScene();

	////初期化
	//void Init();

	////ロード
	//void Load();

	////毎フレーム呼ぶ処理
	//void Step();

	////描画
	//void Draw();

	////後処理
	//void Fin();

	//初期化
	void Init()override;
	//ロード
	void Load();
	//ロード完了
	void OnLoadEnd()override;
	//毎フレーム呼ぶ処理
	void Step()override;
	//描画
	void Draw()override;
	//後処理
	void Fin()override;

private:
	void InitPlayer();
	void InitMap();
	void InitEnemy();
	void InitCamera();
	void InitStoneTrap();

	void LoadPlayer();
	void LoadMap();
	void LoadEnemy();
	void LoadCamera();
	void LoadStoneTrap();

	void StepPlayState();

private:

	//天球
	int m_sky_handle;
	PlayState state_;

};
