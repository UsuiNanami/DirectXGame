#pragma once
#include "KamataEngine.h"
#include "Skydome.h"
#include <vector>

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
	uint32_t textureHandle_ = 1;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// 3Dモデルデータ
	KamataEngine::Model* modelBlock_ = nullptr;

	// スカイドーム
	Skydome* modelskydome_ = nullptr;

	// --- カメラ ---
	KamataEngine::Camera camera_;

	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// デバッグカメラ有効フラグ
	bool isDebugCameraActive_ = false;

	// ワールドトランスフォームの配列
	/* std::vector<KamataEngine::WorldTransform*> worldTransformBlocks_;  横一列（1次元）*/

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_; // 縦横（2次元）
};