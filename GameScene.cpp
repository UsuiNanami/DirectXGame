#include "GameScene.h"

using namespace KamataEngine;

//====================================
// デストラクタ
//====================================
GameScene::~GameScene() {

	// 3Dモデルの解放
	delete model_;

	// 自キャラの解放
	delete player_;
	
}

//====================================
// 初期化処理
//====================================
void GameScene::Initialize() {
	// スプライトの読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// 3Dモデルデータの生成
	model_ = Model::Create();

	// カメラの初期化
	camera_.Initialize();

	// 自キャラの生成
	player_ = new Player();

	// 自キャラの初期化	
	player_->Initialize(model_, textureHandle_, &camera_);
}

//====================================
// 更新処理
//====================================
void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
}

//====================================
// 描画処理
//====================================
void GameScene::Draw() {
	// モデル描画の前処理
	KamataEngine::Model::PreDraw();
	// 自キャラの描画関数を呼び出す
	player_->Draw();
	// モデル描画後処理
	KamataEngine::Model::PostDraw();
}
