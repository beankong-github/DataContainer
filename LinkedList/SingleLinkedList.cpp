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
		// 다음 노드로 이동
		tail = current;
		current = current->next;

		// 현재 노드 삭제
		delete tail;
		tail = nullptr;

		// 디버깅 목적
		--count;
	}
	

}

void SingleLinkedList::AddToHead(int newData)
{
	Node* newNode = new Node(newData);

	// 헤드가 비어 있는 경우 새 노드가 헤드가 된다.
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	// 헤드가 있을 경우 새 노드가 헤드 노드 앞으로 온 뒤,
	// 헤드 포인터로 새 노드를 가리킨다.
	newNode->next = head;
	head = newNode;
	++count;
}

void SingleLinkedList::Insert(int newData)
{
	// head가 비어있는 경우 Head로 추가한다.
	if (head == nullptr)
	{
		AddToHead(newData);
		return;
	}

	Node* current = head;
	Node* trail = nullptr;

	// next 노드가 null일 때까지 검색
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
		std::cout << "리스트가 비어 있어서 삭제가 불가능";
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

		// 다음 노드로 이동
		trail = current;
		current = current->next;
	}

	// 리스트에 삭제하려는 데이터 없음
	if (current == nullptr)
	{
		std::cout << "Data : " << data << "를 찾지 못했습니다.\n";
		return;
	}

	// 검색에 성공한 경우
	// 1. current가 head 인 경우
	if (current == head)
	{
		head = head->next;
	}
	// 2. head가 아닌 경우
	else
	{
		trail->next = current->next;
	}
	delete current;
	--count;
}

void SingleLinkedList::Print(const Node* head)
{	
	// 모든 노드를 출력한다.

	// head 노드부터 순회
	const Node* current = head;

	// 현재 노드가 null 일 때까지 반복 (모든 노드 방문)
	while (current != nullptr)
	{
		// 현재 노드 데이터 출력
		std::cout << *current << " ";
		// 다음 노드로 이동
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
	// List가 비어있거나, 하나 뿐이라면 소트를 진행하지 않는다.
	if (head == nullptr || head->next == nullptr)
		return head;

	Node* mid = SplitList(head);			// 리스트의 중앙노드
	Node* left = MergeSort(head);		// head ~ mid-1
	Node* right = MergeSort(mid);		// mid ~ tail
	
	// 나뉜 리스트를 정렬하여 합친 리스트의 head를 반환한다.
	return MergeList(left, right);
}

Node* SingleLinkedList::SplitList(Node* head)
{
	// 입력받은 리스트가 비어있거나 하나밖에 없다면
	// 리스트를 둘로 나눌 수 없다.
	if (head == nullptr || head->next == nullptr)
		return head;

	Node* slow = head;		// 리스트의 중앙값 검색용
	Node* fast = head;			// 리스트의 마지막 체크용
	Node* prev = nullptr;		// 리스트의 중앙 이전 값

	while (fast != nullptr && fast->next != nullptr)
	{
		prev = slow;	
		slow = slow->next; // slow는 1노드씩 전진 

		fast = fast->next->next;	// fast는 2노드씩 전진
	}

	// 리스트를 반으로 쪼갠다.
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
		// trail 뒤로 a 혹은 b 중 더 작은 노드를 연결한다.
		// 연결 한 뒤에 자신을 다음 노드로 갱신한다.
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

		// trail 연결 리스트의 가장 마지막(다음 노드가 연결될 곳)을 가리킨다.
		trail = trail->next;
	}
	
	//a리스트나 b리스트에 남은 노드가 있다면 연결한다.
	trail->next = a != nullptr ? a : b;

	Print(dummyNode.next);

	// 더미 헤드의 다음 노드를 전달한다.
	return dummyNode.next;
}

