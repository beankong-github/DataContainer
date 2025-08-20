
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


	// ��ȸ
	std::cout << "Ʈ�� ���� ��ȸ\n";
	tree.PreorderTraverse();

	// ����
	std::cout << "\n C��� ����\n";
	tree.Remove("C");

	std::cout << "Ʈ�� ���� ��ȸ\n";
	tree.PreorderTraverse();

	std::cin.get();
}