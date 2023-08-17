// 20_pointer.cpp

/*
	������
	- Ư�� ��ü�� �����ϴ� �޸� ������ �����ּҸ� �����ϴ� ����
	- �ּҸ� ����Ų�ٴ� �ǹ̿����� �������̴�.
	- �����ʹ� Ư�� ��ü�� ���� �ּҸ��� ������ ������ Ư�� ��ü�� �� ũ��� �� �� ����.
	- ����� ���ÿ� �ʱ�ȭ�ϴ� ���� �����Ѵ�. �ʱ�ȭ���� ���� ���·� ����
	�ǵ����� ���� �޸𸮸� ����ϰų� ������ �� �ֱ� �����̴�.

	- �������� ũ��� �ü���� ���� �ٸ���.
	32bit �ü�� : 4byte
	64bit �ü�� : 8byte
	-> 32bit, 64bit�� CPU�� �����͸� ó���ϴµ� ����ϴ� ���������� ũ�⸦ �ǹ��Ѵ�.
	�������� ũ��� �� ���������� ũ�⸦ ���󰡱� ������ 32bit�� ��쿡�� 4byte
	64bit�� ��쿡�� 8byte�� ũ�⸦ ������.

	�������� : CPU�� ����� ó���ϴ� �������� �ӽ� �������
*/

#include<stdio.h>
#include<string.h>

void pointer();
void pointer_and_arr();
void pointer_and_const();
void void_pointer();
void pointer_and_structure();
void pointer_and_function();
void double_pointer();
void pointer_arr();
void pointer_arr_and_2d_arr();

int main()
{
	//pointer();
	//pointer_and_arr();
	//pointer_and_const();
	//void_pointer();
	//pointer_and_structure();
	//pointer_and_function();
	//double_pointer();
	//pointer_arr();
	pointer_arr_and_2d_arr();

	return 0;
}

void pointer()
{
	// & : ���� ������, �������� �޸� �ּҰ��� �˾ƿ��� ������
	// * : ������ ������, �ּҰ��� ������ ������ �����ϴ� ������

	// int�� �����͸� �����ϴ� ����
	int i = 10;

	// int�� �����͸� �����ϴ� ������ �޸𸮸� �����ϴ� ������
	int* ip1 = &i;

	// &i �� ip(&i)�� ���� ǥ���̴�.
	printf("i�� �ּ� 0x%p \n", &i); // &�� ����Ͽ� ���� i�� �����ּҰ� ���
	printf("ip1�� �� 0x%p \n\n", ip1);

	// i�� *ip(*&i)�� ���� ǥ���̴�.
	printf("i�� ��\t\t %d \n", i); // &�� ����Ͽ� ���� i�� �����ּҰ� ���
	printf("ip1�� ������\t %d \n\n", *ip1);
	// ip1 == &i
	// *ip1 == *&i == i

	// 32bit, 64bit���̿� ���� ũ�Ⱑ �ٲ��.
	printf("������ ip1 ũ�� : %d \n\n", (int)sizeof(ip1));
}

void pointer_and_arr()
{
	int arr[5] = { 0,1,2,3,4 }; // �迭�� �̸��� �迭�� �����ּҸ� ����Ų��.
	int* arr_ptr = arr; // arr == &arr[0]

	sizeof(arr);
	sizeof(arr_ptr);

	printf("arr�� �ּ�\t: 0x%p \n", &arr);
	printf("arr_ptr�� ��\t: 0x%p \n\n", arr_ptr);

	printf("arr�� ������ ��\t\t: %d\n", *arr);
	printf("arr�� 0���� ����\t: %d\n", arr[0]);
	printf("arr_ptr�� ������ ��\t: %d\n\n", *(arr_ptr + 1));

	/*
		�����ʹ� +, - �������� �ڷ����� ����Ʈ ũ�⸸ŭ �ּҸ� �̵��Ѵ�.
		�ڷ����� void�� ���� �Ұ���
		�迭[�ε���]�� *(�迭 + �ε���)�̴�.
	*/

	for (int i = 0; i < 5; i++)
		printf("arr[%d]�� �ּ� : 0x%p\n", i, &arr[i]);
	printf("\n");

	for (int i = 0; i < 5; i++)
		printf("arr[%d]�� �ּ� : 0x%p\n", i, &arr_ptr[i]);
	printf("\n");

	for (int i = 0; i < 5; i++)
		printf("arr[%d]�� �ּ� : 0x%p\n", i, arr + i);
	printf("\n");

	for (int i = 0; i < 5; i++)
		printf("arr[%d]�� �ּ� : 0x%p\n", i, arr_ptr + i);
	printf("\n");
}

void pointer_and_const()
{
	/*
		const�� ���� �ڷ����� ���ȭ ��Ų��. -> �������� ���ϰ� ���ƹ���
		���������� const �Ǿտ� ������� ���� �ڷ����� ���ȭ ��Ų��.
	*/

	//1.

	const double PI1 = 3.14;
	double const PI2 = 3.14;
	const double const PI3 = 3.14; // ���� �ڷ����� ���� const�� ���� -> �ϳ��� �����Ͱ� ������
	const const const double const const const PI4 = 3.14; // ���� �ڷ����� ���� const�� ���� -> �ϳ��� �����Ͱ� ������
	// ���� const�� ���� double�� ���ȭ ��Ų��.
	// PI1 = 0; // error : ���ȭ�� �����ʹ� ���� �Ұ���

	//2.
	{
		const int arr[5] = { 0,1,2,3,4 };
		//arr[0] = 5; // error : ���ȭ�� �����ʹ� ���� �Ұ���
	}

	//3.
	{
		int arr[5] = { 0,1,2,3,4 };
		int* arr_ptr = arr;
		arr_ptr[0] = 0;
	}

	//4.
	{
		// ���� : �ø�ƽ, ���ؽ� ���� �����ϱ�

		int arr[5] = { 0,1,2,3,4 };
		int* arr_ptr = arr; // C������ ������ ���� 
		//arr[0] = 0;
		// 
		// ������ ��ü�� ����� �ƴϱ� ������ ��ȸ������ ���� ����
		// -> ���� �߻��� ������ �����.
		arr_ptr[0] = 5;

		printf("%d\n", arr_ptr[0]);
	}

	//5
	{
		int arr1[5] = { 0,1,2,3,4 };
		int arr2[5] = { 0,1,2,3,4 };
		const int* arr_ptr = arr1;
		// ������ ���·ε� const�� �پ��� ������ ���� �Ұ���
		//arr_ptr[0] = 5;

		// ���� const�� int���� �پ��ֱ� ������ �ڽ��� �����ϰ� �ִ� ������ ���������� ��������
		// ������ '*' �ڷ������� const�� �Ⱥپ��� ������ ������ ������ �ִ� 
		// �ּҰ� ��ü�� ������ ����
		arr_ptr = arr2;
	}

	//6
	{
		int arr1[5] = { 0,1,2,3,4 };
		int arr2[5] = { 0,1,2,3,4 };
		int* const arr_ptr = arr1;
		// ������ �����ϰ� �ִ� �ּ��� ����(int)��ü�� const�� �ƴϱ� ������ 
		// ������ �����ϰ� �ִ� �޸𸮿� �����Ͽ� ������ ����
		arr_ptr[0] = 5;

		// ������ '*' �ڷ����� const�� �پ��� ������ ������ ������ �ּҸ� �������� ����
		//arr_ptr = arr2;

		//arr_ptr++;
		arr_ptr + 1;
	}

	// �������� ���� �κ��� �����Ͷ�� const�� ���̴°� ���α׷��� ���� �����ϰ� ���� �� �ִ�.
	// -> �����ϴٸ� const�� �ٿ�����
}

void void_pointer()
{
	/*
		void ������
		- �ڷ����� �������� ���� ������
		- � �ڷ����� �ּҵ� void �����Ϳ� ���� �����ϴ�.
		- �ּҸ� ������ �ϱ� ���ؼ��� ����ȯ�� �ʿ��ϴ�.
	*/

	int i[3] = { 0,1,2 };
	void* void_ptr = i; // � �ڷ����� �ּ��̵� void* �� ���� �� �ִ�.


	// ������ �ִ� �ּ��� �ڷ����� ���� ������ x
	// -> ũ�⵵ �𸣰� �д� ����� �� �� ���⶧��
	//printf("%d\n", *void_ptr); 

	// ����ϱ� ���ؼ��� Ư�� �ڷ������� ����ȯ�� ���־�� �Ѵ�.
	printf("%d\n", *(int*)void_ptr);

	// ������ ���굵 �ȵ�
	//printf("%p\n", void_ptr + 1);

	printf("%p\n", (int*)void_ptr + 1);

	struct data
	{
		int id;
		void* data;
	};

	struct data d;

}

void pointer_and_structure()
{
	struct person
	{
		char name[50];
		int age;
		float height;
	};

	struct person p = { "ȫ�浿", 30, 175.25f };

	// . : ����ü ����� �����ϴ� ������
	p.height = 180.0f;

	// . �����ڴ� &���� �켱������ ����
	// & �����ڸ� ����Ͽ� height ����� �ּҸ� �� �� �ִ�.
	&p.height;

	// ����ü ������ �̸��� ���� �ּҸ� �ǹ����� �ʴ´�.
	struct person* p_ptr = &p;

	// * ���� . �����ڰ� �켱������ �����Ƿ� �켱������ �����ؾ���
	(*p_ptr).age;

	// -> : (*����ü ������). �� ���� �����ϴ� ������
	p_ptr->age;


	struct person p_arr[2] =
	{
		{ "ȫ�浿", 30, 175.25f },
		{ "ȫ�浿", 30, 175.25f },
	};

	p_ptr = p_arr;

	(*(p_ptr + 0)).age;
	p_ptr[0].age;
}

int Add(int x, int y) { return x + y; }
int Sub(int x, int y) { return x - y; }

struct Player {
	char name[50];
	char location[50];
	int hp;
	void (*dead_event[5])(struct Player*);
};

void print_dead(struct Player* p)
{
	printf("%s ���\n", p->name);
}

void revive(struct Player* p)
{
	printf("%s �һ�\n", p->name);
	p->hp = 200;
}

void set_location_to_town(struct Player* p)
{
	printf("������ �̵��մϴ�.\n");
	strcpy_s(p->location, 5, "Town");

	return;
}

void pointer_and_function()
{
	/*
		�Լ� ������
		- Ư�� �ڷ����� ��ȯ�ϰ� Ư�� �Ű����� ����� ������ �Լ��� �����ϴ� ������
		- �Լ��� �̸��� �Լ��� �ּҸ� �ǹ��Ѵ�.
		- ���α׷��� �����ϰ� © �� �ִ�.
	*/

	// ��ȯ�� (*�Լ� ������ ���� �̸�)(�Ű����� �ڷ��� ���)
	int (*func_ptr)(int, int) = NULL;
	// -> int���� ��ȯ�ϰ� int, int ���·� �Ű������� �޴�
	// �Լ��� ������ �� �ִ� �Լ� ������ func_ptr ����

	// �Լ��� �̸��� �Լ��� �ּ�
	func_ptr = Sub;
	printf("%d\n", func_ptr(10, 20));

	// ����ڷκ��� + �Ǵ� -�� ������� �� ������ �Է¹޾� ���� ����� ����ϴ� �Լ�.

	char op = '\0';
	printf("������ �Է� : ");
	scanf_s(" %c", &op, (int)sizeof(op));

	int x = 0;
	printf("�ǿ����� �Է� : ");
	scanf_s("%d", &x);

	int y = 0;
	printf("�ǿ����� �Է� : ");
	scanf_s("%d", &y);

	int (*compute)(int, int) = NULL;

	switch (op)
	{
	case '+': compute = Add; break; // �Լ��� �̸��� �Լ��� �ּ�
	case '-': compute = Sub; break; // �Լ��� �̸��� �Լ��� �ּ�
	};

	if (compute != NULL)
		printf("��� : %d\n", compute(x, y));

	// Ư�� �̺�Ʈ���� �����ų �Լ��� ������ �� �ִ�.

	struct Player p = {
		"Mage",
		"Dungeon",
		100,
		{NULL,NULL,NULL,NULL,NULL}
	};

	p.dead_event[0] = print_dead;
	p.dead_event[1] = revive;
	p.dead_event[2] = set_location_to_town;

	printf("%s�� ��ġ : %s, HP : %d\n", p.name, p.location, p.hp);

	while (1)
	{
		int damage = 0;
		scanf_s("%d", &damage);
		p.hp -= damage;

		if (p.hp <= 0)
		{
			for (int i = 0; i < 5; i++)
				if (p.dead_event[i] != NULL)
					p.dead_event[i](&p);
			break;
		}
	}

	printf("%s�� ��ġ : %s, HP : %d\n", p.name, p.location, p.hp);
}

void swap_ptr1(int* ptr1, int* ptr2)
{
	int* temp = NULL;

	temp = ptr1;
	ptr1 = ptr2;
	ptr2 = temp;

	return;
}

void swap_ptr2(int** ptr1, int** ptr2)
{
	int* temp = NULL;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;

	return;
}

void double_pointer()
{
	/*
		���� ������(double pointer)
		 - ������ ������ �ּҸ� �����ϴ� ����
		 - ���� �̻� ���������� ��������� �ʴ´�.
		 - ������ ������ ���� �����ϱ� ���� ���
	*/

	/*
								 0x121|
								 0x122|    7
								 0x123|
								 0x124|

								 0x125|
		int a = 7;               0x126|    0x121
		int *ptr = &a;           0x127|
		int **pptr = &ptr;       0x128|

								 0x129|
								 0x130|    0x125
								 0x131|
								 0x132|
	*/

	int a = 7;			// ����
	int* ptr = &a;		// ������ �ּҸ� �����ϴ� ���� ������ ����
	int** pptr = &ptr;	// ������ ������ �ּҸ� �����ϴ� ���� ������ ���� 

	// pptr		==	&ptr
	// *pptr	==	*&ptr	==	ptr	==	&a
	// **pptr	==	**&ptr	== *ptr	==	*&a	== a == 7

	printf("&pptr = 0x%p\n", &pptr);
	printf("&ptr  = 0x%p\n", &ptr);
	printf("&a    = 0x%p\n\n", &a);

	printf("pptr == &ptr \n");
	printf("pptr : 0x%p\n", pptr);
	printf("&ptr : 0x%p\n", &ptr);

	printf("*pptr == ptr == &a\n");
	printf("*pptr : 0x%p\n", *pptr);
	printf("ptr : 0x%p\n", ptr);
	printf("&a : 0x%p\n\n", &a);

	printf("**pptr == *ptr == a\n");
	printf("**pptr : %d\n", **pptr);
	printf("*ptr : %d\n", *ptr);
	printf("a : %d\n\n", a);

	int b = 1;
	int c = 2;

	int* ptr1 = &b;
	int* ptr2 = &c;

	printf("**** before swap_ptr1 ****\n");
	printf("ptr1 : 0x%p\n", ptr1);
	printf("ptr2 : 0x%p\n\n", ptr2);

	// �����Ͱ� ���� ������ �ּ� ���� ���ڷ� ��
	swap_ptr1(ptr1, ptr2);

	// �����Ͱ� ������ ���� ������ �ʴ´�.
	printf("**** after swap_ptr1 ****\n");
	printf("ptr1 : 0x%p\n", ptr1);
	printf("ptr2 : 0x%p\n\n", ptr2);

	// ������ ������ �޸� �ּҸ� �Ѱ��ֹǷ�
	// ������ ������ �� ���� ����
	swap_ptr2(&ptr1, &ptr2);

	// �����Ͱ� ������ ���� ���� �ٲ�
	printf("**** after swap_ptr2 ****\n");
	printf("ptr1 : 0x%p\n", ptr1);
	printf("ptr2 : 0x%p\n", ptr2);
}

void pointer_arr()
{
	/*
		������ �迭
		- �����͸� ���ҷ� ���� �迭
	*/

	int a = 0;
	int b = 1;
	int c = 2;

	int* ptr_arr[3] = { &a, &b, &c };

	for (int i = 0; i < 3; i++)
	{
		printf("arr[%d]  : 0x%p\n", i, ptr_arr[i]);
		printf("*arr[%d] : %d\n\n", i, *ptr_arr[i]);
	}

	char* names1[4] =
	{
		"Aladdin",
		"Jasmine",
		"Magic Carpet",
		"Genie",
	};

	for (int i = 0; i < 4; i++)
		printf("%s���ڿ��� �ּ� : 0x%p\n", names1[i], names1[i]);
	printf("\n");

	// �����Ͽ� �޴� ���� �ƴ� �ش� ���ڿ� ����� ���� �ּҸ� ����
	char* test1 = "Hello";
	// ���� �ٸ��� ���� �ּҸ� �޴°� �ƴ϶� �迭�� �����Ѵ�.
	char test2[] = "Hello";

	test1[0] = 'h'; // ���ڿ� ����� ���� �ٲٷ� �õ��� ����

	// "Hello" ���ڿ� ���� ���� ���� �ƴ�
	// ���ο� ���ڿ��� ���� �ּҸ� �־���
	test1 = "hhhhh";

	// ���ڿ� ������� ������ ���� ������, ������ ������ ���̹Ƿ� ����
	test2[0] = 'h';
}

void pointer_arr_and_2d_arr()
{
	float arr[2][4] =
	{
		{1.0f,2.0f,3.0f,4.0f},
		{5.0f,6.0f,7.0f,8.0f},
	};

	/*
		arr == &arr[0] == arr[0] == &arr[0][0]

		*arr = arr[0]
		**arr  == arr[0][0]

		- 2���� �迭�� �����ּҴ� 0���� ���� �ּ��̴�.
	*/

	// ù ���� �ּҸ� ǥ���ϴ� ��
	printf("&a[0][0] : 0x%p\n", arr);
	printf("&a[0][0] : 0x%p\n", arr[0]);
	printf("\n");

	// �ѹ� ������ �ϸ� *arr == arr[0]
	printf("&a[0][0] : 0x%p\n", *arr);
	printf("&a[0][0] : 0x%p\n", &arr[0]);
	printf("&a[0][0] : 0x%p\n", &arr[0][0]);
	printf("\n");

	// 0��0�� ���� ����
	printf("arr[0][0] : %f, %f\n\n", *(*(arr + 0) + 0), arr[0][0]);

	// �� �̵�
	// arr[0][0] -> arr[1][0]
	printf("0x%p\n", (arr + 1));
	printf("0x%p\n", (&arr[1]));
	printf("0x%p\n", (arr[1]));
	printf("0x%p\n", (*(arr + 1)));
	printf("0x%p\n", (&arr[0] + 1));
	printf("0x%p\n", (&arr[1][0]));
	printf("\n");

	// �࿭ �̵�
	// 1������ �̵��� 2�� �̵�
	// arr[0][0] -> arr[0 + 1][0 + 2] -> arr[1][2]
	printf("%f\n", *(*(arr + 1) + 2));

	// 2���� �迭�� �����Ϳ� �־��

	// 1���� �迭�� ���� �����Ϳ� ������� 2���� �迭�� ���� �����Ϳ� ��°�?
	{
		int arr[2][3] = {
			{0,1,2},
			{3,4,5}
		};

		int** ptr_arr = arr;

		// ������ ����
		//ptr_arr[0][0] = 2;
	}

	{
		// 1���� �迭�� ���� ������ �迭�� 2���� �迭 ǥ���ϱ�
		// - ��� �������� �޸𸮰� ���ӵǾ� ���� ����
		// - ���� �߰��Ҷ����� ���ŷӴ�.
		// - �� �ึ�� ���� ������ �ٸ��� �� �� �ִ�.

		int arr0[3] = { 1,2,3 };
		int arr1[4] = { 4,5,6,7 };

		int* ptr_arr[2] = { arr0, arr1 };

		ptr_arr[0][0];
		*(*(ptr_arr + 0) + 0);

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				printf("%d(== %d, %d) => 0x%p, ", ptr_arr[i][j], *(ptr_arr[i] + j),
					*(*(ptr_arr + i) + j), &ptr_arr[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	{
		// 2���� �迭�� ���� ������ �迭�� 2���� �迭 ǥ���ϱ�
		int arr[2][3] = {
			{0,1,2},
			{3,4,5}
		};

		int* ptr_arr[2] = 
		{
			arr[0],
			arr[1],
		};
	}

	{
		/*
			�迭 ������
			- Ư�� ũ��� �ڷ����� ���� �迭�� ����Ű�� ������
			- ������ �迭�� �������ָ� �߰� �۾����� �迭ó�� �ٷ� �� �ִ�.
			- �ϳ��� �ּҸ� ���� �� �ִ�.
		*/

		int arr1[3] = { 0,1,2 };

		int arr2[2][3] = {
			{0,1,2},
			{3,4,5}
		};

		int arr3[3][3] = {
			{0,1,2},
			{3,4,5},
			{6,7,8}
		};

		// 3���� ������ �迭�� �ּҸ� ������ �� �ִ� �迭 ������
		int(*ptr_arr)[3] = NULL;


		// C������ 1���� �迭�� ������ �ִ�. 
		// C++������ �ȵ�
		ptr_arr = arr1;
		ptr_arr[0][0];

		for (int j = 0; j < 3; j++)
			printf("%d, ", ptr_arr[0][j]);
		printf("\n\n");

		ptr_arr = arr2;

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
				printf("%d, ", ptr_arr[i][j]);
			printf("\n");
		}
		printf("\n");

		ptr_arr = arr3;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				printf("%d, ", ptr_arr[i][j]);
			printf("\n");
		}
		printf("\n");
	}
}

