#pragma once

#include <iostream>

// C++ 
struct Position
{
	Position(int x = 0, int y = 0)
		:x(x), y(y)
	{
	}

	bool operator == (const Position& other)
	{
		return x == other.x && y == other.y;
	}

	int x;
	int y;
};

class Node
{
public:
	Node(int x, int y, Node* parentNode = nullptr)
		: pos(x, y), parent(parentNode)
	{
	}

	Position operator - (const Node& other)
	{
		return Position(pos.x - other.pos.x, pos.y - other.pos.y);
	}

	bool operator == (const Node& other) const
	{
		return pos.x == other.pos.x && pos.y == other.pos.y;
	}

public:
	Position pos;
	float gCost = 0.f;
	float hCost = 0.f;
	float fCost = 0.f;
	Node* parent = nullptr; // 이동할 때마다 이전 노드를 부모로 지정하여 길을 만든다.
};