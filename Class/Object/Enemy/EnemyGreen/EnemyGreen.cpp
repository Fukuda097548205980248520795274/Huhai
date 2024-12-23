#include "EnemyGreen.h"

/// <summary>
/// コンストラクタ
/// </summary>
EnemyGreen::EnemyGreen()
{
	// ID
	id_ = 0;

	// 出現しているかどうか（出現フラグ）
	isArrival_ = false;

	// 図形
	shape_.scale = { 20.0f , 20.0f };
	shape_.theta = 0.0f;
	shape_.translate = { 0.0f , 0.0f };

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
/// 動かす
/// </summary>
/// <param name="map">マップ</param>
void EnemyGreen::Move(Map* map)
{
	// null を探す
	if (map == nullptr)
	{
		return;
	}

	if (isArrival_)
	{
		shape_.translate.x += vel_.x;

		LocalToScreen();
		MapUpdate();

		// 壁に触れたら、反転する
		if (map->map_[(kScreenHeight - static_cast<int>(shape_.translate.y)) / kTileSize][static_cast<int>(shape_.translate.x - shape_.scale.x) / kTileSize] != TILE_NOTHING ||
			map->map_[(kScreenHeight - static_cast<int>(shape_.translate.y)) / kTileSize][static_cast<int>(shape_.translate.x + shape_.scale.x - 1.0f) / kTileSize] != TILE_NOTHING)
		{
			vel_.x *= -1.0f;
		}


		/*   落下   */

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
			} else if (vel_.y <= 0.0f)
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


		/*   腐敗   */

		// ジャンプしていないとき、下にあるブロックを腐らせる
		if (jump_.isJump == false)
		{
			if (vel_.x < 0.0f)
			{
				if (map->map_[(kScreenHeight - static_cast<int>(shape_.translate.y - shape_.scale.y)) / kTileSize][(static_cast<int>(shape_.translate.x + shape_.scale.x - 1.0f) / kTileSize)] == TILE_BLOCK)
				{
					map->map_[(kScreenHeight - static_cast<int>(shape_.translate.y - shape_.scale.y)) / kTileSize][(static_cast<int>(shape_.translate.x + shape_.scale.x - 1.0f) / kTileSize)] = -600;
				}
			} else if (vel_.x > 0.0f)
			{
				if (map->map_[(kScreenHeight - static_cast<int>(shape_.translate.y - shape_.scale.y)) / kTileSize][(static_cast<int>(shape_.translate.x - shape_.scale.x) / kTileSize)] == TILE_BLOCK)
				{
					map->map_[(kScreenHeight - static_cast<int>(shape_.translate.y - shape_.scale.y)) / kTileSize][(static_cast<int>(shape_.translate.x - shape_.scale.x) / kTileSize)] = -600;
				}
			}
		}


		// 座標変換
		LocalToScreen();
		MapUpdate();
	}
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="gh"></param>
void EnemyGreen::Draw(int gh)
{
	if (isArrival_)
	{
		Novice::DrawQuad
		(
			static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
			static_cast<int>(pos_.screen.rightTop.x), static_cast<int>(pos_.screen.rightTop.y),
			static_cast<int>(pos_.screen.leftBottom.x), static_cast<int>(pos_.screen.leftBottom.y),
			static_cast<int>(pos_.screen.rightBottom.x), static_cast<int>(pos_.screen.rightBottom.y),
			0, 0, 1, 1, gh, 0x00FF00FF
		);
	}
}