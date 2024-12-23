#pragma once
#include "./Class/Object/Object.h"
#include "./Class/Object/Player/Player.h"

class Plastic : public Object
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Plastic();

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
	/// <param name"player">プレイヤー</param>
	void Move(Map* map , Player* player);

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