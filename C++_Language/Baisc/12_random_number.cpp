// 12_random_number.cpp

#include<iostream>

// c  난수
#include<stdlib.h>
#include<time.h>

// c++ 난수
#include<random>

int main()
{
    /*
        c style 난수의 문제점
        - 시드값을 현재시간으로 하기 때문에 같은 시간대의 프로그램이 동일한 시드값을 가진다.
        - %연산자를 사용해 값의 범위를 줄이므로 균등히 배분되지 않을 수 있다.
        - rand() 자체의 난수 알고리즘이 좋지 않다.
    */
    {
        srand((unsigned int)time(NULL));

        for (int i = 0; i < 10; i++)
            printf("%d, ", rand() % 10);
        printf("\n");
    }

    //c++ style
    {
        std::random_device rd; //하드웨어 시리얼 넘버 사용 : 시드값 랜덤한 난수 생성
        
        std::mt19937_64 messenne(rd()); //rand() 역할, 시드값 매개변수:2^19937_64bit

        std::uniform_int_distribution<> dice(1, 6); //정수 난수 범위 지정

        //std::uniform_real_distribution<> 실수

        for (int i = 0; i < 10; i++) {
            std::cout << dice(messenne) << ", "; //난수 생성
        }
        std::cout << std::endl;
    }

    return 0;
}