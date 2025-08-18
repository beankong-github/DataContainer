#include "HashTable.h"

// �ؽ� �Լ�(Hash Function)
// �Ķ���ͷ� ���޹��� Ű�� Ȱ���ؼ� �ؽ�(����)�� ����
int GenerateKey(const std::string& keyString)
{
	// ������ Ű ����
	int key = 0;
	for (int ix = 0; ix < (int)keyString.length(); ++ix)
	{
		//key += keyString[ix] * (ix + 1);

		//  Horner's method
		key += key * 31 + keyString[ix];
	}

	// ���� ������ ��ȯ
	// �ؽ� ���̺� ������ ���ؼ��� Ű ���� �ε����� ��ȯ�Ǿ�� �ϴµ�,
	// ������� ������ �Ǳ� �����̴�. (�����÷ο� ���->�ֻ��� ��Ʈ 1�� �����Ǹ� ����)
	return key < 0 ? -key : key;

}

 HashTable::HashTable()
{
}

 HashTable::~HashTable()
{
}

 void HashTable::Add(const std::string& key, const std::string& value)
{
	 // Ű ����
	 int keyValue = GenerateKey(key);
	
	 // ��Ŷ �ε����� ��ȯ
	 int bucketIndex = keyValue % bucketCount;

	 // ������ ���� ����Ʈ ��������
	 LinkedList<Entry>& list = table[bucketIndex];

	 // Ű�� ���� �� ����ұ��? ������?
	 // STL�� ��� unordered_map -> �ߺ� ����� / unordered_multimap->�ߺ� ���
	 for (int ix = 0; ix < list.Count(); ++ix)
	 {
		 // Ű�� ������ ������� �ʴ´�,
		 if (list[ix]->data.key == key)
		 {
			 std::cout << "�̹� ������ Ű�� ���� �����Ͱ� ����Ǿ� �ֽ��ϴ�.���� ���� �����˴ϴ�.\n";
			 // ���� �����͸� �����Ѵ�.
			 list.Delete(list[ix]->data);
		 }
	 }
	
	 // �ؽ����̺� �� �߰�
	 list.PushLast(Entry(key, value));

 }

 void HashTable::Delete(const std::string& key)
{
	 // ���� ������ 2�ܰ��� ���� ����
	 // 1. ã��
	 int keyValue = GenerateKey(key);

	 // ��Ŷ �ε���
	 int bucketIndex = keyValue % bucketCount;

	 // ����Ʈ ��������
	 LinkedList<Entry>& list = table[bucketIndex];

	 // 2. ������ Ű ���� ���� ������ �˻�
	 for (int ix = 0; ix < list.Count(); ++ix)
	 {
		 // Ű�� ������ ������� �ʴ´�,
		 if (list[ix]->data.key == key)
		 {
			 // ���� �����͸� �����Ѵ�.
			 list.Delete(list[ix]->data);
			 std::cout << "���� �Ϸ�.\n";
			 return;
		 }
	 }

	 //���� ����
	 std::cout << "������ �����͸� ã�� ���߽��ϴ�.\n";
 }

 bool HashTable::Find(const std::string& key, Entry& outValue)
{

	 // ã��
	 int keyValue = GenerateKey(key);

	 // ��Ŷ �ε���
	 int bucketIndex = keyValue % bucketCount;

	 // ����Ʈ ��������
	 LinkedList<Entry>& list = table[bucketIndex];

	 // �˻��� �ʿ䰡 �ִ��� Ȯ��? 
	 // ����� �����Ͱ� ���� ���
	 if (list.Count() == 0)
	 {
		 std::cout << "���� : �� ���̺�.\n";
		 return false;
	 }

	 // �˻�
	 for (int ix = 0; ix < (int)list.Count(); ++ix)
	 {
		 // ���� Ű�� ���� �����͸� ã������
		 if (list[ix]->data.key == key)
		 {
			 outValue = list[ix]->data;
			 return true;
		 }
	 }

	 std::cout << "������ �����͸� ã�� ���߽��ϴ�.\n";
	 return false;;
}

 void HashTable::Print() const
{
	 for (int ix = 0; ix < bucketCount; ++ix)
	 {
		 LinkedList<HashTable::Entry> list = table[ix];
		 // ����Ʈ�� ��������� ���� ����Ʈ��
		 if (table[ix].Count() == 0)
		 {
			 continue;
		 }

		 for (int jx = 0; jx < (int)list.Count(); ++jx)
		 {
			 std::cout
				 << "Ű : " << list[jx]->data.key
				 << " / �� : " << list[jx]->data.value
				 << "\n";
		 }
	 }
}

 bool HashTable::IsEmpty() const
 {
	 int totalCount = 0;

	 for (int ix = 0; ix < bucketCount; ++ix)
	 {
		 totalCount += (int)table[ix].Count();
	 }

	 return totalCount == 0;
 }