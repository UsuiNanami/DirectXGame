#pragma once
#include "KamataEngine.h"

class Player {
public:
	Player() = default;
	~Player() = default;

	// 初期化: 引数の型をエンジンの仕様に合わせます
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);

	void Update();
	void Draw();

private:
	// メンバ変数（末尾にアンダースコアをつけて区別）
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	KamataEngine::Camera* camera_ = nullptr;
};