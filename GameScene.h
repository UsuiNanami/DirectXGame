#pragma once
#include "KamataEngine.h"
#include "Player.h"

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

private: // privateはGameScene内でしか使わない
// --- テクスチャハンドル  ---
uint32_t textureHandle_ = 0;
// スプライト
KamataEngine::Sprite* sprite_ = nullptr;

// 3Dモデルデータ
KamataEngine::Model* model_ = nullptr;

// --- カメラ ---
KamataEngine::Camera camera_;

// 自キャラをゲームシーンに持たせる
Player* player_ = nullptr;


};

