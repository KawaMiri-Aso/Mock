
//PlayerManager.h
//プレイヤー管理
//CPlayerへのアクセスは必ずCPlayerManagerを経由

#pragma once

#include "Player.h"

class CPlayerManager
{
public:

	CPlayerManager();
	~CPlayerManager();

	//初期化
	void Init();

	//ステップ
	void Step();

	//ロード
	void Load();

	//描画
	void Draw();

	//削除
	void Delete();

	//後処理();
	void Fin();

	//プレイヤークラスを取得
	CPlayer* GetPlayer(){ return &m_player; }

private:

	CPlayer	m_player;	//プレイヤークラス

};

//PlayerManager.hをインクルードした先で使えるように
extern CPlayerManager g_player_manager;
