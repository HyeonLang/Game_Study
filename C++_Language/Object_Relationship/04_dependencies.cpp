// 04_dependencies.cpp
// 의존

#include<iostream>
#include<chrono> // 시간 관련 라이브러리 : 정밀한 시간 단위 측정
using namespace std;
using namespace std::chrono; // 시간 관련 함수

class Timer //시간 측정 클래스 제작
{
public:
	Timer()
	{
		start_time = high_resolution_clock::now(); //현재시간으로 초기화
	}

	void Elapsed() //경과
	{
		auto current_time = high_resolution_clock::now(); // 지나온 시간 - 현재시간
		
		//milli단위를 double형으로 시간 저장
		duration<double, std::milli> delta = current_time - start_time; // 두 시간 차이에 대한 정보를 double형의 milli로 받음

		//함수 호출 간격을 재고싶을 때
		//start_time = current_time;

		cout << delta.count() << std::endl; //count() : delta의 시간 리턴
	}
private:
	time_point<high_resolution_clock> start_time;// 시간을 측정하는 자료형 객체
};

class Worker
{
public:
	void DoSomething()
	{
		// 의존 관계
		// 필요할 때만 가져다 쓰는 관계 : 시간측정을 위한 Timer 클래스 사용
		Timer timer; //지역 변수 : 필요를 다하면 지워버림
		for (int i = 0; i < 100'000'000; i++)
			;
		timer.Elapsed(); //for문이 모두 끝난 후의 시간을 측정
	}
};

int main()
{
	Worker w;
	w.DoSomething();

	return 0;
}

// 과제
// chrono조사 

