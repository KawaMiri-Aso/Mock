
//PlayerManager.cpp
//プレイヤー管理
//CPlayerへのアクセスは必ずCPlayerManagerを経由
#pragma once

#include "PlayerManager.h"

CPlayerManager* CPlayerManager::instance_ = nullptr;

CPlayerManager::CPlayerManager()
{
	m_player = nullptr;
}

CPlayerManager::~CPlayerManager()
{
	Fin();
}

//初期化
void CPlayerManager::Init()
{
	//プレイヤーの初期化を呼ぶ
	m_player = new CPlayer;
	m_player->Init(VGet(-41.0f, 1.0f, 41.0f));
}

//ロード
void CPlayerManager::Load()
{
	m_player->Load();
}

//ステップ
void CPlayerManager::Step()
{
	//プレイヤーのステップ
	m_player->Step();
}

//描画
void CPlayerManager::Draw()
{
	//プレイヤーの描画
	m_player->Draw();
}

//削除
void CPlayerManager::Delete()
{
	//プレイヤー削除
	m_player->Delete();
}

//後処理();
void CPlayerManager::Fin()
{
	//プレイヤーの後処理を呼ぶ
	m_player->Fin();
}
