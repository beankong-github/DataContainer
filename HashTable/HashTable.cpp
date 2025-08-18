#include "HashTable.h"

// 해시 함수(Hash Function)
// 파라미터로 전달받은 키를 활용해서 해시(숫자)를 생성
int GenerateKey(const std::string& keyString)
{
	// 생성될 키 변수
	int key = 0;
	for (int ix = 0; ix < (int)keyString.length(); ++ix)
	{
		//key += keyString[ix] * (ix + 1);

		//  Horner's method
		key += key * 31 + keyString[ix];
	}

	// 절대 값으로 변환
	// 해시 테이블에 저장을 위해서는 키 값이 인덱스로 변환되어야 하는데,
	// 음수라면 문제가 되기 때문이다. (오버플로우 고려->최상위 비트 1로 설정되면 음수)
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
	 // 키 생성
	 int keyValue = GenerateKey(key);
	
	 // 버킷 인덱스로 변환
	 int bucketIndex = keyValue % bucketCount;

	 // 저장할 연결 리스트 가져오기
	 LinkedList<Entry>& list = table[bucketIndex];

	 // 키가 같은 걸 허용할까요? 말까유?
	 // STL의 경우 unordered_map -> 중복 비허용 / unordered_multimap->중복 허용
	 for (int ix = 0; ix < list.Count(); ++ix)
	 {
		 // 키가 같은걸 허용하지 않는다,
		 if (list[ix]->data.key == key)
		 {
			 std::cout << "이미 동일한 키를 가진 데이터가 저장되어 있습니다.이전 값이 삭제됩니다.\n";
			 // 기존 데이터를 삭제한다.
			 list.Delete(list[ix]->data);
		 }
	 }
	
	 // 해시테이블에 값 추가
	 list.PushLast(Entry(key, value));

 }

 void HashTable::Delete(const std::string& key)
{
	 // 삭제 연산은 2단계의 복합 과정
	 // 1. 찾기
	 int keyValue = GenerateKey(key);

	 // 버킷 인덱스
	 int bucketIndex = keyValue % bucketCount;

	 // 리스트 가져오기
	 LinkedList<Entry>& list = table[bucketIndex];

	 // 2. 동일한 키 값을 가진 데이터 검색
	 for (int ix = 0; ix < list.Count(); ++ix)
	 {
		 // 키가 같은걸 허용하지 않는다,
		 if (list[ix]->data.key == key)
		 {
			 // 기존 데이터를 삭제한다.
			 list.Delete(list[ix]->data);
			 std::cout << "삭제 완료.\n";
			 return;
		 }
	 }

	 //삭제 실패
	 std::cout << "삭제할 데이터를 찾지 못했습니다.\n";
 }

 bool HashTable::Find(const std::string& key, Entry& outValue)
{

	 // 찾기
	 int keyValue = GenerateKey(key);

	 // 버킷 인덱스
	 int bucketIndex = keyValue % bucketCount;

	 // 리스트 가져오기
	 LinkedList<Entry>& list = table[bucketIndex];

	 // 검색할 필요가 있는지 확인? 
	 // 저장된 데이터가 없는 경우
	 if (list.Count() == 0)
	 {
		 std::cout << "실패 : 빈 테이블.\n";
		 return false;
	 }

	 // 검색
	 for (int ix = 0; ix < (int)list.Count(); ++ix)
	 {
		 // 같은 키를 가진 데이터를 찾았으면
		 if (list[ix]->data.key == key)
		 {
			 outValue = list[ix]->data;
			 return true;
		 }
	 }

	 std::cout << "삭제할 데이터를 찾지 못했습니다.\n";
	 return false;;
}

 void HashTable::Print() const
{
	 for (int ix = 0; ix < bucketCount; ++ix)
	 {
		 LinkedList<HashTable::Entry> list = table[ix];
		 // 리스트가 비어있으면 다음 리스트로
		 if (table[ix].Count() == 0)
		 {
			 continue;
		 }

		 for (int jx = 0; jx < (int)list.Count(); ++jx)
		 {
			 std::cout
				 << "키 : " << list[jx]->data.key
				 << " / 값 : " << list[jx]->data.value
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