#include <iostream>
#include "Stack.h"

struct Vector2
{
	Vector2()
		:x(0), y(0)
	{
	}
	Vector2(int x, int y)
		:x(x), y(y)
	{
	}

	// ��� ���Ǹ� ���� ������ �����ε�
	friend std::ostream& operator <<(std::ostream& os, const Vector2& position)
	{
		return os << "(" << position.x << "," << position.y << ")";
	}

	int x;
	int y;
};

// ���� ��.
// s : ���� ����
// g : ��ǥ ����
// 1 : �̵� �Ұ�
// 0 : �̵� ����
const size_t MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1','1','1','1','1','1'},
	{'s','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','g'},
	{'1','1','1','1','1','1'}
};

bool IsValidLocation(int y, int x)
{
	if (y >= MAZE_SIZE || x >= MAZE_SIZE)
		return false;

	if (y < 0 || x < 0)
		return false;

	return map[y][x] == '0' || map[y][x] == 'g';
}

int main()
{
	// ���� ��ġ �˻�
	int startY = 0;
	int startX = 0;

	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			std::cout << map[y][x] << " ";

			if (map[y][x] == 's')
			{
				startX = x;
				startY = y;
			}
		}

		std::cout << "\n";
	}

	// ���� ��ġ���� Ž��
	// ���ÿ� ����
	Stack<Vector2> locationStack;
	locationStack.Push(Vector2(startX, startY));

	// �̷�Ž��
	while (!locationStack.IsEmpty())
	{
		// ���� ��ġ ��ȯ(����� ����)
		Vector2 current = locationStack.Pop();
		std::cout << "�湮" << current << " ";

		// �����ߴ��� Ȯ��
		if (map[current.y][current.x] == 'g')
		{
			std::cout << "\n �̷� Ž�� ���� \n";

			std::cin.get();
			return 0;
		}

		// Ž�� �̾��
		map[current.y][current.x] = '.';

		const static Vector2 dir[4] = { Vector2(1, 0), Vector2(-1, 0), Vector2(0, 1), Vector2(0, -1) };

		for (int d = 0; d < 4; ++d)
		{
			Vector2 next = current;
			next.x += dir[d].x;
			next.y += dir[d].y;

			if (IsValidLocation(next.y, next.x))
			{
				locationStack.Push(next);
			}
		}
	}
}