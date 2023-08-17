// 09_perfect_forwarding.cpp

#include <iostream>
#include <vector>

class MyClass {};

void func(MyClass& c) { std::cout << "L-ref" << std::endl; }
void func(const MyClass& c) { std::cout << "const L-ref" << std::endl; }
void func(MyClass&& c) { std::cout << "R-ref" << std::endl; }

/*
	1. ���� Ȯ��

	�Ʒ��� ���� �ڵ带 �ۼ��Ѵٸ� t��� �Ű������� ���� �� ������ Ÿ���� &�� &&�� ���� T��� �ڷ������� �߷��ϰ� �ȴ�.
	-> T, &T, &&T ������ Ÿ���� ���� �� &�� ������ T�� �ν��ع�����.

	�׷��� ������ � Ÿ���� ���� �޴� T t �� ���� copy�ؿ��� �ǰ� L-value Ÿ���� ������ �� �� �ۿ� ����.
	-> �� ������ �ذ��Ͽ� �Ϻ��ϰ� �����ϰ� ���� -> perfect forwarding
*/
//template <typename T> // auto ó�� �ۿ� -> ��� L-value ���
//void func_wrapper(T t) {
//	func(t);
//}


/*
	2. T -> &T�� �ٲ۴ٸ�?

	l-value�� ���� �� �ֱ� ������ func_wrapper(MyClass()); ���� ������ �߻��Ѵ�.
	�������� �ޱ� ���� const T& t Ÿ������ �����ε� �Ͽ����� �ᱹ ���ڸ� �ޱ� ���ؼ���
	�̸��� �ִ� �Ű����� ������ �ޱ� ������ l-value�� �߷��ع����� ������ �߻��ϰ�
	�����ε��� ����� �ϴ� ���ŷο��� �����.
*/
//template <typename T>
//void func_wrapper(T& t) { // R-value�� ���� �� ����.
//	func(t);
//}
//template <typename T>
//void func_wrapper(const T& t) { // R-value�� ������ const L-value�� �ν��Ѵ�.
//	func(t);
//}
//template <typename T>
//void func_wrapper(T&& t) { // R-value�� ������ move�� ������� ������L-value�� �ν��Ѵ�. 
//						     //-> �ᱹ �Ű����� t�� �̸��� �ֱ� ����
//	func(std::move(t));
//}


/*
   3. T -> T&&�� �ٲ۴ٸ�?

   �Ϲ� �Լ������� ������ Ÿ�Կ� ���ؼ� &&�� �޴´ٴ� ���� r-value�� �޴� �ٴ� �ǹ̸� ��������
   ������ ���ø� Ÿ���� T&& ���·� �޴´ٴ� ���� l-value�� r-value�� ���� ���� �� �ִٴ� ���� �ǹ��Ѵ�.
   -> �̰��� universal reference��� �θ���.

   ������ �̸��� �ִ� �Ű������� �ޱ� ������ Ÿ�� ��ü�� l-value�� �ν��ϰԵȴ�.
   -> �̴� forward<T>()�� ����Ͽ� �ذᰡ��

   universal reference�� ���۷��� ��ħ ��Ģ�� ���� T�� Ÿ���� �߷��Ѵ�.
   -> &�� 1, &&�� 0���� �ΰ� OR������ �Ѵٰ� �����ϸ�ȴ�.
                          
   typedef int& T1;
   T1& r1;      T1&     -> int&, &     -> int&
   T1&& r2;     T1&&    -> int&, &&    -> int&

   typedef int&& T2;
   T2& r3;      T2&     -> int&&, &    -> int&
   T2&& r4;     T2&&    -> int&&, &&   -> int&&
*/ 
template <typename T>
void func_wrapper(T&& t) {  
	//func(t);

	func(std::forward<T>(t)); // perfect forwarding 
}


int main() {
	MyClass c;
	const MyClass cc;

	std::cout << "func" << std::endl;
	func(c);		// L-value
	func(cc);		// const L-value
	func(MyClass());// R-value
	std::cout << std::endl;

	std::cout << "func_wrapper" << std::endl;
	func_wrapper(c);
	func_wrapper(cc);
	func_wrapper(MyClass()); 
	std::cout << std::endl;

}