#include<stdio.h>
#include<stdlib.h>
#include"student/student.h"

/*
	����ü STUDENT�� ���� student�� 'Student ������' ��
	���·� ���� �� 0�� ��ȯ�ϴ� main �Լ��� ����
*/

int main()
{

	Student* student = Create();

	if (student != 0)
	{
		student->SetName(student);
		student->SetKorean(student);
		student->SetEnglish(student);
		student->SetMath(student);
		student->PrintScore(student);

		student = Destroy(student);
	}
	
	return 0;
}