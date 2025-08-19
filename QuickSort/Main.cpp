#include "QuickSort.h"
#include <iostream>

#define ArraySize(array) sizeof(array) / sizeof(array[0])

void PrintArray(int array[], int length)
{
    for (int ix = 0; ix < length; ++ix)
    {
        std::cout << array[ix];
        if (ix < length - 1)
        {
            std::cout << ", ";
        }
    }

    std::cout << "\n";
}

int main()
{
    // 자료 집합.
    int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

    // 배열 크기
    auto length = ArraySize(array);

    // 정렬 전 출력
    std::cout << "정렬 전 출력 : ";
    PrintArray(array, length);

    // 정렬
    QuickSort(array, 0, length - 1);

    //정렬 후 출력
    std::cout << "정렬 후 출력 : ";
    PrintArray(array, length);

    return 0;
}