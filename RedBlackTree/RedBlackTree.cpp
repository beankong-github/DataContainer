#include "RedBlackTree.h"


Node* RedBlackTree::nil = nullptr;

// 메모리 해제 함수
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
	// 재귀적으로 모든 노드를 삭제하는 함수 작성 후 호출
	DestroyRecursive(root);

	// Nil 노드 삭제
	SafeDelete(nil);

}

bool RedBlackTree::Find(int data, Node*& outNode)
{
	if (root == nil)
		return false;

	// 재귀적으로 검색 
	return FindRecursive(data, root, outNode);
}

bool RedBlackTree::Insert(int data)
{    // 중복 여부 확인.
	Node* node = nullptr;
	if (Find(data, node))
	{
		std::cout << "Error: 이미 같은 값이 있습니다.\n";
		return false;
	}

	// 삽입 처리.

	// 트리가 비었으면 루트에 추가.
	if (root == nil)
	{
		// 루트는 블랙.
		root = CreateNode(data, Color::Black);
		return true;
	}

	// 재귀적으로 삽입할 위치 검색 후 삽입 처리.
	Node* newNode = CreateNode(data, Color::Red);
	InsertRecursive(root, newNode);

	// Todo: 아래 로직 필요한지 확인할 것.
	// 삽입 후 노드 정리.
	newNode->SetColor(Color::Red);
	newNode->SetLeft(nil);
	newNode->SetRight(nil);

	// 삽입 후 정리.
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
	// 말단까지 검색했는데 찾는데 이터가 없었다.
	// => 실패
	if (node == nil)
	{
		outNode = nullptr;
		return false;
	}

	// 데이터를 찾은 경우
	if (node->GetData() == data)
	{
		outNode = node;
		return true;
	}

	// 찾는 데이터보다 노드가 작은 경우
	if (node->GetData() < data)
	{
		// 오른쪽 탐색
		return FindRecursive(data, node->GetRight(), outNode);
	}
	// 찾는 데이터보다 노드가 더 큰 경우
	else
	{
		// 왼쪽 탐색
		return FindRecursive(data, node->GetLeft(), outNode);
	}
}

void RedBlackTree::InsertRecursive(Node* node, Node* newNode)
{
	// 새 노드 데이터가 더 작으면 왼쪽 하위 트리에 삽입
	if (node->GetData() > newNode->GetData())
	{
		// 왼쪽 하위 자손이 없으면, 왼쪽 자손으로 추가
		if (node->GetLeft() == nil)
		{
			node->SetLeft(newNode);
			newNode->SetParent(node);
			return;
		}

		InsertRecursive(node->GetLeft(), newNode);
	}
	//	새 노드 데이터가 더 크면 왼쪽 하위 트리에 삽입	
	else if (node->GetData() < newNode->GetData())
	{
		// 오른쪽 하위 자손이 없으면, 오른쪽 자손으로 추가
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
		//부모와 삼촌을 Black, 할아버지를 Red로 변경 후, 할아버지 기준으로 다시 검사
		// 삼촌 가져오기 -> 부모의 위치에 따라 달라진다. (ex :부모가 left면 삼촌은 right)
		// 부모 왼쪽 - 삼촌 오른쪽
		if (newNode->GetParent() == newNode->GetParent()->GetParent()->GetLeft())
		{
			Node* uncle = newNode->GetParent()->GetParent()->GetRight();

			// case 1  : 삼촌 빨강
			if (uncle->GetColor() == Color::Red)
			{
				// 부모 삼촌을 검정색
				newNode->GetParent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);

				// 할아버지를 빨간색으로 변경
				newNode->GetParent()->GetParent()->SetColor(Color::Red);

				// 기준을 할아버지로 변경
				newNode = newNode->GetParent()->GetParent();
				continue;

			}

			//삼촌이 검정
			// 부모를 Black, 할아버지를 Red로 변경 후, 할아버지를 기준으로 회전

			// case2 : 부모 왼쪽,  내가 오른쪽이면 지그재그 형태
			// => 회전으로 조부모-부모-나 일직선으로 만들어야 한다.
			if (newNode == newNode->GetParent()->GetLeft())
			{
				// 우회전 
				// 내가 부모의 왼에 있다는 건 내가 더 작다는 것이므로
				// 우회전해야 조부모 오른쪽->나의 오른쪽->부모로 1자 구조가 가능하다.
				newNode = newNode->GetParent();
				RotateToLeft(newNode);

			}

			// case3. 부모와 나의 위치가 일직선일 때
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);

			// 우회전
			RotateToRight(newNode->GetParent()->GetParent());

		}
		// 부모 오른쪽-삼촌 왼쪽
		else
		{
			Node* uncle = newNode->GetParent()->GetParent()->GetLeft();

			// case 1  : 삼촌 빨강
			if (uncle->GetColor() == Color::Red)
			{
				// 부모 삼촌을 검정색
				newNode->GetParent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);

				// 할아버지를 빨간색으로 변경
				newNode->GetParent()->GetParent()->SetColor(Color::Red);

				// 기준을 할아버지로 변경
				newNode = newNode->GetParent()->GetParent();
				continue;

			}

			//삼촌이 검정
			// 부모를 Black, 할아버지를 Red로 변경 후, 할아버지를 기준으로 회전

			// case2 : 부모 오른쪽,  내가 왼쪽이면 지그재그 형태
			// => 회전으로 조부모-부모-나 일직선으로 만들어야 한다.
			if (newNode == newNode->GetParent()->GetLeft())
			{
				// 우회전 
				// 내가 부모의 왼쪽에 있다는 건 내가 더 작다는 것이므로
				// 우회전해야 조부모 오른쪽->나의 오른쪽->부모로 1자 구조가 가능하다.
				newNode = newNode->GetParent();
				RotateToRight(newNode);

			}

			// case3. 부모와 나의 위치가 일직선일 때
			//
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);

			//좌회전
			RotateToLeft(newNode->GetParent()->GetParent());
		}
	}

	// 루트는블랙으로 정리
	root->SetColor(Color::Black);
}

void RedBlackTree::RotateToLeft(Node* node)
{
	// 오른쪽 자손 노드
	Node* right = node->GetRight();

	//오른쪽 자손의 왼쪽 자손 노드를 부모의 오른쪽 자손으로 등록
	// 이진 탐색 트리 특징에 의해 오른쪽 자손의 모든 자손은 부모보다 크다
	node->SetRight(right->GetLeft());

	// 부모 정리
	if (right->GetLeft() != nil)
	{
		right->GetLeft()->SetParent(node);
	}


	// 부모가 Root인 경우
	if (right->GetParent() == root)
	{
		// root 를 오른쪽 자손으로 변경
		root = right;
		right->SetParent(nullptr);
	}
	else
	{
		// 조부모 기준으로 부모가 어디에 있었는지 확인.
		if (node == node->GetParent()->GetLeft())
		{
			node->GetParent()->SetLeft(right);
		}
		else
		{
			node->GetParent()->SetRight(right);
		}
	}

	// 오른쪽 자손의 왼쪽 자슨으로 부모 노드 등록
	right->SetLeft(node);

	// 부모의 부모를 오른쪽 자손으로 설정
	right->SetParent(node->GetParent());

	// 부모의 부모를 오른쪽 자손으로 설정.
	node->SetParent(right);

}


// 회전: 부모와 자손의 위치를 바꾸는 기능.
// 우회전 -> 오른쪽으로 회전.왼쪽 자손과 부모의 위치를 교환.
void RedBlackTree::RotateToRight(Node* node)
{

	// 오른쪽 자손 노드
	Node* left = node->GetLeft();

	// 왼쪽 자손의 오른쪽 자손 노드를 부모의 왼쪽 자손으로 등록
	// 이진 탐색 트리 특징에 의해 왼쪽 자손의 모든 자손은 부모보다 작다.
	node->SetLeft(left->GetRight());

	// 부모 정리
	if (left->GetRight() != nil)
	{
		left->GetRight()->SetParent(node);
	}


	// 부모가 Root인 경우
	if (left->GetParent() == root)
	{
		// root 를 오른쪽 자손으로 변경
		root = left;
		left->SetParent(nullptr);
	}
	// 부모가 Root가 아닌 경우
	else
	{
		// 조부모 기준으로 부모가 어디에 있었는지 확인.
		if (node == node->GetParent()->GetLeft())
		{
			node->GetParent()->SetLeft(left);
		}
		else
		{
			node->GetParent()->SetRight(left);
		}
	}

	// 왼쪽 자손의 오른쪽 자슨으로 부모 노드 등록
	left->SetRight(node);

	// 부모의 부모를 조부모로 설정
	left->SetParent(node->GetParent());

	// 부모의 부모를 왼쪽 자손으로 설정.
	node->SetParent(left);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
	// 탈출 조건.
	if (node == nil)
	{
		return;
	}

	// 노드 색상이 검정이면 blackCount 증가.
	if (node->GetColor() == Color::Black)
	{
		++blackCount;
	}

	// 부모 표기 문자열 설정.
	int parentData = 0;
	const char* position = "Root";

	// 부모 노드가 있는지 확인.
	if (node->GetParent())
	{
		// 부모 노드의 데이터 저장.
		parentData = node->GetParent()->GetData();

		// 부모 노드로부터 현재 노드의 위치 설정.
		if (node == node->GetParent()->GetLeft())
		{
			position = "Left";
		}
		else
		{
			position = "Right";
		}
	}

	// 검은색 수 출력을 위한 문자열.
	char blackCountString[50] = { };

	// 자손이 없으면 현재까지의 검은색 노드 수 설정.
	if (node->GetLeft() == nil && node->GetRight() == nil)
	{
		sprintf_s(blackCountString, "------ %d", blackCount);
	}

	// Depth 출력.
	for (int ix = 0; ix < depth; ++ix)
	{
		std::cout << "  ";
	}

	// 노드 색상에 따른 콘솔 설정.
	if (node->GetColor() == Color::Red)
	{
		SetTextColor(TextColor::Red);
	}
	else
	{
		SetTextColor(TextColor::White);
	}

	// 현재 노드 값 출력.
	std::cout
		<< node->GetData() << " "
		<< node->GetColorString() << " ["
		<< position << ", "
		<< parentData << "] "
		<< blackCountString << "\n";

	// 노드를 출력한 뒤에는 콘솔 원래대로.
	SetTextColor(TextColor::White);

	// 하위 노드 출력.
	PrintRecursive(node->GetLeft(), depth + 1, blackCount);
	PrintRecursive(node->GetRight(), depth + 1, blackCount);

}
void RedBlackTree::DestroyRecursive(Node* node)
{
    // 재귀 탈출 조건.
    if (node == nil)
    {
        return;
    }

    // 자식이 있는 경우.
    DestroyRecursive(node->GetLeft());
    DestroyRecursive(node->GetRight());

    // 노드 삭제.
    SafeDelete(node);
}

void SetTextColor(TextColor color)
{
	// 콘솔 색상 설정.
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}