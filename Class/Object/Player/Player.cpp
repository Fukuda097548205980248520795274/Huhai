#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	// 図形
	shape_.scale = { 24.0f , 24.0f };
	shape_.theta = 0.0f;
	shape_.translate = { 200.0f , 100.0f };

	// 位置
	pos_.local = { {-1.0f , 1.0f} , {1.0f , 1.0f} , {-1.0f , -1.0f} , {1.0f , -1.0f} };
	LocalToScreen();

	// マップ
	MapUpdate();

	// 移動速度
	vel_ = { 0.0f , 0.0f };
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{

}

/// <summary>
/// 操作する
/// </summary>
/// <param name="keys">キー</param>
/// <param name="preKeys">前のキー</param>
/// <param name="">
void Player::Operation(const char* keys, const char* preKeys , Map* map)
{
	// null を探す
	if (keys == nullptr || preKeys == nullptr || map == nullptr)
	{
		return;
	}

	/*   横移動   */

	// 移動速度を初期化する
	vel_.x = 0.0f;

	// Aキーで、右に移動する
	if (keys[DIK_A])
	{
		if (shape_.translate.x - shape_.scale.x > 0.0f)
		{
			vel_.x = -4.0f;

			map_.leftTop = { static_cast<int>(pos_.screen.leftTop.x + vel_.x) / kTileSize , static_cast<int>(pos_.screen.leftTop.y) / kTileSize };
			map_.rightTop = { static_cast<int>(pos_.screen.rightTop.x + vel_.x - 1.0f) / kTileSize , static_cast<int>(pos_.screen.rightTop.y) / kTileSize };
			map_.leftBottom = { static_cast<int>(pos_.screen.leftBottom.x + vel_.x) / kTileSize , static_cast<int>(pos_.screen.leftBottom.y - 1.0f) / kTileSize };
			map_.rightBottom = { static_cast<int>(pos_.screen.rightBottom.x + vel_.x - 1.0f) / kTileSize , static_cast<int>(pos_.screen.rightBottom.y - 1.0f) / kTileSize };

			if (map->map_[map_.leftTop.row][map_.leftTop.column] != TILE_NOTHING ||
				map->map_[map_.leftBottom.row][map_.leftBottom.column] != TILE_NOTHING)
			{
				// 進まない
				vel_.x = 0.0f;

				// 押し込み処理
				shape_.translate.x = static_cast<float>(map_.leftTop.column * kTileSize + kTileSize) + shape_.scale.x;

				// 座標変換
				LocalToScreen();
				MapUpdate();
			}
		}
	}

	// Dキーで、左に移動する
	if (keys[DIK_D])
	{
		if (shape_.translate.x + shape_.scale.x < static_cast<float>(kScreenWidth))
		{
			vel_.x = 4.0f;

			map_.leftTop = { static_cast<int>(pos_.screen.leftTop.x + vel_.x) / kTileSize , static_cast<int>(pos_.screen.leftTop.y) / kTileSize };
			map_.rightTop = { static_cast<int>(pos_.screen.rightTop.x + vel_.x - 1.0f) / kTileSize , static_cast<int>(pos_.screen.rightTop.y) / kTileSize };
			map_.leftBottom = { static_cast<int>(pos_.screen.leftBottom.x + vel_.x) / kTileSize , static_cast<int>(pos_.screen.leftBottom.y - 1.0f) / kTileSize };
			map_.rightBottom = { static_cast<int>(pos_.screen.rightBottom.x + vel_.x - 1.0f) / kTileSize , static_cast<int>(pos_.screen.rightBottom.y - 1.0f) / kTileSize };

			if (map->map_[map_.rightTop.row][map_.rightTop.column] != TILE_NOTHING ||
				map->map_[map_.rightBottom.row][map_.rightBottom.column] != TILE_NOTHING)
			{
				// 進まない
				vel_.x = 0.0f;

				// 押し込み処理
				shape_.translate.x = static_cast<float>(map_.rightTop.column * kTileSize) - shape_.scale.x;

				// 座標変換
				LocalToScreen();
				MapUpdate();
			}
		}
	}

	// 動かす
	shape_.translate.x += vel_.x;


	// 座標変換
	LocalToScreen();
	MapUpdate();
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="gh">画像</param>
void Player::Draw(int gh)
{
	Novice::DrawQuad
	(
		static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
		static_cast<int>(pos_.screen.rightTop.x), static_cast<int>(pos_.screen.rightTop.y),
		static_cast<int>(pos_.screen.leftBottom.x), static_cast<int>(pos_.screen.leftBottom.y),
		static_cast<int>(pos_.screen.rightBottom.x), static_cast<int>(pos_.screen.rightBottom.y),
		0, 0, 1, 1, gh, 0xFFFFFFFF
	);
}