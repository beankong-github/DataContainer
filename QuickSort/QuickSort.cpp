#include "QuickSort.h"

int Partition(int* arr, int left, int right)
{
    // �ǹ��� �������� �迭�� ����
    int pivot = arr[left];

    // ���ʿ��� ���������� �̵��ϸ鼭
    // �ǹ����� ���� ���� �˻�
    int low = left + 1;
    int high = right;

    while (low <= high)
    {
        while (low <= right && arr[low] <= pivot)
        {
            ++low;
        }

        // �����ʿ��� �������� �˻�
        while (high > left && arr[high] >= pivot)
        {
            --high;
        }

        //���� ����Ȯ��
        // low�� high�� ���� ����
        if (low > high)
        {
            break;
        }

        Swap(arr[low], arr[high]);
    }

    // �ǹ�����  ���� ������ ������ ������ ��Ҹ� ��ȯ
    Swap(arr[left], arr[high]);

    // ���� ������ ������ �ε����� ��ȯ
    return high;
}

void  QuickSort(int* arr, int left, int right)
{
    // ���� ó��
    // ���� �ε����� ������ �ε����� ��ġ�ų� �����ߴ��� Ȯ��
    if (left >= right)
    {
        return;
    }

    // �ǹ� �������� �迭 ����
    int pivot = Partition(arr, left, right);

    // ���� �׸� ����(���)
    QuickSort(arr, left, pivot-1);

    // ������ �׸� ����(���)
    QuickSort(arr, pivot+1, right);

    return;
}
