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


	// ����.
	// ��Ģ.
	// 1. �ߺ��� ���� ������� �ʴ´�.
	// 2. ��Ʈ�������� �� ����.
	// 2-1. ��Ʈ�� null�̸� �� ��带 ��Ʈ�� ����.
	// 3. ���� �߰��ϴ� ���� �� ��庸�� ������ ���� ���� Ʈ���� �� �̾.
	// 4. ���� �߰��ϴ� ���� �� ��庸�� ũ�� ������ ���� Ʈ���� �� �̾.
	bool Insert(const T& data)
	{
		// �߰��Ϸ��� �����Ͱ� �̹� �ִ��� �˻�
		Node<T>* outNode = nullptr;

		if (Find(data, outNode))
		{
			std::cout << "Error: �ߺ��� ���� �־ ��带 �߰����� �� �߽��ϴ�.";
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


	// �˻�
	bool Find(const T& data, Node<T>*& outNode) const
	{
		return FindRecursive(data, root, outNode);
	}



	bool Delete(const T& data)
	{
		// ����
		Node<T>* deleteNode = nullptr;
		if (!Find(data, deleteNode))
		{
			std::cout << "Error : ������ ��带 ã�� ���߽��ϴ�.\n";
			return false;
		}

		root = DeleteRecursive(data, root);
		return true;
	}

	// ������ȸ

	// �ּڰ� �˻�
	Node<T>* FindMinValue(Node<T>* node)
	{
		// ���� ���� �� ���
		while (node->GetLeft())
		{
			node = node->GetLeft();
		}

		return node;
	}

	// �ִ� �˻�
	Node<T>* FindMaxValue(Node<T>* node)
	{
		// ���� ���� �� ���
		while (node->GetRight())
		{
			node = node->GetRight();
		}

		return node;
	}

	void Destroy()
	{
		// ��Ʈ�� ��������� ����
		if (nullptr == root)
			return;

		DestroyRecursive(root);
	}

private:
	// ��� �˻�
	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode) const
	{
		if (node == nullptr)
		{
			outNode = nullptr;
			return false;
		}

		// �˻� ���� Ȯ��
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		// ã�� �����Ͱ� ���� ���
		if (node->GetData() > data)
		{
			// ���� ���� Ʈ���� �˻� �� ����
			return FindRecursive(data, node->GetLeft(), outNode);
		}

		// ã�� �����Ͱ� �� ū ���
		// ������ ���� Ʈ���� �˻� �� ����
		return FindRecursive(data, node->GetRight(), outNode);
	}

	// ��� ����
	Node<T>* InsertRecursive(const T& data, Node<T>* node, Node<T>* parent)
	{
		// ���� ���� (����)
		if (node == nullptr)
		{
			//����
			return new Node<T>(data, parent); 
		}

		if (node->GetData() > data)
		{
			node->SetLeft(InsertRecursive(data, node->GetLeft(), node));
		}

		// ū ��� (������ ���� Ʈ���� ����)
		else
		{
			node->SetRight(InsertRecursive(data, node->GetRight(), node));
		}

		// ���������� �˻��ϴ� ��� ��ȯ
		return node;

	}

	Node<T>* DeleteRecursive(const T& data, Node<T>* node)
	{
		// ���� ����
		if (!node)
		{
			return nullptr;
		}

		// ���� ����� �����ͺ��� ������ �����Ͱ� �� ���� ���
		if (node->GetData() > data)
		{
			node->SetLeft(DeleteRecursive(data, node->GetLeft()));
		}
		// ���� ����� �����ͺ��� ������ �����Ͱ� �� ū ���
		else if(node ->GetData() < data)
		{
			node->SetRight(DeleteRecursive(data, node->GetRigh()));
		}
		// ������ ��� ã��
		else
		{
			// ���� ó��

			// 1, �ڽ��� �� �� ���� ���
			if (node->GetLeft() && node->GetRight())
			{
				delete node;
				return nullptr;
			}

			// 2. �ڽ��� �� �� �ִ� ���
			if (node->GetLeft() && node->GetRight())
			{
				// ���� �������� ���� ū ������ ��ü
				// ������ �������� ���� ���� ������ ��ü


				// ������ �������� ���� ���� ������ ������ ����� ���� ��ü�Ѵ�
				node->SetData(FindMinValue(node->GetRight())->GetData());

				// ��ü ���ϴ� ��带 �����Ѵ�.
				node->SetRight(DeleteRecursive(node->GetData(), node->GetRight()));

			}

			// 3. �ڽ��� �ϳ��� �ִ� ���
			else
			{
				// ���ʸ� �ִ� ���
				if (node->GetLeft())
				{
					// ���� �ڼ��� ��ȯ�ϱ� ���� �ӽ� ����
					Node<T>* left = node->GetLeft();

					delete node;

					return left;
				}

				// �����ʸ� �ִ� ���
				else if (node->GetRight())
				{
					// ���� �ڼ��� ��ȯ�ϱ� ���� �ӽ� ����
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

			// �ڼյ� ��� �����ϰ� ��Ʈ �����ϵ���
		}

		Node<T>* left = node->GetLeft();
		Node<T>* right = node->GetRight();

		// �ڼ��� ������ ����
		if (left == nullptr && right == nullptr)
		{
			delete node;
			node = nullptr;
			return;
		}

		// �ڼ��� ������ �ѹ� �� ����
		DestroyRecursive(left);
		DestroyRecursive(right);

		delete node;
		node = nullptr;
	}

private:
	Node<T>* root = nullptr;
};