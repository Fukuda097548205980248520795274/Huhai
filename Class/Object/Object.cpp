#include "Object.h"

/// <summary>
/// ローカル座標をスクリーン座標に変換する
/// </summary>
void Object::LocalToScreen()
{
	// 全てを結合した行列
	struct Matrix3x3 wvpvpMatrix;

	wvpvpMatrix = Multiply(MakeWorldMatrix(shape_.scale, shape_.theta, shape_.translate),
		MakeInverseMatrix(MakeWorldMatrix({ 1.0f , 1.0f }, 0.0f, { 0.0f , 0.0f })));

	wvpvpMatrix = Multiply(wvpvpMatrix, MakeOrthoMatrix(0.0f, static_cast<float>(kScreenHeight), static_cast<float>(kScreenWidth), 0.0f));

	wvpvpMatrix = Multiply(wvpvpMatrix, MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(kScreenWidth), static_cast<float>(kScreenHeight)));

	pos_.screen.leftTop = Transform(pos_.local.leftTop, wvpvpMatrix);
	pos_.screen.rightTop = Transform(pos_.local.rightTop, wvpvpMatrix);
	pos_.screen.leftBottom = Transform(pos_.local.leftBottom, wvpvpMatrix);
	pos_.screen.rightBottom = Transform(pos_.local.rightBottom, wvpvpMatrix);
}

/// <summary>
/// マップの位置を更新する
/// </summary>
void Object::MapUpdate()
{
	map_.leftTop = { static_cast<int>(pos_.screen.leftTop.x) / kTileSize , static_cast<int>(pos_.screen.leftTop.y) / kTileSize };
	map_.rightTop = { static_cast<int>(pos_.screen.rightTop.x) / kTileSize , static_cast<int>(pos_.screen.rightTop.y) / kTileSize };
	map_.leftBottom = { static_cast<int>(pos_.screen.leftBottom.x) / kTileSize , static_cast<int>(pos_.screen.leftBottom.y) / kTileSize };
	map_.rightBottom = { static_cast<int>(pos_.screen.rightBottom.x) / kTileSize , static_cast<int>(pos_.screen.rightBottom.y) / kTileSize };
}