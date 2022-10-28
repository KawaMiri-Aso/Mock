
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

	static void CreateInstance() { if (!instance_)instance_ = new CPlayerManager; }
	static CPlayerManager* GetInstance(){return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

	//初期化
	void Init();
	//ロード
	void Load();
	//ステップ
	void Step();
	//描画
	void Draw();
	//削除
	void Delete();
	//後処理();
	void Fin();

	//プレイヤークラスを取得
	CPlayer* GetPlayer()const { return m_player; }

private:
	static CPlayerManager* instance_;
	CPlayer* m_player;	//プレイヤークラス

};
