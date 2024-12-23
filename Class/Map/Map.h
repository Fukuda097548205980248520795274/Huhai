#pragma once
#include <Novice.h>
#include <stdio.h>
#include "Constant.h"
#include "Enumeration.h"

class Map
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="fName">ファイルの名前（パス）</param>
	Map(const char* fName);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Map();

	/// <summary>
	/// テキストのマップを読み込む
	/// </summary>
	/// <param name="fName">ファイルの名前（パス）</param>
	void LoadMapText(const char* fName);

	/// <summary>
	/// 腐らせる
	/// </summary>
	void Rotten();

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="gh">画像</param>
	void Draw(int gh);

	// マップ
	int map_[kMapChipRow][kMapChipColumn];
};

