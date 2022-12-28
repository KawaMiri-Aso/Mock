
//PlayScene.h
//プレイシーン

#pragma once

#include "DxLib.h"
#include "Scene.h"
#include "../Player/PlayerManager.h"
#include "../Enemy/EnemyManager.h"

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
	void InitTotem();

	void LoadPlayer();
	void LoadMap();
	void LoadEnemy();
	void LoadCamera();
	void LoadStoneTrap();
	void LoadTotem();

	void StepPlayState();

	//プレイヤーと敵の当たり判定
	void HitCheckEnemyToPlayer(CPlayer* player, CEnemy* enemy);
	//プレイヤーの攻撃と敵の当たり判定
	void HitCheckEnemyToPlayerAttack(CPlayer* player, CEnemy* enemy);

private:

	PlayState state_;

};
