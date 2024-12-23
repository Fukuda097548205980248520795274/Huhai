#pragma once
#include "./Class/Object/Object.h"

class Enemy : public Object
{
public:

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
	virtual void Move(Map* map);

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh">画像</param>
	virtual void Draw(int gh);

	// IDを数える値
	static int countId;

	// ID
	int id_;
};