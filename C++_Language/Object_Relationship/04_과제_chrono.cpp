// ����
// chrono���� 

#include <iostream>
#include <chrono>
#include <cmath>

/*
    * chorono ��?

        - C++11���� �߰��� �ð��� ���õ� ���̺귯��
        - ������ C ��Ÿ�ӿ��� �����ϴ� time �Լ����� �پ��� ����� �����ϸ�, C�� time ���� ����� ���� ���е��� �ξ� ����.
        - �ð������� ������ ���� (time �Լ��� ���� �ð��� ��¦ ��߳��� ��� ��. chrono�� ���� �̿�����.
*/

// ��) for�� ���ư��µ� �ɸ� �ð�

int main()
{
    // ���� �ð� now�� start ������ ����
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    // for���� �����鼭 �ð��� �� sum�� 
    int sum = 0;
    for (int i = 0; i < 999999999; i++)
        sum += i;

    // '���ο�' ����ð� now�� ó�� ���۽ð��� start�� �� ���� ������ sec �� ����
    std::chrono::duration<double>sec = std::chrono::system_clock::now() - start;
    std::cout << "for���� �����µ� �ɸ��� �ð�(��) : " << sec.count() << "seconds" << std::endl;

    // ��½�) for���� �����µ� �ɸ��� �ð�(��) : 0.581512seconds

/*
    ���⼭ time_point�� �ð����� �� ���� �ǹ�.

    for���� �����Ͽ� �ٽ� ���� �ð��� ���� �Ŀ� for���� �����ϱ� �� ������ ���� �ð��� ���� for���� �����ϴ� �� �ɸ� �ð��� ���� �� �ִ�.

    chrono���� ��� �� ���� ��Ÿ�� �� duration Ŭ������ ����ϴµ�, duration�� 6���� �ð� ������ �����Ѵ�.

        - duration ���� �ð� ����

            std::chrono::nanoseconds    : ���뼼���� (1/10�� ��)
            std::chrono::microseconds   : ����ũ�� ������ (1/100�� ��)
            std::chrono::milliseconds   : �и� ������ (1/1000 ��)
            std::chrono::seconds        : ��
            std::chrono::minutes        : ��
            std::chrono::hours          : ��

        - clock Ŭ����

            chrono���� system_clock�Ӹ� �ƴ϶� steady_clock�� high_resolution_clock�� �ִ�.

            1) system_clock         : ���� �Ϲ������� ����ϴ� ������, �ý��� �ð��� ��Ÿ����. (C ��Ÿ���� time_t�� ȣȯ)

            2) steady_clock         : ������ �ð�ó�� ���� �������� �ʴ� �ð��� ��Ÿ����.
                                      ��, steady_clock �̿��� clock Ŭ������ time_point�� ���� �� OS���� ��¥�� ���ŷ� �ǵ��� �Ŀ� time_point�� ������ �տ� ���� �ð��� ������,
                                      steady_clock������ �׷� �� ����.
                                      ���� '�ð��� �帧�� �ٲ��� �ʴ� �ð�'�� ��� ���� �� steady_clock�� ����ϸ� �ȴ�.

            3) high_resolution_clock : Windows �Ǵ� Linux���� �����ϴ� ���е��� ���� ���� �ð�.
                                       �� Ŭ������ system_clock�̳� steady_clock�� �ٸ� ��Ī���� ���ǵǱ⵵ �Ѵ�.
*/


// chrono�� �̿��� timer �����

// ���� �ð� now �� startTime ������ ����
    auto startTime = std::chrono::system_clock::now();

    // �ð����� second ������ �ʴ���(1�ʾ�++) ���� Sec ���� ũ�� �ʴ� "(����) " ������ ��������(while) ������
    int Sec = 0;
    while (1)
    {
        // endTime �� ���� �ð� now�� ����
        auto endTime = std::chrono::system_clock::now();
        // endTime ���� ó���ð� �����ߴ� startTime �� ���� second �� ����(�ð� ����)
        auto second = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        // �� ������ 
        if (second.count() > Sec)
        {
            Sec++;
            std::cout << Sec << " ";
        }
    }

    return 0;
}