#include <iostream>
#include "LinkedList.h"

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

    // ����Ʈ ����.
    LinkedList list;

    // �ݺ��ؼ� �Է� �ޱ�.
    char input[50] = {};

    // ������ �߰� ����
    while (true)
    {
        std::cout << "�߰��� �����͸� �Է����ּ���(����� q)\n";
        std::cin >> input;

        // q�� �������� Ȯ��.
        if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
        {
            break;
        }

        // ����ó��.
        if (!atoi(input))
        {
            std::cout << "���ڸ� �Է� �����մϴ�.\n";
            continue;
        }

        // ������ ����.
        list.Insert(atoi(input));

        // ���.
        list.Print();
    }

    // ������ ���� ����
    while (true)
    {
        std::cout << "������ �����͸� �Է����ּ���(����� q)\n";
        std::cin >> input;

        // q�� �������� Ȯ��.
        if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
        {
            break;
        }

        // ����ó��.
        if (!atoi(input))
        {
            std::cout << "���ڸ� �Է� �����մϴ�.\n";
            continue;
        }

        // ������ ����.
        list.Delete(atoi(input));

        // ���.
        list.Print();
    }
}