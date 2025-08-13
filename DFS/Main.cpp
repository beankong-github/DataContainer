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

	// 출력 편의를 위해 연산자 오버로딩
	friend std::ostream& operator <<(std::ostream& os, const Vector2& position)
	{
		return os << "(" << position.x << "," << position.y << ")";
	}

	int x;
	int y;
};

// 작은 맵.
// s : 시작 지점
// g : 목표 지점
// 1 : 이동 불가
// 0 : 이동 가능
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
	// 시작 위치 검색
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

	// 시작 위치부터 탐색
	// 스택에 삽입
	Stack<Vector2> locationStack;
	locationStack.Push(Vector2(startX, startY));

	// 미로탐색
	while (!locationStack.IsEmpty())
	{
		// 현재 위치 반환(출력을 위해)
		Vector2 current = locationStack.Pop();
		std::cout << "방문" << current << " ";

		// 도착했는지 확인
		if (map[current.y][current.x] == 'g')
		{
			std::cout << "\n 미로 탐색 성공 \n";

			std::cin.get();
			return 0;
		}

		// 탐색 이어가기
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