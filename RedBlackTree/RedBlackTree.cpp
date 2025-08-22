#include "RedBlackTree.h"


Node* RedBlackTree::nil = nullptr;

// �޸� ���� �Լ�
template<typename T>
void SafeDelete(T*& resource)
{
	if (resource)
	{
		delete resource;
		resource = nullptr;
	}
}

RedBlackTree::RedBlackTree()
{
	if (nil == nullptr)
	{
		nil = new Node(0, Color::Black);
	}

	root = nil;
}

RedBlackTree::~RedBlackTree()
{
	// ��������� ��� ��带 �����ϴ� �Լ� �ۼ� �� ȣ��
	DestroyRecursive(root);

	// Nil ��� ����
	SafeDelete(nil);

}

bool RedBlackTree::Find(int data, Node*& outNode)
{
	if (root == nil)
		return false;

	// ��������� �˻� 
	return FindRecursive(data, root, outNode);
}

bool RedBlackTree::Insert(int data)
{    // �ߺ� ���� Ȯ��.
	Node* node = nullptr;
	if (Find(data, node))
	{
		std::cout << "Error: �̹� ���� ���� �ֽ��ϴ�.\n";
		return false;
	}

	// ���� ó��.

	// Ʈ���� ������� ��Ʈ�� �߰�.
	if (root == nil)
	{
		// ��Ʈ�� ��.
		root = CreateNode(data, Color::Black);
		return true;
	}

	// ��������� ������ ��ġ �˻� �� ���� ó��.
	Node* newNode = CreateNode(data, Color::Red);
	InsertRecursive(root, newNode);

	// Todo: �Ʒ� ���� �ʿ����� Ȯ���� ��.
	// ���� �� ��� ����.
	newNode->SetColor(Color::Red);
	newNode->SetLeft(nil);
	newNode->SetRight(nil);

	// ���� �� ����.
	RestructureAfterInsert(newNode);
}

void RedBlackTree::Print(int depth, int blackCount)
{
	PrintRecursive(root, depth, blackCount);
}


Node* RedBlackTree::CreateNode(int data, Color color)
{
	Node* newNode = new Node(data, color);
	newNode->SetLeft(nil);
	newNode->SetRight(nil);

	return newNode;
}

bool RedBlackTree::FindRecursive(int data, Node* node, Node*& outNode)
{
	// ���ܱ��� �˻��ߴµ� ã�µ� ���Ͱ� ������.
	// => ����
	if (node == nil)
	{
		outNode = nullptr;
		return false;
	}

	// �����͸� ã�� ���
	if (node->GetData() == data)
	{
		outNode = node;
		return true;
	}

	// ã�� �����ͺ��� ��尡 ���� ���
	if (node->GetData() < data)
	{
		// ������ Ž��
		return FindRecursive(data, node->GetRight(), outNode);
	}
	// ã�� �����ͺ��� ��尡 �� ū ���
	else
	{
		// ���� Ž��
		return FindRecursive(data, node->GetLeft(), outNode);
	}
}

void RedBlackTree::InsertRecursive(Node* node, Node* newNode)
{
	// �� ��� �����Ͱ� �� ������ ���� ���� Ʈ���� ����
	if (node->GetData() > newNode->GetData())
	{
		// ���� ���� �ڼ��� ������, ���� �ڼ����� �߰�
		if (node->GetLeft() == nil)
		{
			node->SetLeft(newNode);
			newNode->SetParent(node);
			return;
		}

		InsertRecursive(node->GetLeft(), newNode);
	}
	//	�� ��� �����Ͱ� �� ũ�� ���� ���� Ʈ���� ����	
	else if (node->GetData() < newNode->GetData())
	{
		// ������ ���� �ڼ��� ������, ������ �ڼ����� �߰�
		if (node->GetRight() == nil)
		{
			node->SetRight(newNode);
			newNode->SetParent(node);
			return;
		}

		InsertRecursive(node->GetRight(), newNode);
	}
}

void RedBlackTree::RestructureAfterInsert(Node* newNode)
{

	while (newNode != root
		&& newNode->GetParent()->GetColor() == Color::Red)
	{
		//�θ�� ������ Black, �Ҿƹ����� Red�� ���� ��, �Ҿƹ��� �������� �ٽ� �˻�
		// ���� �������� -> �θ��� ��ġ�� ���� �޶�����. (ex :�θ� left�� ������ right)
		// �θ� ���� - ���� ������
		if (newNode->GetParent() == newNode->GetParent()->GetParent()->GetLeft())
		{
			Node* uncle = newNode->GetParent()->GetParent()->GetRight();

			// case 1  : ���� ����
			if (uncle->GetColor() == Color::Red)
			{
				// �θ� ������ ������
				newNode->GetParent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);

				// �Ҿƹ����� ���������� ����
				newNode->GetParent()->GetParent()->SetColor(Color::Red);

				// ������ �Ҿƹ����� ����
				newNode = newNode->GetParent()->GetParent();
				continue;

			}

			//������ ����
			// �θ� Black, �Ҿƹ����� Red�� ���� ��, �Ҿƹ����� �������� ȸ��

			// case2 : �θ� ����,  ���� �������̸� ������� ����
			// => ȸ������ ���θ�-�θ�-�� ���������� ������ �Ѵ�.
			if (newNode == newNode->GetParent()->GetLeft())
			{
				// ��ȸ�� 
				// ���� �θ��� �޿� �ִٴ� �� ���� �� �۴ٴ� ���̹Ƿ�
				// ��ȸ���ؾ� ���θ� ������->���� ������->�θ�� 1�� ������ �����ϴ�.
				newNode = newNode->GetParent();
				RotateToLeft(newNode);

			}

			// case3. �θ�� ���� ��ġ�� �������� ��
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);

			// ��ȸ��
			RotateToRight(newNode->GetParent()->GetParent());

		}
		// �θ� ������-���� ����
		else
		{
			Node* uncle = newNode->GetParent()->GetParent()->GetLeft();

			// case 1  : ���� ����
			if (uncle->GetColor() == Color::Red)
			{
				// �θ� ������ ������
				newNode->GetParent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);

				// �Ҿƹ����� ���������� ����
				newNode->GetParent()->GetParent()->SetColor(Color::Red);

				// ������ �Ҿƹ����� ����
				newNode = newNode->GetParent()->GetParent();
				continue;

			}

			//������ ����
			// �θ� Black, �Ҿƹ����� Red�� ���� ��, �Ҿƹ����� �������� ȸ��

			// case2 : �θ� ������,  ���� �����̸� ������� ����
			// => ȸ������ ���θ�-�θ�-�� ���������� ������ �Ѵ�.
			if (newNode == newNode->GetParent()->GetLeft())
			{
				// ��ȸ�� 
				// ���� �θ��� ���ʿ� �ִٴ� �� ���� �� �۴ٴ� ���̹Ƿ�
				// ��ȸ���ؾ� ���θ� ������->���� ������->�θ�� 1�� ������ �����ϴ�.
				newNode = newNode->GetParent();
				RotateToRight(newNode);

			}

			// case3. �θ�� ���� ��ġ�� �������� ��
			//
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);

			//��ȸ��
			RotateToLeft(newNode->GetParent()->GetParent());
		}
	}

	// ��Ʈ�º����� ����
	root->SetColor(Color::Black);
}

void RedBlackTree::RotateToLeft(Node* node)
{
	// ������ �ڼ� ���
	Node* right = node->GetRight();

	//������ �ڼ��� ���� �ڼ� ��带 �θ��� ������ �ڼ����� ���
	// ���� Ž�� Ʈ�� Ư¡�� ���� ������ �ڼ��� ��� �ڼ��� �θ𺸴� ũ��
	node->SetRight(right->GetLeft());

	// �θ� ����
	if (right->GetLeft() != nil)
	{
		right->GetLeft()->SetParent(node);
	}


	// �θ� Root�� ���
	if (right->GetParent() == root)
	{
		// root �� ������ �ڼ����� ����
		root = right;
		right->SetParent(nullptr);
	}
	else
	{
		// ���θ� �������� �θ� ��� �־����� Ȯ��.
		if (node == node->GetParent()->GetLeft())
		{
			node->GetParent()->SetLeft(right);
		}
		else
		{
			node->GetParent()->SetRight(right);
		}
	}

	// ������ �ڼ��� ���� �ڽ����� �θ� ��� ���
	right->SetLeft(node);

	// �θ��� �θ� ������ �ڼ����� ����
	right->SetParent(node->GetParent());

	// �θ��� �θ� ������ �ڼ����� ����.
	node->SetParent(right);

}


// ȸ��: �θ�� �ڼ��� ��ġ�� �ٲٴ� ���.
// ��ȸ�� -> ���������� ȸ��.���� �ڼհ� �θ��� ��ġ�� ��ȯ.
void RedBlackTree::RotateToRight(Node* node)
{

	// ������ �ڼ� ���
	Node* left = node->GetLeft();

	// ���� �ڼ��� ������ �ڼ� ��带 �θ��� ���� �ڼ����� ���
	// ���� Ž�� Ʈ�� Ư¡�� ���� ���� �ڼ��� ��� �ڼ��� �θ𺸴� �۴�.
	node->SetLeft(left->GetRight());

	// �θ� ����
	if (left->GetRight() != nil)
	{
		left->GetRight()->SetParent(node);
	}


	// �θ� Root�� ���
	if (left->GetParent() == root)
	{
		// root �� ������ �ڼ����� ����
		root = left;
		left->SetParent(nullptr);
	}
	// �θ� Root�� �ƴ� ���
	else
	{
		// ���θ� �������� �θ� ��� �־����� Ȯ��.
		if (node == node->GetParent()->GetLeft())
		{
			node->GetParent()->SetLeft(left);
		}
		else
		{
			node->GetParent()->SetRight(left);
		}
	}

	// ���� �ڼ��� ������ �ڽ����� �θ� ��� ���
	left->SetRight(node);

	// �θ��� �θ� ���θ�� ����
	left->SetParent(node->GetParent());

	// �θ��� �θ� ���� �ڼ����� ����.
	node->SetParent(left);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
	// Ż�� ����.
	if (node == nil)
	{
		return;
	}

	// ��� ������ �����̸� blackCount ����.
	if (node->GetColor() == Color::Black)
	{
		++blackCount;
	}

	// �θ� ǥ�� ���ڿ� ����.
	int parentData = 0;
	const char* position = "Root";

	// �θ� ��尡 �ִ��� Ȯ��.
	if (node->GetParent())
	{
		// �θ� ����� ������ ����.
		parentData = node->GetParent()->GetData();

		// �θ� ���κ��� ���� ����� ��ġ ����.
		if (node == node->GetParent()->GetLeft())
		{
			position = "Left";
		}
		else
		{
			position = "Right";
		}
	}

	// ������ �� ����� ���� ���ڿ�.
	char blackCountString[50] = { };

	// �ڼ��� ������ ��������� ������ ��� �� ����.
	if (node->GetLeft() == nil && node->GetRight() == nil)
	{
		sprintf_s(blackCountString, "------ %d", blackCount);
	}

	// Depth ���.
	for (int ix = 0; ix < depth; ++ix)
	{
		std::cout << "  ";
	}

	// ��� ���� ���� �ܼ� ����.
	if (node->GetColor() == Color::Red)
	{
		SetTextColor(TextColor::Red);
	}
	else
	{
		SetTextColor(TextColor::White);
	}

	// ���� ��� �� ���.
	std::cout
		<< node->GetData() << " "
		<< node->GetColorString() << " ["
		<< position << ", "
		<< parentData << "] "
		<< blackCountString << "\n";

	// ��带 ����� �ڿ��� �ܼ� �������.
	SetTextColor(TextColor::White);

	// ���� ��� ���.
	PrintRecursive(node->GetLeft(), depth + 1, blackCount);
	PrintRecursive(node->GetRight(), depth + 1, blackCount);

}
void RedBlackTree::DestroyRecursive(Node* node)
{
    // ��� Ż�� ����.
    if (node == nil)
    {
        return;
    }

    // �ڽ��� �ִ� ���.
    DestroyRecursive(node->GetLeft());
    DestroyRecursive(node->GetRight());

    // ��� ����.
    SafeDelete(node);
}

void SetTextColor(TextColor color)
{
	// �ܼ� ���� ����.
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}