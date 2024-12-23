#include "Map.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="fName"></param>
Map::Map(const char* fName)
{
	// null を探す
	if (fName == nullptr)
	{
		return;
	}

	LoadMapText(fName);
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
}

/// <summary>
/// 腐らせる!!
/// </summary>
void Map::Rotten()
{
	for (int row = 0; row < kMapChipRow; row++)
	{
		for (int column = 0; column < kMapChipColumn; column++)
		{
			if (map_[row][column] < 0)
			{
				map_[row][column]++;

				if (map_[row][column] >= 0)
				{
					map_[row][column] = TILE_NOTHING;
				}
			}
		}
	}
}

/// <summary>
/// テキストのマップを読み込む
/// </summary>
/// <param name="fName">ファイルの名前（パス）</param>
void Map::LoadMapText(const char* fName)
{
	/*   読み込み   */

	// null を探す
	if (fName == nullptr)
	{
		return;
	}

	FILE* fp;

	fopen_s(&fp, fName, "r");

	if (fp == nullptr)
	{
		return;
	}
	else
	{
		for (int row = 0; row < kMapChipRow; row++)
		{
			for (int column = 0; column < kMapChipColumn; column++)
			{
				fscanf_s(fp, "%d", &map_[row][column]);
			}
		}
	}

	fclose(fp);
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="gh"></param>
void Map::Draw(int gh)
{
	for (int row = 0; row < kMapChipRow; row++)
	{
		for (int column = 0; column < kMapChipColumn; column++)
		{
			switch (map_[row][column])
			{
			case TILE_GROUND:

				Novice::DrawQuad
				(
					static_cast<int>(column * kTileSize), static_cast<int>(row * kTileSize),
					static_cast<int>(column * kTileSize + kTileSize), static_cast<int>(row * kTileSize),
					static_cast<int>(column * kTileSize), static_cast<int>(row * kTileSize + kTileSize),
					static_cast<int>(column * kTileSize + kTileSize), static_cast<int>(row * kTileSize + kTileSize),
					0, 0, 1, 1, gh, 0xFFFFFFFF
				);

				break;

			case TILE_BLOCK:

				Novice::DrawQuad
				(
					static_cast<int>(column * kTileSize), static_cast<int>(row * kTileSize),
					static_cast<int>(column * kTileSize + kTileSize), static_cast<int>(row * kTileSize),
					static_cast<int>(column * kTileSize), static_cast<int>(row * kTileSize + kTileSize),
					static_cast<int>(column * kTileSize + kTileSize), static_cast<int>(row * kTileSize + kTileSize),
					0, 0, 1, 1, gh, 0xBBBBFFFF
				);

				break;

			case TILE_BLOCK_ROTTED:

				Novice::DrawQuad
				(
					static_cast<int>(column * kTileSize), static_cast<int>(row * kTileSize),
					static_cast<int>(column * kTileSize + kTileSize), static_cast<int>(row * kTileSize),
					static_cast<int>(column * kTileSize), static_cast<int>(row * kTileSize + kTileSize),
					static_cast<int>(column * kTileSize + kTileSize), static_cast<int>(row * kTileSize + kTileSize),
					0, 0, 1, 1, gh, 0x88FF00FF
				);

				break;

			case TILE_LADDER:

				Novice::DrawQuad
				(
					static_cast<int>(column * kTileSize), static_cast<int>(row * kTileSize),
					static_cast<int>(column * kTileSize + kTileSize), static_cast<int>(row * kTileSize),
					static_cast<int>(column * kTileSize), static_cast<int>(row * kTileSize + kTileSize),
					static_cast<int>(column * kTileSize + kTileSize), static_cast<int>(row * kTileSize + kTileSize),
					0, 0, 1, 1, gh, 0x00FFFFFF
				);

				break;
			}

			if (map_[row][column] < 0)
			{
				Novice::DrawQuad
				(
					static_cast<int>(column * kTileSize), static_cast<int>(row * kTileSize),
					static_cast<int>(column * kTileSize + kTileSize), static_cast<int>(row * kTileSize),
					static_cast<int>(column * kTileSize), static_cast<int>(row * kTileSize + kTileSize),
					static_cast<int>(column * kTileSize + kTileSize), static_cast<int>(row * kTileSize + kTileSize),
					0, 0, 1, 1, gh, 0x555500FF
				);
			}
		}
	}
}