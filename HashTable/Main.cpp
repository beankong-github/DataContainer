#include "HashTable.h"
#include <iostream>

int main()
{
	HashTable table;

	table.Add("n", "010-11111111");
	table.Add("n", "010-12111111");
	table.Add("m", "010-12311111");
	table.Add("o", "010-12341111");
	table.Add("p", "010-12345111");
	table.Add("q", "010-12345611");
	table.Add("r", "010-12345671");

	table.Print();


	std::cin.get();
}