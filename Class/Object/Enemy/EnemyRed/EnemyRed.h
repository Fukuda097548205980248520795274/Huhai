#pragma once
#include "./Class/Object/Enemy/Enemy.h"

class EnemyRed : public Enemy
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyRed();

	/// <summary>
	/// 動かす
	/// </summary>
	/// <param name="map"></param>
	void Move(Map* map) override;

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh"></param>
	void Draw(int gh) override;
};