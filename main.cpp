#include "GameScene.h"
#include "KamataEngine.h"
#include <Windows.h>

using namespace KamataEngine; // KamataEngineを略して書けるようになる

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	//====================================
	// 初期化処理
	//====================================
	KamataEngine::Initialize(L"LE2C_03_ウスイ_ナナミ_05_01");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance(); // DirectXCommonインスタンスの取得

	GameScene* gameScene = new GameScene(); // ゲームシーンのインスタンス生成

	gameScene->Initialize(); // ゲームシーンの初期化

	//====================================
	// メインループ
	//====================================
	while (true) {
		// --- エンジンの更新 ---
		if (KamataEngine::Update()) {
			break;
		}

		// --- ゲームシーンの更新 ---
		gameScene->Update();

		// --- 描画開始 ---
		dxCommon->PreDraw();

		// --- ゲームシーンの描画 ---
		gameScene->Draw();

		// --- 描画終了 ---
		dxCommon->PostDraw();
	}

	//====================================
	// 解放処理
	//====================================
	// --- ゲームシーンの解放 ---
	delete gameScene;

	// --- nullptrの代入 ---
	gameScene = nullptr;

	//====================================
	// 終了処理
	//====================================
	KamataEngine::Finalize();

	return 0;
}
