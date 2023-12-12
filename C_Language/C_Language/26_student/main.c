#include<stdio.h>
#include<stdlib.h>
#include"student/student.h"

/*
	구조체 STUDENT의 변수 student를 'Student 변수명' 의
	형태로 생성 후 0을 반환하는 main 함수를 정의
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