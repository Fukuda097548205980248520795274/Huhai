#pragma once
#include "./Class/Object/Object.h"

class Plastic : public Object
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Plastic();

	/// <summary>
	/// 動かす
	/// </summary>
	/// <param name="map">マップ</param>
	void Move(Map* map);

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh"></param>
	void Draw(int gh);

	// IDをカウントする
	static int countId;

	// ID
	int id_;
};

