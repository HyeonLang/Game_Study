// 09_for.cpp

/*
	for문 
	- 명령문을 정해진 횟수만큼 실행하고 싶을 때 자주 사용한다.
	- 초기식, 조건식, 증감식을 포함하고 있으며 사용자의 목적에
	따라 생략할 수 있다.

	for(초기식 ; 조건식 ; 증감식)
	{
		명령문
	}

	실행 순서
	1. 초기식 수행 : 주로 for문을 시작하기전에 사용할 값을 선언한다
	2. 조건식 검사 : true인 경우 명령문 실행, false라면 for문 종료
	3. 명령문 실행 
	4. 증감식 수행 : 증감식을 수행한 후에 2번(조건식)으로 이동한다..
*/

#include<stdio.h>

int main()
{
    for (int i = 1; i <= 5; i++)
    {
        printf("for문 명령어 %d번 반복중\n", i);
    }

    /*
       for문과 while문의 차이
       작성 형식의 차이가 있어 주로 사용처가 다를 뿐
       for문을 while문처럼 while문을 for문처럼 사용할 수 있다.
    */

    //for (;;)
    //{
    //   printf("무한루프\n");
    //}

    //int i = 0;
    //while (1)
    //{
    //   if (i > 4)
    //   {
    //      break;
    //   }

    //   printf("while문 %d번 반복중\n", i);

    //   i++;
    //}

    /*
       문제
       1. 정수형 변수 num에 사용자로부터 입력을 받는다.
       2. 0 ~ num 까지의 값을 더한다.
       3. 더한값을 출력

       짝수값만 더했을때 값 출력
       홀수값만 더했을때 값 출력
    */

    //int num = 0;
    //int result = 0;
    //printf("num 입력 : ");
    //scanf_s("%d", &num);
    //for (int i = 0; i <= num; i++)
    //   result += i;
    //printf("0 ~ %d 합 : %d\n", num, result);

    //int num = 0;
    //int result = 0;
    //printf("num 입력 : ");
    //scanf_s("%d", &num);
    //for (int i = 0; i <= num; i++)
    //   if(i % 2 == 0)
    //      result += i;
    //printf("0 ~ %d 짝수 합 : %d\n", num, result);

    //int num = 0;
    //int result = 0;
    //printf("num 입력 : ");
    //scanf_s("%d", &num);
    //for (int i = 0; i <= num; i++)
    //   if (i % 2 == 1)
    //      result += i;
    //printf("0 ~ %d 홀수 합 : %d\n", num, result);

    /*
       중첩 for문
    */

    for (int i = 2; i < 10; i++)
    {
        printf("%d단 시작\n", i);
        for (int j = 1; j < 10; j++)
        {
            printf("%d x %d = %02d\n", i, j, i * j);
        }
        printf("\n");
    }

    // 별그리기
    // *****
    // *****
    // *****
    // *****
    // *****
    //for (int i = 0; i < 5; i++)
    //{
    //    for (int j = 0; j < 5; j++)
    //        printf("*");
    //    printf("\n");
    //}

    // 별그리기
    // *        i = 0 j : 0
    // **       i = 1 j : 0, 1
    // ***      i = 2 j : 0, 1, 2
    // ****     i = 3 j : 0, 1, 2, 3
    // *****    i = 4 j : 0, 1, 2, 3, 4

  //  for (int i = 0; i < 5; i++)
  //  {
  //     /* for (int j = 0; j < 5; j++)
  //          if (j <= i)
  //              printf("*");*/

		//for (int j = 0; j < i + 1; j++)
		//		printf("*");

  //      printf("\n");
  //  }

    // ***** 00 ~ 04 / 5 -> 0 0 0 0 0   
    // ***** 05 ~ 09 / 5 -> 1 1 1 1 1
    // ***** 10 ~ 14 / 5 -> 2 2 2 2 2
    // ***** 15 ~ 19 / 5 -> 3 3 3 3 3
    // ***** 20 ~ 24 / 5 -> 4 4 4 4 4

    // 12345 00 ~ 04 % 5 -> 0 1 2 3 4
    // 12345 05 ~ 09 % 5 -> 0 1 2 3 4
    // 12345 10 ~ 14 % 5 -> 0 1 2 3 4
    // 12345 15 ~ 19 % 5 -> 0 1 2 3 4
    // 12345 20 ~ 24 % 5 -> 0 1 2 3 4
    
    int pre_num = 0;
    int cur_num = 0;
    for (int i = 0; i < 25; i++)
    {
        cur_num = i / 5;

        if (cur_num != pre_num)
        {
            printf("\n");
            pre_num = cur_num;
        }
        printf("%d", i % 5 + 1);
    }

    return 0;
}

// 과제 : 별그리기

//*****
//****
//***
//**
//*

//*****
// ****
//  ***
//   **
//    *
// '*' 와 ' ' 사용해 출력하기