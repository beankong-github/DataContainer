#include <iostream>


// ���� Ž��
int BinarySearch(int arr[], int target, int low, int high)
{
	//[1, 2, 3, ~, 8, 9]
	// mid = �߰���
	// target�� mid �� ���� ũ�� mid ���� ���, ������ mid ���� ��Ҹ� �˻��Ѵ�.
	// ���� ����
	// 1. target�� ã�� ���
	// 2. ����  : low�� high ���� �����Ǵ� ���


	// !! Ž�� ����
	// low�� high �� �����ϴ� ��� -> arr�� target ���� ���� ���
	if (low > high)
		return -1;

	// �߰���
	int mid = (low + high) / 2;

	// !! Ž�� ����
	// �߰����� target�̶�� Ž�� ����
	if (arr[mid] == target)
		return mid;
	
	// target�� �߰� ������ ū ���, mid ���� ��Ҹ� �˻��Ѵ�.
	if (arr[mid] < target)
		return  BinarySearch(arr,target, mid+1, high);

	// target�� �߰� ������ ���� ���, mid ���� ��Ҹ� �˻��Ѵ�.
	else if (arr[mid] > target)
		return BinarySearch(arr,target, low, mid-1);
}

int main()
{
	// Ž���� �ڷ�
	// ���� Ž���� �����Ͽ��� ������ �ʼ�
	int array[] = { 2, 5, 8, 12, 16, 23, 38, 56, 72, 91 };
	int length = sizeof(array) / sizeof(array[0]);
	int target = 1;

	int result = BinarySearch(array, target, 0, length-1);

	if (result < 0)
		std::cout << "�˻�����\n";
	else
		std::cout << target << "�� " << result << "�� �ε������� ã��\n";

	std::cin.get();
}