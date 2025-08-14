#include "SingleLinkedList.h"

SingleLinkedList::SingleLinkedList()
{
}

SingleLinkedList::~SingleLinkedList()
{
	Node* current = head;
	Node* tail = nullptr;

	while (current != nullptr)
	{
		// ���� ���� �̵�
		tail = current;
		current = current->next;

		// ���� ��� ����
		delete tail;
		tail = nullptr;

		// ����� ����
		--count;
	}
	

}

void SingleLinkedList::AddToHead(int newData)
{
	Node* newNode = new Node(newData);

	// ��尡 ��� �ִ� ��� �� ��尡 ��尡 �ȴ�.
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	// ��尡 ���� ��� �� ��尡 ��� ��� ������ �� ��,
	// ��� �����ͷ� �� ��带 ����Ų��.
	newNode->next = head;
	head = newNode;
	++count;
}

void SingleLinkedList::Insert(int newData)
{
	// head�� ����ִ� ��� Head�� �߰��Ѵ�.
	if (head == nullptr)
	{
		AddToHead(newData);
		return;
	}

	Node* current = head;
	Node* trail = nullptr;

	// next ��尡 null�� ������ �˻�
	while (current != nullptr)
	{
		trail = current;
		current = current->next;
	}

	Node* newNode = new Node(newData);
	trail->next = newNode;
	++count;
}

void SingleLinkedList::Delete(int data)
{
	if (head == nullptr)
	{
		std::cout << "����Ʈ�� ��� �־ ������ �Ұ���";
		return;
	}

	Node* current = head;
	Node* trail = nullptr;

	while (current != nullptr)
	{
		if (current->data == data)
		{
			break;
		}

		// ���� ���� �̵�
		trail = current;
		current = current->next;
	}

	// ����Ʈ�� �����Ϸ��� ������ ����
	if (current == nullptr)
	{
		std::cout << "Data : " << data << "�� ã�� ���߽��ϴ�.\n";
		return;
	}

	// �˻��� ������ ���
	// 1. current�� head �� ���
	if (current == head)
	{
		head = head->next;
	}
	// 2. head�� �ƴ� ���
	else
	{
		trail->next = current->next;
	}
	delete current;
	--count;
}

void SingleLinkedList::Print(const Node* head)
{	
	// ��� ��带 ����Ѵ�.

	// head ������ ��ȸ
	const Node* current = head;

	// ���� ��尡 null �� ������ �ݺ� (��� ��� �湮)
	while (current != nullptr)
	{
		// ���� ��� ������ ���
		std::cout << *current << " ";
		// ���� ���� �̵�
		current = current->next;
	}

	std::cout << '\n';
}

void SingleLinkedList::Sort()
{
	head = MergeSort(head);
}

const Node* SingleLinkedList::GetHead() const
{
	return head;
}

Node* SingleLinkedList::MergeSort(Node* head)
{
	// List�� ����ְų�, �ϳ� ���̶�� ��Ʈ�� �������� �ʴ´�.
	if (head == nullptr || head->next == nullptr)
		return head;

	Node* mid = SplitList(head);			// ����Ʈ�� �߾ӳ��
	Node* left = MergeSort(head);		// head ~ mid-1
	Node* right = MergeSort(mid);		// mid ~ tail
	
	// ���� ����Ʈ�� �����Ͽ� ��ģ ����Ʈ�� head�� ��ȯ�Ѵ�.
	return MergeList(left, right);
}

Node* SingleLinkedList::SplitList(Node* head)
{
	// �Է¹��� ����Ʈ�� ����ְų� �ϳ��ۿ� ���ٸ�
	// ����Ʈ�� �ѷ� ���� �� ����.
	if (head == nullptr || head->next == nullptr)
		return head;

	Node* slow = head;		// ����Ʈ�� �߾Ӱ� �˻���
	Node* fast = head;			// ����Ʈ�� ������ üũ��
	Node* prev = nullptr;		// ����Ʈ�� �߾� ���� ��

	while (fast != nullptr && fast->next != nullptr)
	{
		prev = slow;	
		slow = slow->next; // slow�� 1��徿 ���� 

		fast = fast->next->next;	// fast�� 2��徿 ����
	}

	// ����Ʈ�� ������ �ɰ���.
	// [head] - [...] - [prev] \ [slow] - [...]
	prev->next = nullptr;		
	return slow;
}

Node* SingleLinkedList::MergeList(Node* a, Node* b)
{
	Node dummyNode;
	Node* trail = &dummyNode;

	while (a != nullptr && b != nullptr)
	{
		// trail �ڷ� a Ȥ�� b �� �� ���� ��带 �����Ѵ�.
		// ���� �� �ڿ� �ڽ��� ���� ���� �����Ѵ�.
		if (a->data <= b->data)
		{
			trail->next = a;
			a = a->next;
		}
		else
		{
			trail->next = b;
			b = b->next;
		}

		// trail ���� ����Ʈ�� ���� ������(���� ��尡 ����� ��)�� ����Ų��.
		trail = trail->next;
	}
	
	//a����Ʈ�� b����Ʈ�� ���� ��尡 �ִٸ� �����Ѵ�.
	trail->next = a != nullptr ? a : b;

	Print(dummyNode.next);

	// ���� ����� ���� ��带 �����Ѵ�.
	return dummyNode.next;
}

