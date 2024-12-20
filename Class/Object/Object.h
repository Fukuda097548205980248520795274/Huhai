#pragma once
#include <Novice.h>
#include "Strucutre.h"
#include "Constant.h"
#include "./Function/Matrix/Matrix.h"
#include "./Class/Map/Map.h"

class Object
{
public:

	/// <summary>
	/// ローカル座標をスクリーン座標に変換する
	/// </summary>
	void LocalToScreen();

	/// <summary>
	/// マップの位置を更新する
	/// </summary>
	void MapUpdate();

	// 出現しているかどうか（出現フラグ）
	int isArrival_;

	// 図形
	struct Shape shape_;

	// 位置
	struct Pos2 pos_;

	// マップ
	struct VertexMap map_;

	// 移動速度
	struct Vec2 vel_;

	// ジャンプ
	struct Jump jump_;
};

