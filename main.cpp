#include <Novice.h>
#include "Constant.h"
#include "./Class/Object/Player/Player.h"
#include "./Class/Map/Map.h"

const char kWindowTitle[] = "LC1C_20_フクダソウワ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kScreenWidth, kScreenHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	/*---------------
	    変数を作る
	---------------*/

	// プレイヤー
	Player* player = new Player();

	// ステージ
	Map* stage1 = new Map("./TextFiles/Stage/stage1.csv");

	int ghWhite = Novice::LoadTexture("./NoviceResources/white1x1.png");


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// 操作する
		player->Operation(keys, preKeys);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// プレイヤー
		player->Draw(ghWhite);

		// ステージ
		stage1->Draw(ghWhite);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete player;

	delete stage1;


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
