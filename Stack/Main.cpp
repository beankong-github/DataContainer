#include "Stack.h"

int main()
{
	// ���� ��ü ����
	Stack<int> stack;

	stack.Push(10);
	stack.Push(300);
	
	stack.Pop();

	std::cin.get();

	return 0;
}