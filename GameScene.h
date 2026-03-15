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

private: // privateはGameScene内でしか使わない
	// --- テクスチャハンドル 2D ---
	uint32_t textureHandle_ = 0;
	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;


	// --- テクスチャハンドル　3D ---
	uint32_t textureHandle2_ = 0;
	// スプライト
	KamataEngine::Sprite* sprite2_ = nullptr;
	// モデル本体
	KamataEngine::Model* model_ = nullptr;
	// ワールドトランスフォーム　　モデルの描画にはワールドトランスフォームとカメラが必要！
	KamataEngine::WorldTransform worldTransform_;
	// カメラ
	KamataEngine::Camera camera_;


	// --- 音声データ ---
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;


	// --- デバッグテキスト表示用 ---
	KamataEngine::DebugText* debugText_ = nullptr;
	// ImGuiで値を入力する変数
	float inputFloat3[3] = {0, 0, 0};


	// --- デバッグカメラ ---
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
};
