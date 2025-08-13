#include<iostream>
#include "LinkedList.h"

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	LinkedList<int> list;

	FILE* inputs = nullptr;
	fopen_s(&inputs, "input.txt", "rt");
	if (inputs != nullptr)
	{
		char  input[1024];
		fread_s(input, sizeof(input), 1, 1024, inputs);

		char* left = nullptr;
		char* num = strtok_s(input, " ", &left);

		while (num != nullptr)
		{
			list.PushLast(atoi(num));
			num = strtok_s(NULL, " ", &left);
		}
		list.Print();
	}

	std::cin.get();

	//while(true)
	//{ 
	//	std::cout << "추가할 데이터를 입력해주세요. 종료 q\n";
	//	std::cin >> input;

	//	if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
	//	{
	//		break;
	//	}

	//	if (!atoi(input))
	//	{
	//		std::cout << "숫자만 입력하세요. \n";
	//		continue;
	//	}

	//	list.PushLast(atoi(input));
	//	memset(input, 0, sizeof(input));
	//	list.Print();
	//}
 
}