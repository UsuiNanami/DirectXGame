#include "GameScene.h"

using namespace KamataEngine;

//====================================
// デストラクタ
//====================================
GameScene::~GameScene() {}

//====================================
// 初期化処理
//====================================
void GameScene::Initialize() {}

//====================================
// 更新処理
//====================================
void GameScene::Update() {}

	#ifdef _DEBUG // デバッグビルドのときだけ!!
	// デバッグカメラの有効フラグを切り替える
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif

	// カメラの処理
	if (isDebugCameraActive_) {
		// デバックカメラの更新
		debugCamera_->Update();

		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;

		// ビュープロジェクションの転送
		camera_.TransferMatrix();
	
	} else {

		camera_.UpdateMatrix();
	
	}

}

//====================================
// 描画処理
//====================================
void GameScene::Draw() {}