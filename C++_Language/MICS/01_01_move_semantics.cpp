// 01_01_move_semantics.cpp

/*
   ����Ʈ ������
   - ������ó�� �����ϴ� Ŭ���� ���ø�.
   - ���(dangling) ������, �޸� ����(memory leack)�� ���̱� ���� ������
   - memory ����� ���ԵǾ� �ִ�.

   ����Ʈ �������� ����
   - auto_ptr -> ����
   ->����
   - unique_ptr
   - shared_ptr
   - weak_ptr
*/

#include <iostream>
#include <memory>
#include "01_02_resource.h"
#include "01_03_auto_ptr.h"
using namespace std;

/*
   RAII ��Ģ : Resource Acquisition is initialization
   - ������ �������� ���� �ϴ� ��
   - RAII�� ��Ģ�� ����Ʈ �����Ϳ� ����Ǿ� ����
*/

/* Early Return : �̸� ��ȯ */
void DoSomthing1()
{
	Resource* resource = new Resource;

	//...

	// if (true) return; // early return -> �޸� ���� �߻�

	if (true)
	{
		//�ذ��1 : �����ϴ� ������ �������ش�.
		//����    : �ڵ尡 ������� ��԰� ������ �� ����
		//        -> �Ű澲�� �ʾƵ� ������ �����ǰ� ����� �ʹ� -> ����Ʈ ������

		delete resource;
		return;
	}

	delete resource;
}

/* fix */
void Dosomething2()
{
	// �ذ��2 : �Ҹ��ڿ��� �������ֱ�
	// ��ü�� �Ҹ��ϸ鼭 �Ҹ��ڰ� ȣ��ȴ�.
    // �Ҹ��ڿ� ���������� ���ִ� �ڵ尡 �־
    // �Ű� ������ �ʾƵ� �ڵ����� �޸𸮸� �������ش�.
    // -> ����Ʈ �����Ͱ� �̷� ������ ������� �ִ�.
	AutoPtr<Resource> resource(new Resource);

	if (true)
		return;
}


void DoSomething3(AutoPtr<Resource> temp)
{

}

int main()
{
	// ������ ��� �� �ڵ����� �Ҹ��Ų��.
	{
		cout << "{" << endl;
		AutoPtr<Resource> res = new Resource; // ����Ʈ ������ ����
		cout << "}" << endl;
	} // ����Ʈ ������ �Ҹ�

	// ����Ʈ ������ ������
	AutoPtr<Resource> res1 = new Resource;

	// . �����ڸ� ���� �����°��� ����Ʈ �������� ��� �Լ��̴�.
	res1.Test();

	// ������ �������� ����� �����ϱ����ؼ��� -> �����ڸ� ���� �����Ѵ�.
	//res1->


	// AutoPtr�� ������ 1
	AutoPtr<Resource> res2 = new Resource;

	// autoptr�� ���� �������� �������� �Ѿ ������ �ȴ�.
	DoSomething3(res2); // copy �Ű������̱� ������ ������ ���� �Լ��� �Ѿ. �� res2�� nullptr

	//res2-> // �������� ����� ���� �߻���


	// ������ 2 
	// autoptr�� *�迭 ����*�� ����, ������ ������ �ʴ´�.
	// delete�� �ְ� delete[]�� ���� 


	// �̷��� ������ �־� autoptr�� ������� �ʴ´�. -> 3���� ���·� �ٲ� - unique_ptr -shared_ptr - weak_ptr

	return 0;
}