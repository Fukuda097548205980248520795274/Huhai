#pragma once
#include "./Class/Object/Enemy/Enemy.h"

class EnemyGreen : public Enemy
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyGreen();

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

