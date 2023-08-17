// 12_random_number.cpp

#include<iostream>

// c  ����
#include<stdlib.h>
#include<time.h>

// c++ ����
#include<random>

int main()
{
    /*
        c style ������ ������
        - �õ尪�� ����ð����� �ϱ� ������ ���� �ð����� ���α׷��� ������ �õ尪�� ������.
        - %�����ڸ� ����� ���� ������ ���̹Ƿ� �յ��� ��е��� ���� �� �ִ�.
        - rand() ��ü�� ���� �˰����� ���� �ʴ�.
    */
    {
        srand((unsigned int)time(NULL));

        for (int i = 0; i < 10; i++)
            printf("%d, ", rand() % 10);
        printf("\n");
    }

    //c++ style
    {
        std::random_device rd; //�ϵ���� �ø��� �ѹ� ��� : �õ尪 ������ ���� ����
        
        std::mt19937_64 messenne(rd()); //rand() ����, �õ尪 �Ű�����:2^19937_64bit

        std::uniform_int_distribution<> dice(1, 6); //���� ���� ���� ����

        //std::uniform_real_distribution<> �Ǽ�

        for (int i = 0; i < 10; i++) {
            std::cout << dice(messenne) << ", "; //���� ����
        }
        std::cout << std::endl;
    }

    return 0;
}