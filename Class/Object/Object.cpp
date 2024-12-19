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