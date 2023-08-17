// 03_shared_ptr.cpp

/*
   shared_ptr
      - ����ũ �����Ϳ� �޸� ������ ������ ������ ������.
      - �����͸� �Լ��� ���� �����ؾ� �� ��, ����ũ ������ ��� ����ϱ� �����ϴ�.
      - ���� ī���� ����� ����Ѵ�.
         �� �ش� dull�����͸� �����ϰ� �ִ� ����Ʈ �������� *������ ī����*�Ͽ� ������
         ����Ʈ �����Ͱ� �Ҹ��Ҷ� �������ִ� ���
*/
#include <iostream>
#include <memory>
#include "02_02_resource.h"
using namespace std;

int main()
{
    {
        // dull ptr�� �޾� res1 �������� ī��Ʈ ���� : 0 -> 1
        std::shared_ptr<Resource> res1 = std::make_shared<Resource>(5);

        res1->SetAll(2);
        res1->Print();

        cout << "Count : " << res1.use_count() << endl;
        
        {
            // res2�� res1�� ����Ű�� �ּҸ� �޾� ī��Ʈ ���� : 1 -> 2
            auto res2(res1);

            res2->SetAll(3);
            res2->Print();

            cout << "Count : " << res1.use_count() << endl; // res2.use_count() ���� ��� ����.
        } // res2 �Ҹ�� ī��Ʈ ���� : 2 -> 1 , ���� dull ptr�� ������ ����Ʈ �����Ͱ� �־� �޸� ������ ���� ����.

        cout << "Count : " << res1.use_count() << endl;
    } // res1 �Ҹ�� ī��Ʈ ���� : 1 -> 0, dull ptr�� ������ ������ ����Ʈ �����Ͱ� �Ҹ��Ͽ� �޸𸮸� �����Ѵ�.



    // shared_ptr�� ����Ҷ� ������
    Resource* ptr = new Resource(10);

    {

        // dull �����͸� �޾� res1�� �������� ī��Ʈ 0 -> 1 ����
        std::shared_ptr<Resource> res1(ptr);

        res1->SetAll(2);
        res1->Print();
        cout << "Count : " << res1.use_count() << endl;

        {
            // dull �����͸� �޾� res2�� �������� ī��Ʈ 0 -> 1 ����
            // dull ������ ���·� �޾����Ƿ� res1�� ������ ���� ī��Ʈ�� ���� ������ �ȴ�.
            std::shared_ptr<Resource> res2(ptr);


            res2->SetAll(3);
            res2->Print();
            // res1�� ������ �����Ƿ� count : 1 ���
            cout << "Count : " << res2.use_count() << endl;

        } // res2 �Ҹ�, res2 �������� ī��Ʈ ���� 1 -> 0, ������ ����Ʈ ������ �Ҹ��Ͽ� ������ dull pointer ����


        cout << "Count : " << res1.use_count() << endl;

        system("pause");
    } // res1 �Ҹ�, res1 ��������ī��Ʈ ���� 0 -> 1, ������ ����Ʈ ������ �Ҹ��Ͽ� ������ dull pointer ���� 
    // ������ res2���� ���� �ش� �����͸� �����Ͽ����Ƿ� -> ��������� ���� �߻� -> *error*

    return 0;
}