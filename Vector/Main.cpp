#include<iostream>
#include "Vector.h"

int main()
{
	const int count = 30;
	Vector<int> vector;

	for (int i = 0; i < count; ++i)
	{
		vector.PushBack(i + 1);
	}

	for (const auto& v : vector)
	{
		std::cout << v << std::endl;
	}

	std::cin.get();
}