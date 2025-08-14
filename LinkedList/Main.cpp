#include <iostream>
#include "SingleLinkedList.h"

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    //// 반복해서 입력 받기.
    //char input[50] = {};

    //// 데이터 추가 루프
    //while (true)
    //{
    //    std::cout << "추가할 데이터를 입력해주세요(종료는 q)\n";
    //    std::cin >> input;

    //    // q를 눌렀는지 확인.
    //    if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
    //    {
    //        break;
    //    }

    //    // 예외처리.
    //    if (!atoi(input))
    //    {
    //        std::cout << "숫자만 입력 가능합니다.\n";
    //        continue;
    //    }

    //    // 데이터 삽입.
    //    list.Insert(atoi(input));

    //    // 출력.
    //    list.Print();
    //}

    // 리스트 생성.
    SingleLinkedList list;
    FILE* inputs = nullptr;
    fopen_s(&inputs, "SortTestInput.txt", "rt");
    if (inputs != nullptr)
    {
        char  input[1024];
        fread_s(input, sizeof(input), 1, 1024, inputs);

        char* left = nullptr;
        char* num = strtok_s(input, " ", &left);

        while (num != nullptr)
        {
            list.Insert(atoi(num));
            num = strtok_s(NULL, " ", &left);
        }
        list.Print(list.GetHead());
    }

    list.Sort();

    // 데이터 삭제 루프
    //while (true)
    //{
    //    std::cout << "삭제할 데이터를 입력해주세요(종료는 q)\n";
    //    std::cin >> input;

    //    // q를 눌렀는지 확인.
    //    if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
    //    {
    //        break;
    //    }

    //    // 예외처리.
    //    if (!atoi(input))
    //    {
    //        std::cout << "숫자만 입력 가능합니다.\n";
    //        continue;
    //    }

    //    // 데이터 삽입.
    //    list.Delete(atoi(input));

    //    // 출력.
    //    list.Print();
    //}
}