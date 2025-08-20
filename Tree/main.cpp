
#include "Tree.h"
#include "String.h"
int main()
{
	Tree<String> tree("A");
	tree.AddChild("A", "B");
	tree.AddChild("A", "C");
	tree.AddChild("B", "D");
	tree.AddChild("B", "E");
	tree.AddChild("C", "F");


	// 순회
	std::cout << "트리 전위 순회\n";
	tree.PreorderTraverse();

	// 삭제
	std::cout << "\n C노드 삭제\n";
	tree.Remove("C");

	std::cout << "트리 전위 순회\n";
	tree.PreorderTraverse();

	std::cin.get();
}