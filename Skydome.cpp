#include "Skydome.h"
#include "MyMath.h"

//====================================
// デストラクタ
//====================================
Skydome::~Skydome() {
	delete model_;
}

//====================================
// 初期化処理
//====================================
void Skydome::Initialize() {
	// スライドの通り、skydome.obj を読み込む
	model_ = Model::CreateFromOBJ("SkyDome");

	// ワールド変換の初期化
	worldTransform_.Initialize();

	// 天球は巨大である必要があるので、スケールを大きくする
	worldTransform_.scale_ = {150.0f, 150.0f, 150.0f};
}

//====================================
// 更新処理
//====================================
void Skydome::Update() {
	worldTransform_.matWorld_ = MakeAffineMatrix(
		worldTransform_.scale_,
		worldTransform_.rotation_,
		worldTransform_.translation_
	);
	worldTransform_.TransferMatrix();
}

//====================================
// 描画処理
//====================================
void Skydome::Draw(const Camera& camera) {
	model_->Draw(worldTransform_, camera);
}