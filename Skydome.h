#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;
class Skydome {
public:

	// --- デストラクタ ---
	Skydome() = default;
	~Skydome();

	// --- 初期化 ---
	void Initialize();

	// --- 更新処理 ---
	void Update();

	// --- 描画処理 ---
	void Draw(const Camera& camera);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

};
