#pragma once

/*
	student.h

	문자형 포인터 변수 name, 3개의 정수형 원소를 가지느 배열 score, 그 합인 total,
	평균인 average를 멤버로 가지는 구조체 STUDENT에 대하여, 해당 구조체 변수를
	'Student 변수명'의 형태로도 생성할 수 있도록 정의.
*/

typedef enum
{
	min,			// 0
	korean = min,	// 0
	english,		// 1
	math,			// 2
	max = math,		// 2
	count			// 3
}
Subject;

typedef struct STUDENT
{
	char*	name;
	int		score[count];
	int		total;
	float	average;

	//함수포인터
	void (*SetName)(struct STUDENT*);
	void (*SetKorean)(struct STUDENT*);
	void (*SetEnglish)(struct STUDENT*);
	void (*SetMath)(struct STUDENT*);
	void (*PrintScore)(struct STUDENT*);
}
Student;

Student* Create();
void* Destroy(Student const* const student);
