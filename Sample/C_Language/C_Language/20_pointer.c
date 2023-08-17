// 20_pointer.cpp

/*
	포인터
	- 특정 개체가 차지하는 메모리 공간의 시작주소를 저장하는 변수
	- 주소를 가리킨다는 의미에서의 포인터이다.
	- 포인터는 특정 개체의 시작 주소만을 가지기 때문에 특정 개체의 총 크기는 알 수 없다.
	- 선언과 동시에 초기화하는 것을 권장한다. 초기화되지 않은 상태로 사용시
	의도하지 않은 메모리를 사용하거나 변경할 수 있기 때문이다.

	- 포인터의 크기는 운영체제의 따라 다르다.
	32bit 운영체제 : 4byte
	64bit 운영체제 : 8byte
	-> 32bit, 64bit는 CPU가 데이터를 처리하는데 사용하는 레지스터의 크기를 의미한다.
	포인터의 크기는 이 레지스터의 크기를 따라가기 때문에 32bit인 경우에는 4byte
	64bit인 경우에는 8byte의 크기를 가진다.

	레지스터 : CPU가 명령을 처리하는 데이터의 임시 저장공간
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
	// & : 참조 연산자, 데이터의 메모리 주소값을 알아오는 연산자
	// * : 역참조 연산자, 주소값에 데이터 공간에 접근하는 연산자

	// int형 데이터를 저장하는 변수
	int i = 10;

	// int형 데이터를 저장하는 변수의 메모리를 저장하는 포인터
	int* ip1 = &i;

	// &i 와 ip(&i)는 같은 표현이다.
	printf("i의 주소 0x%p \n", &i); // &를 사용하여 변수 i의 사작주소값 출력
	printf("ip1의 값 0x%p \n\n", ip1);

	// i와 *ip(*&i)는 같은 표현이다.
	printf("i의 값\t\t %d \n", i); // &를 사용하여 변수 i의 사작주소값 출력
	printf("ip1의 역참조\t %d \n\n", *ip1);
	// ip1 == &i
	// *ip1 == *&i == i

	// 32bit, 64bit차이에 따라 크기가 바뀐다.
	printf("포인터 ip1 크기 : %d \n\n", (int)sizeof(ip1));
}

void pointer_and_arr()
{
	int arr[5] = { 0,1,2,3,4 }; // 배열의 이름은 배열의 시작주소를 가리킨다.
	int* arr_ptr = arr; // arr == &arr[0]

	sizeof(arr);
	sizeof(arr_ptr);

	printf("arr의 주소\t: 0x%p \n", &arr);
	printf("arr_ptr의 값\t: 0x%p \n\n", arr_ptr);

	printf("arr의 역참조 값\t\t: %d\n", *arr);
	printf("arr의 0번지 원소\t: %d\n", arr[0]);
	printf("arr_ptr의 역참조 값\t: %d\n\n", *(arr_ptr + 1));

	/*
		포인터는 +, - 연산으로 자료형의 바이트 크기만큼 주소를 이동한다.
		자료형이 void인 경우는 불가능
		배열[인덱스]는 *(배열 + 인덱스)이다.
	*/

	for (int i = 0; i < 5; i++)
		printf("arr[%d]의 주소 : 0x%p\n", i, &arr[i]);
	printf("\n");

	for (int i = 0; i < 5; i++)
		printf("arr[%d]의 주소 : 0x%p\n", i, &arr_ptr[i]);
	printf("\n");

	for (int i = 0; i < 5; i++)
		printf("arr[%d]의 주소 : 0x%p\n", i, arr + i);
	printf("\n");

	for (int i = 0; i < 5; i++)
		printf("arr[%d]의 주소 : 0x%p\n", i, arr_ptr + i);
	printf("\n");
}

void pointer_and_const()
{
	/*
		const는 앞의 자료형을 상수화 시킨다. -> 수정하지 못하게 막아버림
		예외적으로 const 맨앞에 있을경우 뒤의 자료형을 상수화 시킨다.
	*/

	//1.

	const double PI1 = 3.14;
	double const PI2 = 3.14;
	const double const PI3 = 3.14; // 같은 자료형에 대한 const는 무시 -> 하나만 적은것과 동일함
	const const const double const const const PI4 = 3.14; // 같은 자료형에 대한 const는 무시 -> 하나만 적은것과 동일함
	// 위의 const가 전부 double을 상수화 시킨다.
	// PI1 = 0; // error : 상수화된 데이터는 수정 불가능

	//2.
	{
		const int arr[5] = { 0,1,2,3,4 };
		//arr[0] = 5; // error : 상수화된 데이터는 수정 불가능
	}

	//3.
	{
		int arr[5] = { 0,1,2,3,4 };
		int* arr_ptr = arr;
		arr_ptr[0] = 0;
	}

	//4.
	{
		// 과제 : 시맨틱, 신텍스 에러 조사하기

		int arr[5] = { 0,1,2,3,4 };
		int* arr_ptr = arr; // C에서만 가능한 문법 
		//arr[0] = 0;
		// 
		// 포인터 자체는 상수가 아니기 때문에 우회적으로 수정 가능
		// -> 문제 발생의 여지가 생긴다.
		arr_ptr[0] = 5;

		printf("%d\n", arr_ptr[0]);
	}

	//5
	{
		int arr1[5] = { 0,1,2,3,4 };
		int arr2[5] = { 0,1,2,3,4 };
		const int* arr_ptr = arr1;
		// 포인터 형태로도 const가 붙었기 때문에 수정 불가능
		//arr_ptr[0] = 5;

		// 현재 const가 int형에 붙어있기 때문에 자신이 소유하고 있는 변수를 수정하지는 못하지만
		// 포인터 '*' 자료형에는 const가 안붙었기 때문에 본인이 가지고 있는 
		// 주소값 자체는 변경이 가능
		arr_ptr = arr2;
	}

	//6
	{
		int arr1[5] = { 0,1,2,3,4 };
		int arr2[5] = { 0,1,2,3,4 };
		int* const arr_ptr = arr1;
		// 본인이 소유하고 있는 주소의 형태(int)자체는 const가 아니기 때문에 
		// 본인이 소유하고 있는 메모리에 접근하여 수정이 가능
		arr_ptr[0] = 5;

		// 포인터 '*' 자료형에 const가 붙었기 때문에 본인이 소유한 주소를 변경하지 못함
		//arr_ptr = arr2;

		//arr_ptr++;
		arr_ptr + 1;
	}

	// 수정하지 않을 부분의 데이터라면 const를 붙이는게 프로그램을 더욱 안전하게 만들 수 있다.
	// -> 가능하다면 const를 붙여주자
}

void void_pointer()
{
	/*
		void 포인터
		- 자료형이 정해지지 않은 포인터
		- 어떤 자료형의 주소든 void 포인터에 저장 가능하다.
		- 주소를 역참조 하기 위해서는 형변환이 필요하다.
	*/

	int i[3] = { 0,1,2 };
	void* void_ptr = i; // 어떤 자료형의 주소이든 void* 에 담을 수 있다.


	// 가지고 있는 주소의 자료형을 몰라 역참조 x
	// -> 크기도 모르고 읽는 방법도 알 수 없기때문
	//printf("%d\n", *void_ptr); 

	// 사용하기 위해서는 특정 자료형으로 형변환을 해주어야 한다.
	printf("%d\n", *(int*)void_ptr);

	// 포인터 연산도 안됨
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

	struct person p = { "홍길동", 30, 175.25f };

	// . : 구조체 멤버를 참조하는 연산자
	p.height = 180.0f;

	// . 연산자는 &보다 우선순위가 높다
	// & 연산자를 사용하여 height 멤버의 주소를 알 수 있다.
	&p.height;

	// 구조체 변수의 이름은 시작 주소를 의미하지 않는다.
	struct person* p_ptr = &p;

	// * 보다 . 연산자가 우선순위가 높으므로 우선순위를 지정해야함
	(*p_ptr).age;

	// -> : (*구조체 포인터). 와 같이 동작하는 연산자
	p_ptr->age;


	struct person p_arr[2] =
	{
		{ "홍길동", 30, 175.25f },
		{ "홍길동", 30, 175.25f },
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
	printf("%s 사망\n", p->name);
}

void revive(struct Player* p)
{
	printf("%s 소생\n", p->name);
	p->hp = 200;
}

void set_location_to_town(struct Player* p)
{
	printf("마을로 이동합니다.\n");
	strcpy_s(p->location, 5, "Town");

	return;
}

void pointer_and_function()
{
	/*
		함수 포인터
		- 특정 자료형을 반환하고 특정 매개변수 목록을 가지는 함수를 저장하는 포인터
		- 함수의 이름은 함수의 주소를 의미한다.
		- 프로그램을 유연하게 짤 수 있다.
	*/

	// 반환값 (*함수 포인터 변수 이름)(매개변수 자료형 목록)
	int (*func_ptr)(int, int) = NULL;
	// -> int형을 반환하고 int, int 형태로 매개변수를 받는
	// 함수를 저장할 수 있는 함수 포인터 func_ptr 선언

	// 함수의 이름은 함수의 주소
	func_ptr = Sub;
	printf("%d\n", func_ptr(10, 20));

	// 사용자로부터 + 또는 -의 연산장와 두 정수를 입력받아 연산 결과를 출력하는 함수.

	char op = '\0';
	printf("연산자 입력 : ");
	scanf_s(" %c", &op, (int)sizeof(op));

	int x = 0;
	printf("피연산자 입력 : ");
	scanf_s("%d", &x);

	int y = 0;
	printf("피연산자 입력 : ");
	scanf_s("%d", &y);

	int (*compute)(int, int) = NULL;

	switch (op)
	{
	case '+': compute = Add; break; // 함수의 이름은 함수의 주소
	case '-': compute = Sub; break; // 함수의 이름은 함수의 주소
	};

	if (compute != NULL)
		printf("결과 : %d\n", compute(x, y));

	// 특정 이벤트에서 실행시킬 함수를 예약할 수 있다.

	struct Player p = {
		"Mage",
		"Dungeon",
		100,
		{NULL,NULL,NULL,NULL,NULL}
	};

	p.dead_event[0] = print_dead;
	p.dead_event[1] = revive;
	p.dead_event[2] = set_location_to_town;

	printf("%s의 위치 : %s, HP : %d\n", p.name, p.location, p.hp);

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

	printf("%s의 위치 : %s, HP : %d\n", p.name, p.location, p.hp);
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
		이중 포인터(double pointer)
		 - 포인터 변수의 주소를 저장하는 변수
		 - 삼중 이상도 가능하지만 사용하지는 않는다.
		 - 포인터 변수의 값을 변경하기 위해 사용
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

	int a = 7;			// 변수
	int* ptr = &a;		// 변수의 주소를 저장하는 단일 포인터 변수
	int** pptr = &ptr;	// 포인터 변수의 주소를 저장하는 이중 포인터 변수 

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

	// 포인터가 가진 변수의 주소 값이 인자로 들어감
	swap_ptr1(ptr1, ptr2);

	// 포인터가 소유한 값은 변하지 않는다.
	printf("**** after swap_ptr1 ****\n");
	printf("ptr1 : 0x%p\n", ptr1);
	printf("ptr2 : 0x%p\n\n", ptr2);

	// 포인터 변수의 메모리 주소를 넘겨주므로
	// 포인터 변수의 값 수정 가능
	swap_ptr2(&ptr1, &ptr2);

	// 포인터가 소유한 값의 값이 바뀜
	printf("**** after swap_ptr2 ****\n");
	printf("ptr1 : 0x%p\n", ptr1);
	printf("ptr2 : 0x%p\n", ptr2);
}

void pointer_arr()
{
	/*
		포인터 배열
		- 포인터를 원소로 가진 배열
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
		printf("%s문자열의 주소 : 0x%p\n", names1[i], names1[i]);
	printf("\n");

	// 복사하여 받는 것이 아닌 해당 문자열 상수의 시작 주소를 받음
	char* test1 = "Hello";
	// 위와 다르게 시작 주소를 받는게 아니라 배열에 복사한다.
	char test2[] = "Hello";

	test1[0] = 'h'; // 문자열 상수의 값을 바꾸려 시도해 에러

	// "Hello" 문자에 덮어 씌운 것이 아닌
	// 새로운 문자열의 시작 주소를 넣어줌
	test1 = "hhhhh";

	// 문자열 상수에서 복사한 값을 저장한, 변수를 수정할 뿐이므로 가능
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

		- 2차원 배열의 시작주소는 0행의 시작 주소이다.
	*/

	// 첫 시작 주소를 표현하는 법
	printf("&a[0][0] : 0x%p\n", arr);
	printf("&a[0][0] : 0x%p\n", arr[0]);
	printf("\n");

	// 한번 역참조 하면 *arr == arr[0]
	printf("&a[0][0] : 0x%p\n", *arr);
	printf("&a[0][0] : 0x%p\n", &arr[0]);
	printf("&a[0][0] : 0x%p\n", &arr[0][0]);
	printf("\n");

	// 0행0열 원소 접근
	printf("arr[0][0] : %f, %f\n\n", *(*(arr + 0) + 0), arr[0][0]);

	// 행 이동
	// arr[0][0] -> arr[1][0]
	printf("0x%p\n", (arr + 1));
	printf("0x%p\n", (&arr[1]));
	printf("0x%p\n", (arr[1]));
	printf("0x%p\n", (*(arr + 1)));
	printf("0x%p\n", (&arr[0] + 1));
	printf("0x%p\n", (&arr[1][0]));
	printf("\n");

	// 행열 이동
	// 1행으로 이동후 2열 이동
	// arr[0][0] -> arr[0 + 1][0 + 2] -> arr[1][2]
	printf("%f\n", *(*(arr + 1) + 2));

	// 2차원 배열을 포인터에 넣어보기

	// 1차원 배열은 단일 포인터에 담았으니 2차원 배열은 이중 포인터에 담는가?
	{
		int arr[2][3] = {
			{0,1,2},
			{3,4,5}
		};

		int** ptr_arr = arr;

		// 엑세스 위반
		//ptr_arr[0][0] = 2;
	}

	{
		// 1차원 배열과 단일 포인터 배열로 2차원 배열 표현하기
		// - 모든 데이터의 메모리가 연속되어 있지 않음
		// - 행을 추가할때마다 번거롭다.
		// - 각 행마다 열의 개수를 다르게 할 수 있다.

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
		// 2차원 배열과 단일 포인터 배열로 2차원 배열 표현하기
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
			배열 포인터
			- 특정 크기와 자료형을 가진 배열을 가리키는 포인터
			- 선언후 배열만 대입해주면 추가 작업없이 배열처럼 다룰 수 있다.
			- 하나의 주소만 담을 수 있다.
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

		// 3열을 가지는 배열의 주소를 저장할 수 있는 배열 포인터
		int(*ptr_arr)[3] = NULL;


		// C언어에서는 1차원 배열도 담을수 있다. 
		// C++에서는 안됨
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

