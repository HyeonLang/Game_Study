// 07_dead_lock.cpp

#include<iostream>  
#include<thread>
#include<chrono>
#include<mutex> // mutual exlusion : 상호 배제
using namespace std;

//=================================
// dead lock 문제 확인과 해결 1
//=================================
mutex mtx1;

int main()
{
    //====================
    // dead lock 문제 확인
    //====================

    auto worker1 = []()
    {

        for (int i = 0; i < 1000; i++)
        {
            mtx1.lock();

            // 해당 공간이 해제되기전에 종료되어 공간을 해제하지 못함.
            // -> 해당 공간이나 자원이 풀리기를 무한히 대기함 -> dead lock
            if (i == 10)
                return; //early return 

            mtx1.unlock();
        }

    };

    //====================
    // dead lock 문제 해결
    //====================
    auto solution = []()
    {

        for (int i = 0; i < 1000; i++)
        {
            /*
               lock_guard를 사용하여 해결가능
                  - 생성과 동시에 받은 mutex의 lock()을 호출한다.
                  - lock_guard가 소멸하면서 받은 mutex의 unlock()를 호출한다.
            */
            lock_guard<mutex> guard(mtx1);

            if (i == 10)
                return;
        }

    };

    return 0;
}

//=================================
// dead lock 문제 확인과 해결 2
//=================================
mutex mtx1;
mutex mtx2;

int main()
{
    //====================
    // dead lock 문제 확인
    //====================
    //auto worker1 = []()
    //{

    //   for (int i = 0; i < 1000; i++)
    //   {
    //      lock_guard<mutex> guard1(mtx1);
    //      lock_guard<mutex> guard2(mtx2);
    //   }

    //};

    //auto worker2 = []()
    //{
    //   for (int i = 0; i < 1000; i++)
    //   {
    //      lock_guard<mutex> guard2(mtx2);
    //      lock_guard<mutex> guard1(mtx1);
    //   }
    //};

    //thread t1(worker1);
    //thread t2(worker2);

    //t1.join();
    //t2.join();

    /*
       실행결과 -> 프로그램이 종료하지 않는다.

       worker1 : mtx1를 lock하고 mtx2를 lock한다.
       worker2 : mtx2를 lock하고 mtx1을 lock한다.

       이 코드에서 woker1에서 mtx1를 lock()하고 work2에서 mtx2를 lock()하게 된다면
       worker1은 mtx2를 lock()하지 못하게 되고 worker2가 mtx2를 unlock()할때까지 대기한다.
       하지만 worker2는 mtx1이 unlock() 될때까지 대기해야 하기 때문에 mtx2를 unlock()을 하지못한다.
       -> 서로가 서로의 자원이 해제되기를 무한히 대기함 -> dead lock()

       해결 방법 중 하나로는 한 스레드에게 우선권을 주는 방법이있다.
    */

    //====================
    // dead lock 문제 해결
    //====================
    auto worker1 = []()
    {
        for (int i = 0; i < 10; i++)
        {
            mtx1.lock();
            mtx2.lock();

            printf("mtx1 working!\n");

            mtx2.unlock();
            mtx1.unlock();
        }
    };

    auto worker2 = []()
    {
        for (int i = 0; i < 10; i++)
        {
            mtx2.lock();

            //try_lock() : lock()할 수 있다면 lock()을 한 후 true 반환. 
            //            lock()할 수 없다면 대기하지 않고 false 반환.
            // -> mtx1이 잠겨 있다면 worker2가 다른 스레드가 먼저 처리하도록 양보를 한 것
            if (mtx1.try_lock() == false)
            {
                mtx2.unlock();
                continue;
            }


            printf("mtx2 working!\n");

            mtx2.unlock();
            mtx1.unlock();
        }
    };

    thread t1(worker1);
    thread t2(worker2);

    t1.join();
    t2.join();

    /*
       문제는 해결했지만 기아 상태를 발생시킬 수 있다.
       -> 스레드 사이의 우위가 생겨 한 스레드만 작업을 하고 다른 스레드는 작업을 하지 못하는 상황

       데드락 상황을 피하기 위한 가이드 라인
          - 중첩된 Lock을 사용하는 것을 피해라.
             -> 모든 스레드가 lock()을 하나만 사용한다면 데드락을 피할 수 있다.

          - Lock을 소유하고 있을 때 유저 코드를 호출하는 것을 피해라.
             -> 유저 코드 내부에 Lock()이 있을 수 있기 때문에 중첩될 수 있다.

          - 여러개의 Lock()들을 얻어야 한다면 언제나 정해진 순서로 획득해라.
             -> 위의 우리가 발생한 상황도 lock을 얻는 순서가 서로 달라 생긴 문제이다.
             만약에 정해진 순서대로 받았다면 데드락은 발생하지 않았을 것이다.
    */

    return 0;
}