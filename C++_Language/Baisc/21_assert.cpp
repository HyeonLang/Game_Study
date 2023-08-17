// 21_assert.cpp

#include <iostream>
#include <cassert>

int main() {
	int x = 0;
	//x �Է�, ��ȭ �ڵ�
	std::cout << x << std::endl;

	/*
		assert
			- ���ǽ��� true �̸� ��� ����, �ƴϸ� ����
			- Ư�� ������ ���� ���� Ȯ�� ����
			- debug ��忡���� ����, release ��忡���� ����
			- �Ϲ� assert�� ��Ÿ�ӽ� Ȯ�� : ���� ���� üũ
	*/
	//assert(x != 0); 
	
	//���ڿ� ����� ���ڿ��� ù �ּ� == true : ���ڿ��� �ڵ� ������ �� �� ����.
	assert(x != 0 && "x is 0");  

	//���� assert : ������ Ÿ�Ӷ� Ȯ���ϴ� assert
	//static_assert(false); 
	
	//�����Ͻ� Ȯ�ΰ����� ������� �����ϴ�.
	bool is_b = true;
	const bool is_cb = is_b; //const�� �����Ͻ�, ��Ÿ�ӽ� ��� �� Ȯ���� �����ϴ�.
	constexpr bool is_db = true; //constexpr : �����Ͻ� ������ �Ǿ�� �ϴ� ����
	//static_assert(is_b, "is_b" ); //error
	//static_assert(is_cb,"is_cb" ); //error
	
	constexpr int z = 30;
	constexpr int w = 20;
	static_assert(z > w, "w is bigger than z"); //z <= w�� ��� error 

	return 0;
}

//static_assert ��� ����
template<typename T>
void Test(T val)
{
	static_assert(typeid(T) != typeid(int), "T is int"); //T �� int�� ���� 
}