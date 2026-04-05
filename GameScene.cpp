#include "GameScene.h"
#include "MyMath.h"
#include "Skydome.h"

//====================================
// デストラクタ
//====================================
GameScene::~GameScene() {
	// 3Dモデルの解放
	delete modelBlock_;

	delete modelskydome_;

	// デバッグカメラの解放
	delete debugCamera_;

	// 2重ループで1つずつ delete する
	for (uint32_t i = 0; i < worldTransformBlocks_.size(); i++) {        // 行のループ
		for (uint32_t j = 0; j < worldTransformBlocks_[i].size(); j++) { // 列のループ

			// ブロック（WorldTransform）のメモリを解放
			delete worldTransformBlocks_[i][j];
		}
		// 内側の vector（列）を空にする
		worldTransformBlocks_[i].clear();
	}
	// 外側の vector（行）を空にする
	worldTransformBlocks_.clear();
}

//====================================
// 初期化処理
//====================================
void GameScene::Initialize() {

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("cube/cube.jpg");

	// 3Dモデルデータの生成
	modelBlock_ = Model::Create();

	// スカイドームの生成
	modelskydome_ = new Skydome();
	modelskydome_->Initialize();

	// カメラの初期化
	camera_.Initialize();

	// farZ (カメラから見て、どこまで遠くを描画するかという距離）
	camera_.farZ = 1000.0f;

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 要素数
	const uint32_t kNumBlockVertical = 10;   // Verticalは垂直方向の意味　（垂直方向に並べるブロックの数）
	const uint32_t kNumBlockHorizontal = 20; // Horizontalは横方向の意味　（横方向に並べるブロックの数）

	// ブロック１個分の横幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	// 要素数を変更する
	worldTransformBlocks_.resize(kNumBlockVertical); // まず縦方向の要素数を変更する

	for (uint32_t i = 0; i < kNumBlockVertical; i++) { // 縦方向の要素数を変更した後、横方向の要素数を変更する
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			// 条件に合う場所にブロックを生成する
			if ((i + j) % 2 == 0) {                                             // iとjの和が偶数のときだけブロックを生成する
				worldTransformBlocks_[i][j] = new WorldTransform();             // 中身を作る
				worldTransformBlocks_[i][j]->Initialize();                      // 初期化する
				worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;  // 横方向に並べる
				worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i; // 縦方向に並べる
				worldTransformBlocks_[i][j]->translation_.z = 0.0f;
			}
			else {
				// 条件に合わない場所はnullptrにする
				worldTransformBlocks_[i][j] = nullptr;
			}
		}
	}
}

//====================================
// 更新処理
//====================================
void GameScene::Update() {
	// 縦（行）のループ
	for (uint32_t i = 0; i < worldTransformBlocks_.size(); i++) {
		// 横（列）のループ
		for (uint32_t j = 0; j < worldTransformBlocks_[i].size(); j++) {

			// worldTransformBlocks_[i][j] に対して処理を行う
			if (worldTransformBlocks_[i][j] != nullptr) { // nullptrじゃないときだけ処理する

				worldTransformBlocks_[i][j]->matWorld_ = MakeAffineMatrix(
					worldTransformBlocks_[i][j]->scale_, 
					worldTransformBlocks_[i][j]->rotation_,
					worldTransformBlocks_[i][j]->translation_
				);

				worldTransformBlocks_[i][j]->TransferMatrix();
			}
		}
	}

	// デバッグカメラの更新
	debugCamera_->Update();

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
	modelskydome_->Update();

}

//====================================
// 描画処理
//====================================
void GameScene::Draw() {
	// モデル描画前処理
	KamataEngine::Model::PreDraw();

	// スカイドームの描画
	
	if (modelskydome_) {
		modelskydome_->Draw(camera_);
	}

	// 縦（行）のループ
	for (uint32_t i = 0; i < worldTransformBlocks_.size(); i++) {
		// 横（列）のループ
		for (uint32_t j = 0; j < worldTransformBlocks_[i].size(); j++) {

			// [i][j] のブロックを描画する
			if (worldTransformBlocks_[i][j] != nullptr) { // nullptrでないときだけ描画する
				modelBlock_->Draw(*worldTransformBlocks_[i][j], camera_, textureHandle_);
			}
		}
	}

	// モデル描画後処理
	KamataEngine::Model::PostDraw();
}