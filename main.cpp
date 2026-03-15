#include "GameScene.h"
#include "KamataEngine.h"
#include <Windows.h>

using namespace KamataEngine; // KamataEngineを略して書けるようになる

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	//====================================
	// 初期化処理
	//====================================
	KamataEngine::Initialize(L"LE2C_03_ウスイ_ナナミ_04_03");

	ImGuiManager* imguiManager = ImGuiManager::GetInstance(); // ImGuiManagerインスタンスの取得

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

		// --- ImGui受付開始 ---
		imguiManager->Begin();

		// --- ゲームシーンの更新 ---
		gameScene->Update();


		// --- ImGui受付終了 ---
		imguiManager->End();

		// --- 描画開始 ---
		dxCommon->PreDraw();

		// --- ゲームシーンの描画 ---
		gameScene->Draw();

		// --- 軸表示の描画 ---
		AxisIndicator::GetInstance()->Draw();

		// --- ImGui描画 ---
		imguiManager->Draw();

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
