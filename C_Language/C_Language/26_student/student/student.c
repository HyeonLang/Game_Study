#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "student.h"

/*
	구조체 STUDENT의 포인터와, 문자열을 전달받아, STUDENT의 포인터가
	가리키는 공간의 name에 해당 문자열의 크기만큼의 새로운 공간을 할당하고
	문자열을 복사하는 함수 SetName 을 정의한 뒤, 해당 함수의 접근 범위를 현재 파일 내로 한정
*/

/*
	정적 함수
	- 함수 앞에 static 키워드가 붙은 함수
	- 외부에서 바로 접근이 안되고 정적 함수와 같은 파일에 존재하는 코드안에서 호출이 가능하다.
*/
static void SetName(Student* const student)
{
	char name[100] = { 0 };

	printf("학생 이름 : ");
	scanf_s("%s", name, (unsigned int)sizeof(name));

	int const count = strlen(name) + sizeof(char);

	student->name = calloc(count, sizeof(char));

	if (student->name == NULL)
		return;

	strcpy_s(student->name, count, name);
}

/*
	정수형 변수의 포인터를 전달받아 해당 공간의 값을 사용자로부터
	입력받은 접수로 변경하는 함수 SetScore를 정의하고, 해당 함수를 이용하여
	구조체 STUDENT의 포인터를 전달받는 세 함수 SetKorean, SetEnglish, SetMath를 
	정의한 뒤, 네 함수의 접근 범위를 모두 현재 파일 내로 한정.
*/

static void SetScore(Student* const student, Subject const subject)
{
	printf("점수 : ");
	scanf_s("%d", &student->score[subject]);
}

static void SetKorean(Student* const student){ printf("국어 ");SetScore(student, korean);}

static void SetEnglish(Student* const student){printf("영어 ");SetScore(student, english);}

static void SetMath(Student* const student){printf("수학 ");SetScore(student, math);}

static void PrintScore(Student* const student)
{
	student->total = 0;

	for (int i = min; i <= max; i++)
		student->total += student->score[i];

	student->average = student->total / (float)(count);

	printf_s("학생 이름 : %s\n", student->name);
	printf_s("국어 점수 : %u\n", student->score[korean]);
	printf_s("영어 점수 : %u\n", student->score[english]);
	printf_s("수학 점수 : %u\n", student->score[math]);
	printf_s("합산 점수 : %u\n", student->total);
	printf_s("평균 점수 : %f\n", student->average);
}

Student* Create()
{
	Student* const student = calloc(1, sizeof(Student));

	if (student == NULL)
		return NULL;

	student->SetName	= SetName;
	student->SetKorean	= SetKorean;
	student->SetEnglish	= SetEnglish;
	student->SetMath	= SetMath;
	student->PrintScore	= PrintScore;

	return student;
}

void* Destroy(Student const* const student)
{
	free(student->name);
	free(student);

	return NULL;
}
