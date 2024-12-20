#pragma once
#include "./Class/Object/Object.h"

class Treasure : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Treasure();

	/// <summary>
	/// 配置する
	/// </summary>
	/// <param name="posX">X軸の位置</param>
	/// <param name="posY">Y軸の位置</param>
	void Arrangement(float posX, float posY);

	/// <summary>
	/// 動かす
	/// </summary>
	/// <param name="map">マップ</param>
	void Move(Map* map);

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh">画像</param>
	void Draw(int gh);

	// IDに入れる値
	static int countId;

	// ID
	int id_;
};