#pragma once
#include <iostream>

#include "Node.h"

template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() = default;
	~BinarySearchTree()
	{
		Destroy();
	}


	// 삽입.
	// 규칙.
	// 1. 중복된 값은 허용하지 않는다.
	// 2. 루트에서부터 비교 시작.
	// 2-1. 루트가 null이면 새 노드를 루트로 지정.
	// 3. 새로 추가하는 값이 비교 노드보다 작으면 왼쪽 하위 트리로 비교 이어감.
	// 4. 새로 추가하는 값이 비교 노드보다 크면 오른쪽 하위 트리로 비교 이어감.
	bool Insert(const T& data)
	{
		// 추가하려는 데이터가 이미 있는지 검색
		Node<T>* outNode = nullptr;

		if (Find(data, outNode))
		{
			std::cout << "Error: 중복된 값이 있어서 노드를 추가하지 못 했습니다.";
			return false;
		}

		if (root == nullptr)
		{
			root = new Node<T>(data);
			return true;
		}

		root = InsertRecursive(data, root, nullptr);
		return true;
	}


	// 검색
	bool Find(const T& data, Node<T>*& outNode) const
	{
		return FindRecursive(data, root, outNode);
	}



	bool Delete(const T& data)
	{
		// 삭제
		Node<T>* deleteNode = nullptr;
		if (!Find(data, deleteNode))
		{
			std::cout << "Error : 삭제할 노드를 찾지 못했습니다.\n";
			return false;
		}

		root = DeleteRecursive(data, root);
		return true;
	}

	// 중위순회

	// 최솟값 검색
	Node<T>* FindMinValue(Node<T>* node)
	{
		// 가장 왼쪽 끝 노드
		while (node->GetLeft())
		{
			node = node->GetLeft();
		}

		return node;
	}

	// 최댓값 검색
	Node<T>* FindMaxValue(Node<T>* node)
	{
		// 가장 왼쪽 끝 노드
		while (node->GetRight())
		{
			node = node->GetRight();
		}

		return node;
	}

	void Destroy()
	{
		// 루트가 비어있으면 종료
		if (nullptr == root)
			return;

		DestroyRecursive(root);
	}

private:
	// 재귀 검색
	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode) const
	{
		if (node == nullptr)
		{
			outNode = nullptr;
			return false;
		}

		// 검색 성공 확인
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		// 찾는 데이터가 작은 경우
		if (node->GetData() > data)
		{
			// 왼쪽 하위 트리로 검색 더 진행
			return FindRecursive(data, node->GetLeft(), outNode);
		}

		// 찾는 데이터가 더 큰 경우
		// 오른쪽 하위 트리로 검색 더 진행
		return FindRecursive(data, node->GetRight(), outNode);
	}

	// 재귀 삽입
	Node<T>* InsertRecursive(const T& data, Node<T>* node, Node<T>* parent)
	{
		// 종료 조건 (삽입)
		if (node == nullptr)
		{
			//삽입
			return new Node<T>(data, parent); 
		}

		if (node->GetData() > data)
		{
			node->SetLeft(InsertRecursive(data, node->GetLeft(), node));
		}

		// 큰 경우 (오른쪽 하위 트리에 삽입)
		else
		{
			node->SetRight(InsertRecursive(data, node->GetRight(), node));
		}

		// 마지막으로 검색하는 노드 반환
		return node;

	}

	Node<T>* DeleteRecursive(const T& data, Node<T>* node)
	{
		// 종료 조건
		if (!node)
		{
			return nullptr;
		}

		// 현재 노드의 데이터보다 삭제할 데이터가 더 작은 경우
		if (node->GetData() > data)
		{
			node->SetLeft(DeleteRecursive(data, node->GetLeft()));
		}
		// 현재 노드의 데이터보다 삭제할 데이터가 더 큰 경우
		else if(node ->GetData() < data)
		{
			node->SetRight(DeleteRecursive(data, node->GetRigh()));
		}
		// 삭제할 노드 찾음
		else
		{
			// 삭제 처리

			// 1, 자식이 둘 다 없는 경우
			if (node->GetLeft() && node->GetRight())
			{
				delete node;
				return nullptr;
			}

			// 2. 자식이 둘 다 있는 경우
			if (node->GetLeft() && node->GetRight())
			{
				// 왼쪽 하위에서 가장 큰 값으로 대체
				// 오른쪽 하위에서 가장 작은 값으로 대체


				// 오른쪽 하위에서 가장 작은 값으로 삭제할 노드의 값을 대체한다
				node->SetData(FindMinValue(node->GetRight())->GetData());

				// 대체 당하는 노드를 삭제한다.
				node->SetRight(DeleteRecursive(node->GetData(), node->GetRight()));

			}

			// 3. 자식이 하나만 있는 경우
			else
			{
				// 왼쪽만 있는 경우
				if (node->GetLeft())
				{
					// 왼쪽 자손을 반환하기 위해 임시 저장
					Node<T>* left = node->GetLeft();

					delete node;

					return left;
				}

				// 오른쪽만 있는 경우
				else if (node->GetRight())
				{
					// 왼쪽 자손을 반환하기 위해 임시 저장
					Node<T>* right = node->GetRight();

					delete node;

					return right;
				}
			}

		}
		return node;
	}

	void DestroyRecursive(Node<T>* node)
	{
		if (node == nullptr)
		{
			return;

			// 자손도 모두 제거하고 루트 제거하도록
		}

		Node<T>* left = node->GetLeft();
		Node<T>* right = node->GetRight();

		// 자손이 없으면 삭제
		if (left == nullptr && right == nullptr)
		{
			delete node;
			node = nullptr;
			return;
		}

		// 자손이 있으면 한번 더 진행
		DestroyRecursive(left);
		DestroyRecursive(right);

		delete node;
		node = nullptr;
	}

private:
	Node<T>* root = nullptr;
};