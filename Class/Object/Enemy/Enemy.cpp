#include "Enemy.h"

/// <summary>
/// 配置する
/// </summary>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
void Enemy::Arrangement(float posX , float posY)
{
	if (isArrival_ == false)
	{
		// IDを入れる
		id_ = ++countId;

		// 出現させる（出現フラグがtrueになる）
		isArrival_ = true;

		// 位置
		shape_.translate = { posX , static_cast<float>(kScreenHeight) - posY };
		LocalToScreen();

		// マップ
		MapUpdate();

		// 移動速度
		vel_ = { -2.0f , 0.0f };

		// ジャンプ
		jump_.isJump = false;
		jump_.fallingVel = 0.0f;
	}
}

/// <summary>
/// null を探す
/// </summary>
/// <param name="map">マップ</param>
void Enemy::Move(Map* map)
{
	// null を探す
	if (map == nullptr)
	{
		return;
	}
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="gh"></param>
void Enemy::Draw(int gh)
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