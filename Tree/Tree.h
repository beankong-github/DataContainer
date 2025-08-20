#pragma once
#include "List.h"
#include "Node.h"


template<typename T>
class Tree
{
public:
	Tree(const T& data)
		: root(new Node<T>(data))
	{
	}

	~Tree()
	{
		// TODO : �ڼ��� ��� �����ϴ� �Լ� ���� �� ȣ�� �ؾ� �Ѵ�.
		List<Node<T>*>& children = root->GetChildren();
		while (children.Size() > 0)
		{
			root->RemoveChild(children[0]);
		}
		
		// ��Ʈ ����
		delete root;
		root = nullptr;

	}

	void AddChild(const T& parentData, const T& childData)
	{
		// 1. �˻�
		Node<T>* outParent = nullptr;
		if (Find(parentData, outParent))
		{
			outParent->AddChild(childData);
			return;
		}

		// �θ� ��� �˻� ����
		std::cout <<  parentData <<" ���� ���� �θ� ��� �˻� ����\n" ;
	}
	
	bool Remove(const T& data)
	{
		// TODO :: ������ ��带 �˻��ϰ�, �ڼ� ������ �����ϴ� �Լ� �ۼ� �� ȣ��

		Node<T>* outNode = nullptr;
		
		// �˻� ����
		if (!Find(data, outNode))
		{
			std::cout << "������ ��带 ã�� ���߽��ϴ�.\n";
			return false;
		}

		// �˻� ����
		// ����� �� 1 : ������ ��尡 ��Ʈ ����� ���
		if (outNode == root)
		{
			std::cout << "��Ʈ ��� ���� �Ұ�\n";
			return false;
		}
		// ����� �� 2
		Node<T>* parent = outNode->GetParent();
		parent->RemoveChild(outNode);

		return true;
	}


	// �����ͷ� Ư�� ��带 �˻�
	bool Find(const T& data, Node<T>*& outNode)
	{
		return FindRecursive(data, root, outNode);
	}

	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
	{
		// ��� �Լ� ���� ����
		if (node == nullptr)
		{
			outNode = nullptr;
			return false;
		}

		// �˻� ����
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		// �ڼ��� ��������� �˻�
		List<Node<T>*>& children = node->GetChildren();
		int count = children.Size();
		for (int ix = 0; ix < count; ++ix)
		{
			// �ڼ� �˻� ����
			Node<T>* child = children[ix];
			bool result = FindRecursive(data, child, outNode);
			if (result)
			{
				return true;
			}
		}

		// �˻� ����
		outNode = nullptr;
		return false;

	}

	// ���� ��ȸ
	void PreorderTraverse()
	{
		PreorderTraverseRecursive(root);
	}

	// ���� ��ȸ ���
	// node : �湮�� ���� ���
	// depth :  ����� �� �θ�-�ڼ� ���п� 
	void  PreorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// ��� �Լ� ���� ����
		if (!node)
		{
			return;
		}

		// �X�� ���
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "    ";
		}

		// �θ��� �湮
		std::cout << node->GetData() << "\n";
		// �ڼ� ��� �湮
		List<Node<T>*>& children = node->GetChildren();
		if (children.Size() == 0)
			return;

		for (int ix = 0; ix < children.Size(); ++ix)
		{
			Node<T>* child = children[ix];
			PreorderTraverseRecursive(child, depth + 1);
		}
	}




private:
	Node<T>* root = nullptr;
};