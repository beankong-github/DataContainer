#include "Stack.h"

int main()
{
	// 스택 객체 생성
	Stack<int> stack;

	stack.Push(10);
	stack.Push(300);
	
	stack.Pop();

	std::cin.get();

	return 0;
}