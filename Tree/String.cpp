#include "String.h"

String::String(const char* value)
{
    // 문자열 길이 구하기
    length = value == nullptr ? 0 : (int)strlen(value);
    
    // 입력값이 없으면 종료
    if (value == nullptr)
        return; 

    // 문자열 복사
    data = new char[length + 1];
    strcpy_s(data, length + 1, value);
}

String::String(const String& other)
    :length(other.length)
{
    data = new char[other.length + 1];
    
    // 복사
    strcpy_s(data, length + 1, other.data);
}

String::String(String&& other) noexcept
    :length(other.length)
{
    data = other.data;
    other.data = nullptr;
}

String::~String()
{
    if (data)
    {
        delete[] data;
        data = nullptr;
    }
}

String& String::operator=(const String& other)
{
    length = other.length;

    data = new char[other.length + 1];

    // 복사
    strcpy_s(data, length + 1, other.data);

    return *this;
}

String& String::operator=(String&& other)
{
    length = other.length;
    data = other.data;
    other.data = nullptr;

    return *this;
}

bool String::operator==(const String& other)
{
    return strcmp(data, other.data) == 0;
}

String String::operator+(const String& other)
{
    // 두 문자열을 더한 총 길이
    size_t newLength = length + other.length;
    // 저장공간 확보
    char* newString = new char[newLength + 2];
    // 내 문자열 복사
    strcat_s(newString, length+1, data);
   // 다른 문자열 복사
   //strcpy_s(newString + length, other.length + 1, other.data);
    strcat_s(newString, newLength+2, other.data);

    String temp(newString);
    delete[] newString;

    return temp;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
    return os << string.data;
}
