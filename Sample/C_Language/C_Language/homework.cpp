
//#define HOME1
//#define HOME2
#define HOME3

// #ifdef : 상단에 지정한 매크로가 정의되어 있다면 아래의 코드를 프로그램에 포함
#ifdef HOME1
/*
	과제 : 환율 계산기 만들기
	과제 : bmi 계산기 만들기
*/
#include<stdio.h>

int main()
{
	// 환율 계산기 만들기
	//int won = 0;
	//printf("원화 입력 : ");
	//scanf_s("%d", &won);
	//
	//printf("달러 : %lf", won * 0.00075);

	// bmi

	double height = 0, weight = 0;

	printf("신장 입력(cm) : ");
	scanf_s("%lf", &height);

	height *= 0.01;

	printf("무게 입력(kg) : ");
	scanf_s("%lf", &weight);

	printf("bmi : %lf", weight / (height * height));

	return 0;
}
#endif

#ifdef HOME2


// 과제 : bmi 계산기 업그레이드
//	- 나온 bmi수치에 따라 저체중, 정상, 과체중, 비만 출력하기

#include<stdio.h>

int main()
{
	double height = 0, weight = 0;

	printf("신장 입력(cm) : ");
	scanf_s("%lf", &height);

	height *= 0.01;

	printf("무게 입력(kg) : ");
	scanf_s("%lf", &weight);

	double bmi = weight / (height * height);
	printf("bmi : %lf\n", bmi);

	if (bmi < 20)
		printf("저체중입니다.\n");
	else if(bmi < 25)
		printf("정상입니다.\n");
	else if(bmi < 30)
		printf("과체중입니다.\n");
	else
		printf("비만입니다.\n");

	return 0;
}


#endif 

#ifdef HOME3

#include<stdio.h>

int main()
{
	// 과제 : 가위 바위 보 게임 만들기
	//	- 상대방은 가위로 고정
	//  - 플레이어가 내는 경우에 따라 승, 패, 무승부 출력
	//  - if, switch문을 사용하여 작성

	int enemy = 0;
	int player = 0;
	printf("가위 바위 보? : ");
	scanf_s("%d", &player);

	if (player == 0) printf("무승부");
	if (player == 1) printf("패배");
	if (player == 2) printf("승리");
	
	switch (player)
	{
	case 0: printf("무승부");	break;
	case 1: printf("패배");		break;
	case 2: printf("승리");		break;
	}

	return 0;
}



#endif


