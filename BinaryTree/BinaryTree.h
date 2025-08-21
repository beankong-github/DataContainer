#pragma once
#include "Node.h"
#include <iostream>

template<typename T>
class BinaryTree
{
	BinaryTree()
        :root(nullptr)
    {}

	~BinaryTree();

    void AddLeftChild(const T& parentData, const T& childData)
    {
        Node<T>* parent = nullptr;
        bool result = Find(parentData, parent);

        if (result)
        {
            parent->AddLeftChild(childData);
            return;
        }

        // �˻� ����.
        std::cout << "�߰� ����: �θ� ��带 ã�� ���߽��ϴ�.\n";
    }

    void AddRightChild(const T& parentData, const T& childData)
    {
        Node<T>* parent = nullptr;
        bool result = Find(parentData, parent);

        if (result)
        {
            parent->AddRightChild(childData);
            return;
        }

        // �˻� ����.
        std::cout << "�߰� ����: �θ� ��带 ã�� ���߽��ϴ�.\n";
    }


    bool Find(const T& data, Node<T>*& outNode)
    {
        return FindRecursive(data, root, outNode);
    }

    void PreOrderTraverse()
    {
        PreorderTraverseRecursive(root);
    }

    void DeleteNode(const T& data)
    {
        // �˻�
        Node<T>* deleteNode = nullptr;
        bool result = Find(data, deleteNode);

        // ã ������ ����
        if(result)
        {
            deleteNode->Destroy();
            return true;
        }

        // �� ã������ 
        std::cout << "���� ���� : ��带 ã�� ���߽��ϴ�.\n.";
        return false;

    }
    
private:
    bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
    {
        // ���� ����.
        if (!node)
        {
            // ��¿� null ����.
            outNode = nullptr;
            return false;
        }

        // Ȯ��.
        if (node->GetData() == data)
        {
            outNode = node;
            return true;
        }

        // ���� �ڼ����� �˻� ����.
        bool result = FindRecursive(data, node->GetLeftChild(), outNode);
        if (result)
        {
            return true;
        }

        // ������ �ڼ����� �˻� ����.
        result = FindRecursive(data, node->GetRightChild(), outNode);
        if (result)
        {
            return true;
        }

        // �˻� ����.
        outNode = nullptr;
        return false;
    }

    bool PreorderTraverseRecursive(Node<T>* node, int depth = 0)
    {
    }

private:
    Node<T>*  root;

};