#include "MergeSort.h"

#define ArraySize(array) sizeof(array) / sizeof(array[0])

int main()
{
    // �迭.
    int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

    // �迭 ����
    int length = (int)ArraySize(array);

    // ���� �� ���
    std::cout << "���� �� �迭:";
    PrintArray(array, length);

    // ����
    MergeSort(array, length);

    // ���� �� ���
    std::cout << "���� �� �迭:";
    PrintArray(array, length);



}