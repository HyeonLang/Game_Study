
//#define HOME1
//#define HOME2
#define HOME3

// #ifdef : ��ܿ� ������ ��ũ�ΰ� ���ǵǾ� �ִٸ� �Ʒ��� �ڵ带 ���α׷��� ����
#ifdef HOME1
/*
	���� : ȯ�� ���� �����
	���� : bmi ���� �����
*/
#include<stdio.h>

int main()
{
	// ȯ�� ���� �����
	//int won = 0;
	//printf("��ȭ �Է� : ");
	//scanf_s("%d", &won);
	//
	//printf("�޷� : %lf", won * 0.00075);

	// bmi

	double height = 0, weight = 0;

	printf("���� �Է�(cm) : ");
	scanf_s("%lf", &height);

	height *= 0.01;

	printf("���� �Է�(kg) : ");
	scanf_s("%lf", &weight);

	printf("bmi : %lf", weight / (height * height));

	return 0;
}
#endif

#ifdef HOME2


// ���� : bmi ���� ���׷��̵�
//	- ���� bmi��ġ�� ���� ��ü��, ����, ��ü��, �� ����ϱ�

#include<stdio.h>

int main()
{
	double height = 0, weight = 0;

	printf("���� �Է�(cm) : ");
	scanf_s("%lf", &height);

	height *= 0.01;

	printf("���� �Է�(kg) : ");
	scanf_s("%lf", &weight);

	double bmi = weight / (height * height);
	printf("bmi : %lf\n", bmi);

	if (bmi < 20)
		printf("��ü���Դϴ�.\n");
	else if(bmi < 25)
		printf("�����Դϴ�.\n");
	else if(bmi < 30)
		printf("��ü���Դϴ�.\n");
	else
		printf("���Դϴ�.\n");

	return 0;
}


#endif 

#ifdef HOME3

#include<stdio.h>

int main()
{
	// ���� : ���� ���� �� ���� �����
	//	- ������ ������ ����
	//  - �÷��̾ ���� ��쿡 ���� ��, ��, ���º� ���
	//  - if, switch���� ����Ͽ� �ۼ�

	int enemy = 0;
	int player = 0;
	printf("���� ���� ��? : ");
	scanf_s("%d", &player);

	if (player == 0) printf("���º�");
	if (player == 1) printf("�й�");
	if (player == 2) printf("�¸�");
	
	switch (player)
	{
	case 0: printf("���º�");	break;
	case 1: printf("�й�");		break;
	case 2: printf("�¸�");		break;
	}

	return 0;
}



#endif


