#pragma once

/*
	student.h

	������ ������ ���� name, 3���� ������ ���Ҹ� ������ �迭 score, �� ���� total,
	����� average�� ����� ������ ����ü STUDENT�� ���Ͽ�, �ش� ����ü ������
	'Student ������'�� ���·ε� ������ �� �ֵ��� ����.
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

	//�Լ�������
	void (*SetName)(struct STUDENT*);
	void (*SetKorean)(struct STUDENT*);
	void (*SetEnglish)(struct STUDENT*);
	void (*SetMath)(struct STUDENT*);
	void (*PrintScore)(struct STUDENT*);
}
Student;

Student* Create();
void* Destroy(Student const* const student);
