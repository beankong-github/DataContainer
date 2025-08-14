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


    //// �ݺ��ؼ� �Է� �ޱ�.
    //char input[50] = {};

    //// ������ �߰� ����
    //while (true)
    //{
    //    std::cout << "�߰��� �����͸� �Է����ּ���(����� q)\n";
    //    std::cin >> input;

    //    // q�� �������� Ȯ��.
    //    if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
    //    {
    //        break;
    //    }

    //    // ����ó��.
    //    if (!atoi(input))
    //    {
    //        std::cout << "���ڸ� �Է� �����մϴ�.\n";
    //        continue;
    //    }

    //    // ������ ����.
    //    list.Insert(atoi(input));

    //    // ���.
    //    list.Print();
    //}

    // ����Ʈ ����.
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

    // ������ ���� ����
    //while (true)
    //{
    //    std::cout << "������ �����͸� �Է����ּ���(����� q)\n";
    //    std::cin >> input;

    //    // q�� �������� Ȯ��.
    //    if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
    //    {
    //        break;
    //    }

    //    // ����ó��.
    //    if (!atoi(input))
    //    {
    //        std::cout << "���ڸ� �Է� �����մϴ�.\n";
    //        continue;
    //    }

    //    // ������ ����.
    //    list.Delete(atoi(input));

    //    // ���.
    //    list.Print();
    //}
}