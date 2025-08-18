#pragma once
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Pair.h"

class HashTable
{
	// Ÿ�� ������ (Type Alias)
private:
	using Entry = TPair<std::string, std::string>;

public:
	HashTable();
	~HashTable();

	// �߰�
	void Add(const std::string& key, const std::string& value);

	// ����
	void Delete(const std::string& key);
	
	// �˻�
	bool Find(const std::string& key, Entry& outValue);

	// ���
	void Print() const;

	// ������� Ȯ��
	bool IsEmpty() const;

private:
	// ��Ŷ(Bucket) ����
	static const int bucketCount = 19;	 // �ؽ� �浹�� �����ϱ� ���ؼ��� ��Ŷ�� ũ�Ⱑ �Ҽ��� ���� �����ϴ�.
	// 2�� �ڷᱸ�� Ȱ�� (ü�̴�)
	LinkedList<Entry> table[bucketCount] = {};

};
