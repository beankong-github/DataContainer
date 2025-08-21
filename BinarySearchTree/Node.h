#pragma once


template<typename T>
class Node
{

public:
	Node(const T& data = T(), Node<T>* parent = nullptr)
		:data(data), parent(parent)
	{
	}


	T GetData() const { return data; };
	void SetData(const T& newData) { data = newData; }

	Node<T>* GetParent() const{ return parent; };
	void SetParent(Node<T>* newParent)  { parent = newParent; };

	Node<T>* GetLeft() const{ return left; };
	void SetLeft(Node<T>* newLeft)  { left = newLeft; };

	Node<T>* GetRight() const{ return right; };
	void SetRight(Node<T>* newRight)  { left = newRight; };

private:
	T data;
	Node<T>* parent = nullptr;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};