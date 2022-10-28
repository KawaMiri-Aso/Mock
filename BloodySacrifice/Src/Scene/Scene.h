#pragma once

class CScene
{

public:
	CScene();
	virtual ~CScene();

	//初期化
	virtual void Init() = 0;

	//ロード
	virtual void Load() = 0;

	//ロード完了
	virtual void OnLoadEnd() = 0;

	//毎フレーム呼ぶ処理
	virtual void Step() = 0;

	//描画
	virtual void Draw() = 0;

	//後処理
	virtual void Fin() = 0;
};
