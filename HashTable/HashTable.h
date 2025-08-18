#pragma once
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Pair.h"

class HashTable
{
	// 타입 재정의 (Type Alias)
private:
	using Entry = TPair<std::string, std::string>;

public:
	HashTable();
	~HashTable();

	// 추가
	void Add(const std::string& key, const std::string& value);

	// 삭제
	void Delete(const std::string& key);
	
	// 검색
	bool Find(const std::string& key, Entry& outValue);

	// 출력
	void Print() const;

	// 비었는지 확인
	bool IsEmpty() const;

private:
	// 버킷(Bucket) 정의
	static const int bucketCount = 19;	 // 해시 충돌을 방지하기 위해서는 버킷의 크기가 소수인 것이 유리하다.
	// 2차 자료구조 활용 (체이닝)
	LinkedList<Entry> table[bucketCount] = {};

};
