#pragma once

template<typename T>
class Node
{
	template<typename T>
	friend class LinkedList;

private:
	Node()
		:data(),next(nullptr), prev(nullptr)
	{
	}

private:

	T data /*= default(T)*/;
	Node<T>* next  = nullptr;
	Node<T>* prev = nullptr ;

};