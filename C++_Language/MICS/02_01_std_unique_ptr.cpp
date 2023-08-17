// 02_01_std_unique_ptr.cpp

/*
   unique_ptr
   - Ư�� ��ü�� *�ϳ��� ����Ʈ �����͸�* �������� ������ �ϴ� ����Ʈ ������
   - auto_ptr�� �������� ������ ������
   - unique_ptr�� �Ҹ��Ҷ�, �ڽ��� ������ dull �����͸� �����Ѵ�.
      �� dull(raw) pointer : ����Ʈ �����Ͱ� ������ ���� ������
*/

#include <iostream>
#include <memory>
#include "02_02_resource.h"
using namespace std;

void DoSomething(std::unique_ptr<Resource> res)
{
    res->SetAll(10);
    res->Print();
}

int main() 
{
    //1.
    {
        std::unique_ptr<Resource> res1(new Resource(5));

        auto res2 = make_unique<Resource>(5); // unique_ptr�� ����� �ִ� �Լ� : �������� ��ġ�� ����

        res2->SetAll(5);
        res2->Print();

        //res2 = res1; // ����ũ �ؾ��ϹǷ� ���� ����(L-value)�� �ȵ�. 

        res2 = std::move(res1); // L-value�� R-value�� �ٲپ� �̵� ���� ������ ȣ��
                                // res2�� ���� ������ �ִ� �����ʹ� ������.

        // res2�� �ű�� ���� res1�� �������� ����ϱ� ������ �̵� ���� �� ���� �õ��� ����
        //res1->Print(); // error
    }

    //2.
    {
        auto res1 = std::make_unique<Resource>(5);

        // ���� �����ڸ� ȣ���ϹǷ� error 
        //DoSomething(res1); 

        // R-value ���·� �ѱ�� ����.
        // -> ��� ������ �����Ͱ� �̵��ϰ� �ȴ�.
        // -> ������ �������� �������� �ѱ�°� ������ �ȴٸ� ���� ���·� �ް� �ѱ�°� ����.
        DoSomething(std::move(res1)); // res1�� nullptr�� ��. 

        // ����Ʈ �����Ͱ� ������ �ִ� �������� dull �����͸� ��ȯ
        res1.get();
    }

    //3.
    {
        // dull �����Ϳ� ����Ʈ �����͸� ���� ����ϸ� �߻��� �� �ִ� ������

        Resource* res = new Resource(5);

        // res�� ������ �ּҸ� �Ѱ��ش�. res�� ����Ʈ �����Ͱ� �ƴϱ� ������ �������� ������� �ʴ´�. 
        // -> unique_ptr�� �� ��ü�� ���Ͽ� �ϳ��� �����͸� �����ؾ��ϴµ� �ΰ� �̻��� �����Ͱ� �����ϰ� ��
        std::unique_ptr<Resource> res1(res);
        // res = nullptr; // nullptr�� �ʱ�ȭ���ָ� �Ǳ���

        //...

        // res1�� res2�� ���� �ּҸ� �����ϰ� �ȴ�.
        std::unique_ptr<Resource> res2(res);

        // �ش� ������ ����� res1�� res2 �Ҹ� -> �Ѵ� �ڱⰡ ������ res�� �ּҸ� �����Ѵ�.
        // ���� �ּҸ� �ι� �����Ϸ��� �õ��� -> ��� ������ ������ �߻�
        // ������ dull ������ ������ ���� �Ҵ��ϴ� ���� ���� �ʴ°� ����.
    }

    const std::unique_ptr<Resource> res1(new Resource(5)); // ����Ʈ �����͸� �����ϰ� ���� ���ϱ� ���� const
    std::unique_ptr<const Resource> res2(new Resource(5)); // Resource�� �����ϰ� ���� ���ϱ� ���� const

    return 0;
}