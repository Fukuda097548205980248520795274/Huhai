#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	// 出現しているかどうか（出現フラグ）
	isArrival_ = true;

	// 図形
	shape_.scale = { 18.0f , 18.0f };
	shape_.theta = 0.0f;
	shape_.translate = { 50.0f , 300.0f };

	// 位置
	pos_.local = { {-1.0f , 1.0f} , {1.0f , 1.0f} , {-1.0f , -1.0f} , {1.0f , -1.0f} };
	LocalToScreen();

	// マップ
	MapUpdate();

	// 移動速度
	vel_ = { 0.0f , 0.0f };

	// ジャンプ
	jump_.isJump = false;
	jump_.fallingVel = 0.0f;
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


	/*   梯子   */

	// Wキーで、梯子を上る
	if (keys[DIK_W])
	{
		if (map->map_[(kScreenHeight - static_cast<int>(shape_.translate.y)) / kTileSize][static_cast<int>(shape_.translate.x) / kTileSize] == TILE_LADDER)
		{
			shape_.translate.y += 2.0f;
		}
	}
	else
	{
		if (map->map_[(kScreenHeight - static_cast<int>(shape_.translate.y)) / kTileSize][static_cast<int>(shape_.translate.x) / kTileSize] == TILE_LADDER)
		{
			shape_.translate.y += -2.0f;
		}
	}


	/*   ジャンプ   */

	// Jキーで、ジャンプする（ジャンプフラグをtrueにする）
	if (!preKeys[DIK_J] && keys[DIK_J])
	{
		if (jump_.isJump == false)
		{
			jump_.isJump = true;
			jump_.fallingVel = -0.5f;

			// 上に飛ぶ
			vel_.y = 10.0f;
		}
	}

	// 空中にいるとき、自動的にジャンプする（ジャンプフラグがtrueになる）
	if (jump_.isJump == false)
	{
		map_.leftTop = { static_cast<int>(pos_.screen.leftTop.x) / kTileSize , static_cast<int>(pos_.screen.leftTop.y) / kTileSize };
		map_.rightTop = { static_cast<int>(pos_.screen.rightTop.x - 1.0f) / kTileSize , static_cast<int>(pos_.screen.rightTop.y) / kTileSize };
		map_.leftBottom = { static_cast<int>(pos_.screen.leftBottom.x) / kTileSize , static_cast<int>(pos_.screen.leftBottom.y) / kTileSize };
		map_.rightBottom = { static_cast<int>(pos_.screen.rightBottom.x - 1.0f) / kTileSize , static_cast<int>(pos_.screen.rightBottom.y) / kTileSize };

		if (map->map_[map_.leftBottom.row][map_.leftBottom.column] == TILE_NOTHING &&
			map->map_[map_.rightBottom.row][map_.rightBottom.column] == TILE_NOTHING)
		{
			jump_.isJump = true;
			jump_.fallingVel = -0.5f;

			// 上に飛ぶ
			vel_.y = 0.0f;
		}

		// 座標変換
		LocalToScreen();
		MapUpdate();
	}

	// ジャンプしている（ジャンプフラグがtrueである）ときの動き
	if (jump_.isJump)
	{

		// 徐々に減速する
		vel_.y += jump_.fallingVel;

		// 移動速度を制限する
		if (vel_.y < -48.0f)
		{
			vel_.y = -48.0f;
		}

		// 上昇中
		if (vel_.y > 0.0f)
		{
			map_.leftTop = { static_cast<int>(pos_.screen.leftTop.x) / kTileSize , static_cast<int>(pos_.screen.leftTop.y - vel_.y) / kTileSize };
			map_.rightTop = { static_cast<int>(pos_.screen.rightTop.x - 1.0f) / kTileSize , static_cast<int>(pos_.screen.rightTop.y - vel_.y) / kTileSize };
			map_.leftBottom = { static_cast<int>(pos_.screen.leftBottom.x) / kTileSize , static_cast<int>(pos_.screen.leftBottom.y - vel_.y - 1.0f) / kTileSize };
			map_.rightBottom = { static_cast<int>(pos_.screen.rightBottom.x - 1.0f) / kTileSize , static_cast<int>(pos_.screen.rightBottom.y - vel_.y - 1.0f) / kTileSize };

			// 天井に着いたら、上昇速度が消える
			if (map->map_[map_.leftTop.row][map_.leftTop.column] != TILE_NOTHING ||
				map->map_[map_.rightTop.row][map_.rightTop.column] != TILE_NOTHING)
			{
				vel_.y = 0.0f;

				shape_.translate.y = static_cast<float>(kScreenHeight - (map_.leftTop.row * kTileSize + kTileSize)) - shape_.scale.y;

				// 座標変換
				LocalToScreen();
				MapUpdate();
			}
		}
		else if(vel_.y <= 0.0f)
		{
			// 落下中

			map_.leftTop = { static_cast<int>(pos_.screen.leftTop.x) / kTileSize , static_cast<int>(pos_.screen.leftTop.y - vel_.y) / kTileSize };
			map_.rightTop = { static_cast<int>(pos_.screen.rightTop.x - 1.0f) / kTileSize , static_cast<int>(pos_.screen.rightTop.y - vel_.y) / kTileSize };
			map_.leftBottom = { static_cast<int>(pos_.screen.leftBottom.x) / kTileSize , static_cast<int>(pos_.screen.leftBottom.y - vel_.y - 1.0f) / kTileSize };
			map_.rightBottom = { static_cast<int>(pos_.screen.rightBottom.x - 1.0f) / kTileSize , static_cast<int>(pos_.screen.rightBottom.y - vel_.y - 1.0f) / kTileSize };

			// 地上についたら、ジャンプをやめる（ジャンプフラグがfalseになる）
			if (map->map_[map_.leftBottom.row][map_.leftBottom.column] != TILE_NOTHING ||
				map->map_[map_.rightBottom.row][map_.rightBottom.column] != TILE_NOTHING)
			{
				// 落下が止まる
				vel_.y = 0.0f;

				shape_.translate.y = static_cast<float>(kScreenHeight - (map_.leftBottom.row * kTileSize)) + shape_.scale.y;

				jump_.isJump = false;

				// 座標変換
				LocalToScreen();
				MapUpdate();
			}
		}
	}

	// 動かす
	shape_.translate.y += vel_.y;


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
	if (isArrival_)
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
}