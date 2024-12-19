#pragma once

// ベクトル
struct Vec2
{
	float x;
	float y;
};

// 行列
struct Matrix3x3
{
	float m[3][3];
};

// 頂点
struct Vertex
{
	// 左上
	struct Vec2 leftTop;

	// 右上
	struct Vec2 rightTop;

	// 左下
	struct Vec2 leftBottom;

	// 右下
	struct Vec2 rightBottom;
};