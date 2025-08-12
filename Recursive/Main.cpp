#include <iostream>


// 이진 탐색
int BinarySearch(int arr[], int target, int low, int high)
{
	//[1, 2, 3, ~, 8, 9]
	// mid = 중간값
	// target이 mid 값 보다 크면 mid 이후 요소, 작으면 mid 이전 요소를 검색한다.
	// 종료 조건
	// 1. target을 찾은 경우
	// 2. 예외  : low와 high 값이 교차되는 경우


	// !! 탐색 실패
	// low와 high 값 교차하는 경우 -> arr에 target 값이 없는 경우
	if (low > high)
		return -1;

	// 중간값
	int mid = (low + high) / 2;

	// !! 탐색 성공
	// 중간값이 target이라면 탐색 성공
	if (arr[mid] == target)
		return mid;
	
	// target이 중간 값보다 큰 경우, mid 이후 요소를 검색한다.
	if (arr[mid] < target)
		return  BinarySearch(arr,target, mid+1, high);

	// target이 중간 값보다 작은 경우, mid 이전 요소를 검색한다.
	else if (arr[mid] > target)
		return BinarySearch(arr,target, low, mid-1);
}

int main()
{
	// 탐색할 자료
	// 이진 탐색이 가능하여면 정렬이 필수
	int array[] = { 2, 5, 8, 12, 16, 23, 38, 56, 72, 91 };
	int length = sizeof(array) / sizeof(array[0]);
	int target = 1;

	int result = BinarySearch(array, target, 0, length-1);

	if (result < 0)
		std::cout << "검색실패\n";
	else
		std::cout << target << "을 " << result << "번 인덱스에서 찾음\n";

	std::cin.get();
}