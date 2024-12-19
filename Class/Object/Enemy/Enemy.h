#pragma once
#include "./Class/Object/Object.h"

class Enemy : public Object
{
public:

	/// <summary>
	/// 動かす
	/// </summary>
	/// <param name="map">マップ</param>
	virtual void Move(Map* map);

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh"></param>
	virtual void Draw(int gh);

	// ID
	int id_;
};

