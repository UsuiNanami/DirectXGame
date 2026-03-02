#pragma once
#include "KamataEngine.h"

//====================================
// ゲームシーン
//====================================
class GameScene {
public:
	GameScene() = default; // コンストクラタ
	~GameScene();          // デストラクタ

	// --- 初期化 ---
	void Initialize();

	// --- 更新処理 ---
	void Update();

	// --- 描画処理 ---
	void Draw();
};
