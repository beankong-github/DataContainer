#include <iostream>
#include "QuadTree.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 트리 생성
	QuadTree tree(Bounds(0.f, 0.f, 100.f, 100.f));

	tree.Insert(new Node(Bounds(40.f, 40.f, 20.f, 20.f)));

	std::cin.get();

	return 0;
}
