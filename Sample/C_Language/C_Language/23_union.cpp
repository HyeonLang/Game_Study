// 23_union.cpp

#include<stdio.h>
#include<string.h>

void uinon_();
void uinon_and_structures1();
void uinon_and_structures2();

void endianness();

int main()
{
	//uinon_();
	//uinon_and_structures1();
	//uinon_and_structures2();
	endianness();

	return 0;
}

void uinon_()
{
	/*
		공용체 (Union)
		- 하나의 메모리를 다양한 자료형을 가진 멤버들이 공유해서 사용하는 것
		- 구조체와 유사하지만 구조체는 멤버 각각의 메모리 공간이 있지만
		공용체는 하나의 메모리 공간을 모든 멤버가 공유해서 사용한다.
	*/

	{
		// 과제 : 16바이트가 나오는 이유 조사하기(패딩)
		union my_union
		{
			char c;
			int i;
			double d;
		};

		my_union uni;

		printf("유니온 공간의 사이즈\t: %d\n", sizeof(uni));
		printf("유니온 멤버 c의 사이즈\t: %d\n", sizeof(uni.c));
		printf("유니온 멤버 i의 사이즈\t: %d\n", sizeof(uni.i));
		printf("유니온 멤버 d의 사이즈\t: %d\n\n", sizeof(uni.d));

		printf("0x%p\n", &uni);
		printf("0x%p\n", &uni.c);
		printf("0x%p\n", &uni.i);
		printf("0x%p\n\n", &uni.d);
	}

	{
		union my_union
		{
			char c;
			int i;
			float f;
		};

		union my_union uni;

		uni.i = 123456;

		printf("%d %f %d %c\n\n", uni.i, uni.f, (int)uni.c, uni.c);

		printf("c : %c\n", uni.c);
		printf("i : %d\n", uni.i);
		printf("f : %f\n\n", uni.f);

		uni.c = 'A';

		printf("c : %c\n", uni.c);
		printf("i : %d\n", uni.i);
		printf("f : %f\n\n", uni.f);

		uni.f = 1.1f;

		printf("c : %c\n", uni.c);
		printf("i : %d\n", uni.i);
		printf("f : %f\n\n", uni.f);
	}
}

void uinon_and_structures1()
{
	{
		// 타입을 혼용해 사용가능
		struct ptr
		{
			union
			{
				int* ip;
				float* fp;
			};

			bool is_int;	// 무슨 형의 자료를 저장했는지 판단하기 위한 변수
		};

		ptr ptr;

		int i = 100;
		float f = 200.0f;

		ptr.ip = &i;
		ptr.is_int = true;

		if (ptr.is_int == true)
		{
			printf("ptr is Int : %d\n", *ptr.ip);
		}
		else
		{
			printf("ptr is float : %f\n", *ptr.fp);
		}

		ptr.fp = &f;
		ptr.is_int = false;

		if (ptr.is_int == true)
		{
			printf("ptr is Int : %d\n", *ptr.ip);
		}
		else
		{
			printf("ptr is float : %f\n", *ptr.fp);
		}
	}

	{
		// 다른이름/형식으로 사용가능
		struct Location
		{
			union
			{
				struct { double x; double y; };
				struct { double arr[2]; };
			};
		};

		struct Location loc = { 1.1,1.2 };

		printf("%lf, %lf\n", loc.x, loc.y);
		printf("%lf, %lf\n\n", loc.arr[0], loc.arr[1]);
	}
}

enum OwnerType
{
	Personal,
	Company
};

struct personal_owner
{
	// 개인 소유일 경우에는 주민등록번호 저장
	char rrn1[7];
	char rrn2[8];
};

struct company_owner
{
	// 회사 소유일 경우에는 회사 등록 번호 저장
	char crn1[4];
	char crn2[3];
	char crn3[6];
};

struct car_data
{
	char model[15]; // 차 기종

	OwnerType owner_type;

	union
	{
		struct personal_owner po;
		struct company_owner co;
	};
};

void print_car(struct car_data data)
{
	if (data.owner_type == Personal)
	{
		printf("personal owner = %s-%s\n",
			data.po.rrn1,
			data.po.rrn2
		);
	}
	else if (data.owner_type == Company)
	{
		printf("Company owner = %s-%s-%s\n",
			data.co.crn1,
			data.co.crn2,
			data.co.crn3
		);
	}
}



void uinon_and_structures2()
{
	/*
		과제 : 로그 라이크 만들기
		- 22번에서 배웠던 열거형을 활용하여 로그라이크 게임 만들기
		- 승리 조건, 패배 조건
		- 몬스터, 플레이어, 벽, 함정 등등 게임에 등장하는 오브젝트 6종류 만들기
		- 몬스터와 전투 구현
		- 전투 이외의 이벤트 2개 이상 구현
		- 메뉴 구현
	*/

	car_data c1 = {
		"Avante",
		Personal
	};
	strcpy_s(c1.po.rrn1, sizeof(c1.po.rrn1), "111111");
	strcpy_s(c1.po.rrn2, sizeof(c1.po.rrn2), "1111111");

	car_data c2 = {
	"Avante",
	Company
	};
	strcpy_s(c2.co.crn1, sizeof(c2.co.crn1), "111");
	strcpy_s(c2.co.crn2, sizeof(c2.co.crn2), "11");
	strcpy_s(c2.co.crn3, sizeof(c2.co.crn3), "11111");

	print_car(c1);
	print_car(c2);
}

void endianness()
{
	union mu_union {
		int i;
		char c;
	};

	union mu_union uni;

	// 12 34 56 78
	// 78 56 34 12
	uni.i = 0x12345678;

	printf("0x12345678\n");
	printf("i : %x\n", uni.i);
	printf("c : %x\n", uni.c);

	/*
		Endianness

		Little Endian
		- 데이터가 끝나는 마지막 단위가 가장 작은 메모리 주소에 위치
		- 사람이 쓰는 방법을 뒤집은 표현
		- 현재 흔히 사용되는 intel 이나 AMD CPU(x86 x64)에서 사용

		Big Endian
		- 데이터가 끝나는 마지막 단위가 가장 큰 메모리 주소에 위치
		- 사람이 숫자를 쓰는 방법과 같다
		- 디버깅 과정에서 메모리 확인이 편함
		- 네트워크 스트림에 사용
		- xbox360, IBM PowerPc CPU 등에서 사용되었음
	*/
}
