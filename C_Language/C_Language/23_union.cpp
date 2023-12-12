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
		����ü (Union)
		- �ϳ��� �޸𸮸� �پ��� �ڷ����� ���� ������� �����ؼ� ����ϴ� ��
		- ����ü�� ���������� ����ü�� ��� ������ �޸� ������ ������
		����ü�� �ϳ��� �޸� ������ ��� ����� �����ؼ� ����Ѵ�.
	*/

	{
		// ���� : 16����Ʈ�� ������ ���� �����ϱ�(�е�)
		union my_union
		{
			char c;
			int i;
			double d;
		};

		my_union uni;

		printf("���Ͽ� ������ ������\t: %d\n", sizeof(uni));
		printf("���Ͽ� ��� c�� ������\t: %d\n", sizeof(uni.c));
		printf("���Ͽ� ��� i�� ������\t: %d\n", sizeof(uni.i));
		printf("���Ͽ� ��� d�� ������\t: %d\n\n", sizeof(uni.d));

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
		// Ÿ���� ȥ���� ��밡��
		struct ptr
		{
			union
			{
				int* ip;
				float* fp;
			};

			bool is_int;	// ���� ���� �ڷḦ �����ߴ��� �Ǵ��ϱ� ���� ����
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
		// �ٸ��̸�/�������� ��밡��
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
	// ���� ������ ��쿡�� �ֹε�Ϲ�ȣ ����
	char rrn1[7];
	char rrn2[8];
};

struct company_owner
{
	// ȸ�� ������ ��쿡�� ȸ�� ��� ��ȣ ����
	char crn1[4];
	char crn2[3];
	char crn3[6];
};

struct car_data
{
	char model[15]; // �� ����

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
		���� : �α� ����ũ �����
		- 22������ ����� �������� Ȱ���Ͽ� �α׶���ũ ���� �����
		- �¸� ����, �й� ����
		- ����, �÷��̾�, ��, ���� ��� ���ӿ� �����ϴ� ������Ʈ 6���� �����
		- ���Ϳ� ���� ����
		- ���� �̿��� �̺�Ʈ 2�� �̻� ����
		- �޴� ����
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
		- �����Ͱ� ������ ������ ������ ���� ���� �޸� �ּҿ� ��ġ
		- ����� ���� ����� ������ ǥ��
		- ���� ���� ���Ǵ� intel �̳� AMD CPU(x86 x64)���� ���

		Big Endian
		- �����Ͱ� ������ ������ ������ ���� ū �޸� �ּҿ� ��ġ
		- ����� ���ڸ� ���� ����� ����
		- ����� �������� �޸� Ȯ���� ����
		- ��Ʈ��ũ ��Ʈ���� ���
		- xbox360, IBM PowerPc CPU ��� ���Ǿ���
	*/
}
