#include "GameScene.h"

using namespace KamataEngine;

//====================================
// デストラクタ
//====================================
GameScene::~GameScene() {
	// --- 2D メインゲームの解放処理 ---
	delete sprite_;

	// --- 3D メインゲームの解放処理 ---
	delete model_;

	// --- デバックカメラの解放処理 ---
	delete debugCamera_;
}

//====================================
// 初期化処理
//====================================
void GameScene::Initialize() {
	// --- 2D メインゲームの初期化処理 ---
	// スプライトの読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");
	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	// --- 3D メインゲームの初期化処理 ---
	// 3Dモデルのテクスチャ読み込み
	textureHandle2_ = TextureManager::Load("cube/cube.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// カメラの初期化
	camera_.Initialize();

	// --- 音声の初期化処理 ---
	soundDataHandle_ = Audio::GetInstance()->LoadWave("fanfare.wav");
	// 音声を再生する
	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);

	// --- デバッグカメラの初期化 --- (画面横幅,画面縦幅)
	debugCamera_ = new DebugCamera(1280, 720);

	// ---　ライン表示の初期化　---
	PrimitiveDrawer::GetInstance()->SetCamera(&debugCamera_->GetCamera());

	// --- 軸方向表示 ---
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示のターゲットカメラをデバックカメラにする
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());
}

//====================================
// 更新処理
//====================================
void GameScene::Update() {
	// --- 2Dモデルの更新 ---
	// ~~~ スプライトの移動 ~~~
	// スプライトの現在の座標を取得する
	Vector2 position = sprite_->GetPosition();
	Vector2 speed_ = {2.0f, 1.0f};

	// 座標を{2,1}移動する   スプライトの移動
	position.x += speed_.x;
	position.y += speed_.y;
	// 移動後の座標をスプライトに反映する
	sprite_->SetPosition(position);

	// --- 音声のループ再生と停止 ---
	// Sを押した瞬間
	if (Input::GetInstance()->TriggerKey(DIK_S)) {
		// 音声を停止する
		Audio::GetInstance()->StopWave(voiceHandle_); // StopWave停止
	}
	// Pを押した瞬間
	if (Input::GetInstance()->TriggerKey(DIK_P)) {
		// 音声を再生する
		voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_); // PlayWave再生
	}

	/// --- デバックカメラの更新 ---
	debugCamera_->Update();

	// --- デバックウィンドウ ---
	ImGui::Begin("Debug1");
	ImGui::Text("Hello, ImGui!");
	// float3入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	// float3スライダー
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	// デモウィンドウの表示
	ImGui::ShowDemoWindow();

	ImGui::End();
}

//====================================
// 描画処理
//====================================
void GameScene::Draw() {
	// --- 2Dモデルの描画 ---
	// スプライト描画前処理
	Sprite::PreDraw();

	// スプライト描画 PreDrawとPostDrawの間に記述する
	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

	// --- 3Dモデルの描画 ---
	// モデル描画の前処理
	Model::PreDraw();

	/*// モデル描画 PreDrawとPostDrawの間に記述する　（座標、カメラ、テクスチャを渡す）
	model_->Draw(worldTransform_, camera_, textureHandle2_);*/
	// デバックカメラを使ってモデルを描画する
	model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle2_);

	// モデル描画後処理
	Model::PostDraw();

	// --- ラインの描画 ---
	// X軸（赤）                                 // 始点     // 終点    // 色(RGBA)
	PrimitiveDrawer::GetInstance()->DrawLine3d({-5, 0, 0}, {5, 0, 0}, {1, 0, 0, 1});

	// Y軸（緑）
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, -5, 0}, {0, 5, 0}, {0, 1, 0, 1});

	// Z軸（青）
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, -5}, {0, 0, 5}, {0, 0, 1, 1});
}
