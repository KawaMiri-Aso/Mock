
//PlayerManager.cpp
//プレイヤー管理
//CPlayerへのアクセスは必ずCPlayerManagerを経由

#include "PlayerManager.h"

//CPlayerManagerの実体宣言
CPlayerManager g_player_manager;

CPlayerManager::CPlayerManager()
{
	//CPlayerのコンストラクタは自動で呼ばれます
}

CPlayerManager::~CPlayerManager()
{
	//CPlayerのデストラクタは自動で呼ばれます
}

//初期化
void CPlayerManager::Init()
{
	//プレイヤーの初期化を呼ぶ
	m_player.Init(VGet(0.0f, 1.0f, 0.0f));
}

//ステップ
void CPlayerManager::Step()
{
	//プレイヤーのステップ
	m_player.Step();
}

//描画
void CPlayerManager::Draw()
{
	//プレイヤーの描画
	m_player.Draw();
}

//削除
void CPlayerManager::Delete()
{
	//プレイヤー削除
	m_player.Delete();
}

//後処理();
void CPlayerManager::Fin()
{
	//プレイヤーの後処理を呼ぶ
	m_player.Fin();
}
