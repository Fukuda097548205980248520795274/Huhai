#include <Novice.h>
#include "Constant.h"
#include "./Class/Object/Player/Player.h"
#include "./Class/Map/Map.h"
#include "./Class/Object/Plastic/Plastic.h"
#include "./Class/Object/Treasure/Treasure.h"

const char kWindowTitle[] = "LC1C_20_フクダソウワ_タイトル";

int Plastic::countId;
int Treasure::countId;

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

	// プラスチック
	Plastic* plastic[kTileNum];

	// 宝
	Treasure* treasure[kTileNum];

	for (int i = 0; i < kTileNum; i++)
	{
		plastic[i] = new Plastic();
		treasure[i] = new Treasure();
	}

	// マップ
	Map* map = new Map("./TextFiles/Stage/stage1.csv");

	// オブジェクトを置き換える
	for (int row = 0; row < kMapChipRow; row++)
	{
		for (int column = 0; column < kMapChipColumn; column++)
		{
			switch (map->map_[row][column])
			{
			case TILE_PLASTIC:
				// プラスチック

				for (int i = 0; i < kTileNum; i++)
				{
					if (plastic[i]->id_ == 0)
					{
						plastic[i]->Arrangement(static_cast<float>(column * kTileSize) + plastic[i]->shape_.scale.x,
							static_cast<float>(row * kTileSize) + plastic[i]->shape_.scale.y);

						break;
					}
				}

				map->map_[row][column] = TILE_NOTHING;

				break;

			case TILE_TREASURE:
				// 宝

				for (int i = 0; i < kTileNum; i++)
				{
					if (treasure[i]->id_ == 0)
					{
						treasure[i]->Arrangement(static_cast<float>(column * kTileSize) + treasure[i]->shape_.scale.x,
							static_cast<float>(row * kTileSize) + treasure[i]->shape_.scale.y);

						break;
					}
				}

				map->map_[row][column] = TILE_NOTHING;

				break;
			}
		}
	}

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
		player->Operation(keys, preKeys , map);

		// ブロックの動き
		for (int i = 0; i < kTileNum; i++)
		{
			plastic[i]->Move(map , player);
			treasure[i]->Move(map , player);
		}

		for (int i = 0; i < kTileNum; i++)
		{
			for (int j = 0; j < kTileNum; j++)
			{
				if (plastic[i]->isArrival_ && plastic[j]->isArrival_)
				{
					if (plastic[i]->vel_.x > 0.0f)
					{
						if (plastic[i]->shape_.translate.x + plastic[i]->shape_.scale.x > plastic[j]->shape_.translate.x - plastic[j]->shape_.scale.x &&
							plastic[i]->shape_.translate.x + plastic[i]->shape_.scale.x < plastic[j]->shape_.translate.x + plastic[j]->shape_.scale.x)
						{
							if (plastic[i]->shape_.translate.y + plastic[i]->shape_.scale.y > plastic[j]->shape_.translate.y - plastic[j]->shape_.scale.y &&
								plastic[i]->shape_.translate.y - plastic[i]->shape_.scale.y < plastic[j]->shape_.translate.y + plastic[j]->shape_.scale.y)
							{
								plastic[i]->shape_.translate.x = plastic[j]->shape_.translate.x - plastic[j]->shape_.scale.x - plastic[i]->shape_.scale.x;
								plastic[i]->LocalToScreen();
								plastic[i]->MapUpdate();
							}
						}
					}

					if (plastic[i]->vel_.x < 0.0f)
					{
						if (plastic[i]->shape_.translate.x - plastic[i]->shape_.scale.x < plastic[j]->shape_.translate.x + plastic[j]->shape_.scale.x &&
							plastic[i]->shape_.translate.x - plastic[i]->shape_.scale.x > plastic[j]->shape_.translate.x - plastic[j]->shape_.scale.x)
						{
							if (plastic[i]->shape_.translate.y + plastic[i]->shape_.scale.y > plastic[j]->shape_.translate.y - plastic[j]->shape_.scale.y &&
								plastic[i]->shape_.translate.y - plastic[i]->shape_.scale.y < plastic[j]->shape_.translate.y + plastic[j]->shape_.scale.y)
							{
								plastic[i]->shape_.translate.x = plastic[j]->shape_.translate.x + plastic[j]->shape_.scale.x + plastic[i]->shape_.scale.x;
								plastic[i]->LocalToScreen();
								plastic[i]->MapUpdate();
							}
						}
					}
				}

				if (plastic[i]->isArrival_ && treasure[j]->isArrival_)
				{
					if (plastic[i]->vel_.x > 0.0f)
					{
						if (plastic[i]->shape_.translate.x + plastic[i]->shape_.scale.x > treasure[j]->shape_.translate.x - treasure[j]->shape_.scale.x &&
							plastic[i]->shape_.translate.x + plastic[i]->shape_.scale.x < treasure[j]->shape_.translate.x + treasure[j]->shape_.scale.x)
						{
							if (plastic[i]->shape_.translate.y + plastic[i]->shape_.scale.y > treasure[j]->shape_.translate.y - treasure[j]->shape_.scale.y &&
								plastic[i]->shape_.translate.y - plastic[i]->shape_.scale.y < treasure[j]->shape_.translate.y + treasure[j]->shape_.scale.y)
							{
								plastic[i]->shape_.translate.x = treasure[j]->shape_.translate.x - treasure[j]->shape_.scale.x - plastic[i]->shape_.scale.x;
								plastic[i]->LocalToScreen();
								plastic[i]->MapUpdate();
							}
						}
					}

					if (plastic[i]->vel_.x < 0.0f)
					{
						if (plastic[i]->shape_.translate.x - plastic[i]->shape_.scale.x < treasure[j]->shape_.translate.x + treasure[j]->shape_.scale.x &&
							plastic[i]->shape_.translate.x - plastic[i]->shape_.scale.x > treasure[j]->shape_.translate.x - treasure[j]->shape_.scale.x)
						{
							if (plastic[i]->shape_.translate.y + plastic[i]->shape_.scale.y > treasure[j]->shape_.translate.y - treasure[j]->shape_.scale.y &&
								plastic[i]->shape_.translate.y - plastic[i]->shape_.scale.y < treasure[j]->shape_.translate.y + treasure[j]->shape_.scale.y)
							{
								plastic[i]->shape_.translate.x = treasure[j]->shape_.translate.x + treasure[j]->shape_.scale.x + plastic[i]->shape_.scale.x;
								plastic[i]->LocalToScreen();
								plastic[i]->MapUpdate();
							}
						}
					}
				}

				if (treasure[i]->isArrival_ && plastic[j]->isArrival_)
				{
					if (treasure[i]->vel_.x > 0.0f)
					{
						if (treasure[i]->shape_.translate.x + treasure[i]->shape_.scale.x > plastic[j]->shape_.translate.x - plastic[j]->shape_.scale.x &&
							treasure[i]->shape_.translate.x + treasure[i]->shape_.scale.x < plastic[j]->shape_.translate.x + plastic[j]->shape_.scale.x)
						{
							if (treasure[i]->shape_.translate.y + treasure[i]->shape_.scale.y > plastic[j]->shape_.translate.y - plastic[j]->shape_.scale.y &&
								treasure[i]->shape_.translate.y - treasure[i]->shape_.scale.y < plastic[j]->shape_.translate.y + plastic[j]->shape_.scale.y)
							{
								treasure[i]->shape_.translate.x = plastic[j]->shape_.translate.x - plastic[j]->shape_.scale.x - treasure[i]->shape_.scale.x;
								treasure[i]->LocalToScreen();
								treasure[i]->MapUpdate();
							}
						}
					}

					if (treasure[i]->vel_.x < 0.0f)
					{
						if (treasure[i]->shape_.translate.x - treasure[i]->shape_.scale.x < plastic[j]->shape_.translate.x + plastic[j]->shape_.scale.x &&
							treasure[i]->shape_.translate.x - treasure[i]->shape_.scale.x > plastic[j]->shape_.translate.x - plastic[j]->shape_.scale.x)
						{
							if (treasure[i]->shape_.translate.y + treasure[i]->shape_.scale.y > plastic[j]->shape_.translate.y - plastic[j]->shape_.scale.y &&
								treasure[i]->shape_.translate.y - treasure[i]->shape_.scale.y < plastic[j]->shape_.translate.y + plastic[j]->shape_.scale.y)
							{
								treasure[i]->shape_.translate.x = plastic[j]->shape_.translate.x + plastic[j]->shape_.scale.x + treasure[i]->shape_.scale.x;
								treasure[i]->LocalToScreen();
								treasure[i]->MapUpdate();
							}
						}
					}
				}

				if (treasure[i]->isArrival_ && treasure[j]->isArrival_)
				{
					if (treasure[i]->vel_.x > 0.0f)
					{
						if (treasure[i]->shape_.translate.x + treasure[i]->shape_.scale.x > treasure[j]->shape_.translate.x - treasure[j]->shape_.scale.x &&
							treasure[i]->shape_.translate.x + treasure[i]->shape_.scale.x < treasure[j]->shape_.translate.x + treasure[j]->shape_.scale.x)
						{
							if (treasure[i]->shape_.translate.y + treasure[i]->shape_.scale.y > treasure[j]->shape_.translate.y - treasure[j]->shape_.scale.y &&
								treasure[i]->shape_.translate.y - treasure[i]->shape_.scale.y < treasure[j]->shape_.translate.y + treasure[j]->shape_.scale.y)
							{
								treasure[i]->shape_.translate.x = treasure[j]->shape_.translate.x - treasure[j]->shape_.scale.x - treasure[i]->shape_.scale.x;
								treasure[i]->LocalToScreen();
								treasure[i]->MapUpdate();
							}
						}
					}

					if (treasure[i]->vel_.x < 0.0f)
					{
						if (treasure[i]->shape_.translate.x - treasure[i]->shape_.scale.x < treasure[j]->shape_.translate.x + treasure[j]->shape_.scale.x &&
							treasure[i]->shape_.translate.x - treasure[i]->shape_.scale.x > treasure[j]->shape_.translate.x - treasure[j]->shape_.scale.x)
						{
							if (treasure[i]->shape_.translate.y + treasure[i]->shape_.scale.y > treasure[j]->shape_.translate.y - treasure[j]->shape_.scale.y &&
								treasure[i]->shape_.translate.y - treasure[i]->shape_.scale.y < treasure[j]->shape_.translate.y + treasure[j]->shape_.scale.y)
							{
								treasure[i]->shape_.translate.x = treasure[j]->shape_.translate.x + treasure[j]->shape_.scale.x + treasure[i]->shape_.scale.x;
								treasure[i]->LocalToScreen();
								treasure[i]->MapUpdate();
							}
						}
					}

					if (treasure[i]->jump_.isJump)
					{
						if (treasure[i]->shape_.translate.y - treasure[i]->shape_.scale.y < treasure[j]->shape_.translate.y + treasure[i]->shape_.scale.y &&
							treasure[i]->shape_.translate.y - treasure[i]->shape_.scale.y > treasure[j]->shape_.translate.y - treasure[i]->shape_.scale.y)
						{
							if (treasure[i]->shape_.translate.x + treasure[i]->shape_.scale.x > treasure[j]->shape_.translate.x - treasure[j]->shape_.scale.x &&
								treasure[i]->shape_.translate.x - treasure[i]->shape_.scale.x < treasure[j]->shape_.translate.x + treasure[j]->shape_.scale.x)
							{
								treasure[i]->jump_.isJump = false;
								treasure[i]->vel_.y = 0.0f;

								treasure[i]->shape_.translate.y = treasure[j]->shape_.translate.y + treasure[j]->shape_.scale.y + treasure[i]->shape_.scale.y;

								treasure[i]->LocalToScreen();
								treasure[i]->MapUpdate();
							}
						}
					}
				}
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// プレイヤー
		player->Draw(ghWhite);

		// ステージ
		map->Draw(ghWhite);

		// ブロック
		for (int i = 0; i < kTileNum; i++)
		{
			plastic[i]->Draw(ghWhite);
			treasure[i]->Draw(ghWhite);
		}

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

	delete map;

	for (int i = 0; i < kTileNum; i++)
	{
		delete plastic[i];
		delete treasure[i];
	}


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}