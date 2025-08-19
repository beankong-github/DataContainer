#include "MergeSort.h"

#define ArraySize(array) sizeof(array) / sizeof(array[0])

int main()
{
    // 배열.
    int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

    // 배열 길이
    int length = (int)ArraySize(array);

    // 정렬 전 출력
    std::cout << "정렬 전 배열:";
    PrintArray(array, length);

    // 정렬
    MergeSort(array, length);

    // 정렬 후 출력
    std::cout << "정렬 후 배열:";
    PrintArray(array, length);



}