// 과제
// chrono조사 

#include <iostream>
#include <chrono>
#include <cmath>

/*
    * chorono 란?

        - C++11에서 추가된 시간에 관련된 라이브러리
        - 기존의 C 런타임에서 제공하는 time 함수보다 다양한 기능을 제공하며, C의 time 보다 사용이 쉽고 정밀도가 훨씬 높다.
        - 시간끼리도 연산이 가능 (time 함수를 쓰면 시간이 살짝 어긋나는 경우 有. chrono를 적극 이용하자.
*/

// 예) for문 돌아가는데 걸린 시간

int main()
{
    // 현재 시간 now를 start 변수에 저장
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    // for문을 돌리면서 시간의 합 sum을 
    int sum = 0;
    for (int i = 0; i < 999999999; i++)
        sum += i;

    // '새로운' 현재시간 now에 처음 시작시간인 start를 뺀 것을 더블형 sec 에 저장
    std::chrono::duration<double>sec = std::chrono::system_clock::now() - start;
    std::cout << "for문을 돌리는데 걸리는 시간(초) : " << sec.count() << "seconds" << std::endl;

    // 출력시) for문을 돌리는데 걸리는 시간(초) : 0.581512seconds

/*
    여기서 time_point는 시간상의 한 축을 의미.

    for문을 실행하여 다시 현재 시각을 얻은 후에 for문을 시작하기 전 저장한 현재 시각을 빼면 for문을 수행하는 데 걸린 시간을 얻을 수 있다.

    chrono에서 경과 시 간을 나타낼 때 duration 클래스를 사용하는데, duration은 6가지 시간 단위를 지원한다.

        - duration 지원 시간 단위

            std::chrono::nanoseconds    : 나노세컨드 (1/10억 초)
            std::chrono::microseconds   : 마이크로 세컨드 (1/100만 초)
            std::chrono::milliseconds   : 밀리 세컨드 (1/1000 초)
            std::chrono::seconds        : 초
            std::chrono::minutes        : 분
            std::chrono::hours          : 시

        - clock 클래스

            chrono에는 system_clock뿐만 아니라 steady_clock와 high_resolution_clock도 있다.

            1) system_clock         : 가장 일반적으로 사용하는 것으로, 시스템 시간을 나타낸다. (C 런타임의 time_t와 호환)

            2) steady_clock         : 물리적 시간처럼 결코 역행하지 않는 시간을 나타낸다.
                                      즉, steady_clock 이외의 clock 클래스는 time_point를 얻은 후 OS에서 날짜를 과거로 되돌린 후에 time_point를 얻으면 앞에 얻은 시간을 얻지만,
                                      steady_clock에서는 그럴 수 없다.
                                      따라서 '시간의 흐름이 바뀌지 않는 시간'을 얻고 싶을 때 steady_clock를 사용하면 된다.

            3) high_resolution_clock : Windows 또는 Linux에서 제공하는 정밀도가 가장 높은 시간.
                                       이 클래스는 system_clock이나 steady_clock의 다른 별칭으로 정의되기도 한다.
*/


// chrono를 이용해 timer 만들기

// 현재 시간 now 를 startTime 변수에 저장
    auto startTime = std::chrono::system_clock::now();

    // 시간간격 second 변수가 초단위(1초씩++) 변수 Sec 보다 크면 초당 "(몇초) " 찍히게 무한으로(while) 돌려줌
    int Sec = 0;
    while (1)
    {
        // endTime 에 현재 시간 now를 저장
        auto endTime = std::chrono::system_clock::now();
        // endTime 에서 처음시간 저장했던 startTime 뺀 것을 second 에 저장(시간 간격)
        auto second = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        // 그 간격이 
        if (second.count() > Sec)
        {
            Sec++;
            std::cout << Sec << " ";
        }
    }

    return 0;
}