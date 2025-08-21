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

        // 검색 실패.
        std::cout << "추가 실패: 부모 노드를 찾지 못했습니다.\n";
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

        // 검색 실패.
        std::cout << "추가 실패: 부모 노드를 찾지 못했습니다.\n";
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
        // 검색
        Node<T>* deleteNode = nullptr;
        bool result = Find(data, deleteNode);

        // 찾 았으면 삭제
        if(result)
        {
            deleteNode->Destroy();
            return true;
        }

        // 못 찾았으면 
        std::cout << "삭제 실패 : 노드를 찾지 못했습니다.\n.";
        return false;

    }
    
private:
    bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
    {
        // 종료 조건.
        if (!node)
        {
            // 출력에 null 설정.
            outNode = nullptr;
            return false;
        }

        // 확인.
        if (node->GetData() == data)
        {
            outNode = node;
            return true;
        }

        // 왼쪽 자손으로 검색 진행.
        bool result = FindRecursive(data, node->GetLeftChild(), outNode);
        if (result)
        {
            return true;
        }

        // 오른쪽 자손으로 검색 진행.
        result = FindRecursive(data, node->GetRightChild(), outNode);
        if (result)
        {
            return true;
        }

        // 검색 실패.
        outNode = nullptr;
        return false;
    }

    bool PreorderTraverseRecursive(Node<T>* node, int depth = 0)
    {
    }

private:
    Node<T>*  root;

};