#include "QuickSort.h"

int Partition(int* arr, int left, int right)
{
    // 피벗을 기준으로 배열을 분할
    int pivot = arr[left];

    // 왼쪽에서 오른쪽으로 이동하면서
    // 피벗보다 작은 값을 검색
    int low = left + 1;
    int high = right;

    while (low <= high)
    {
        while (low <= right && arr[low] <= pivot)
        {
            ++low;
        }

        // 오른쪽에서 왼쪽으로 검색
        while (high > left && arr[high] >= pivot)
        {
            --high;
        }

        //종료 조건확인
        // low와 high가 서로 교차
        if (low > high)
        {
            break;
        }

        Swap(arr[low], arr[high]);
    }

    // 피벗값과  왼쪽 데이터 집합의 마지막 요소를 교환
    Swap(arr[left], arr[high]);

    // 왼쪽 집합의 마지막 인덱스를 반환
    return high;
}

void  QuickSort(int* arr, int left, int right)
{
    // 예외 처리
    // 왼쪽 인덱스와 오른쪽 인덱스가 겹치거나 교차했는지 확인
    if (left >= right)
    {
        return;
    }

    // 피벗 기준으로 배열 분할
    int pivot = Partition(arr, left, right);

    // 왼쪽 항목 정렬(재귀)
    QuickSort(arr, left, pivot-1);

    // 오른쪽 항목 정렬(재귀)
    QuickSort(arr, pivot+1, right);

    return;
}
