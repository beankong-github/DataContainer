#pragma once
#include <iostream>

class String
{
public:
	String(const char* value = nullptr);
	String(const String& other);
	String(String&& other) noexcept;
	~String();

	String& operator=(const String& other);
	String& operator=(String&& other);
	bool operator==(const String& other);
	String operator+(const String& other);

	// 편의 함수
	friend std::ostream& operator<<(std::ostream& os, const String& string);

private:
	int length = 0;
	char* data = nullptr;
};