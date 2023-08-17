// 01_03_auto_ptr.h
#pragma once

#include <iostream>

/*
   std::auto_ptr<T>
   - c++98 처음 추가
   - c++11 안쓰기로 함.
   - c++17 삭제
*/

// 간단하게 구현한 autoptr
template <class T>
class AutoPtr final
{
public:

    AutoPtr(T* ptr = nullptr)
        : ptr(ptr)
    {}

    // 소멸시 자동으로 해제하도록 만듬
    ~AutoPtr()
    {
        if (ptr != nullptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }

    // 복사 생성자 (move)
    // autoptr은 하나의 포인터를 여러개의 autoptr이 가지지 못하게 만든다.
    // unique point - 무조건 소유권을 하나만 갖는 것
    // 재정의 하여 이전 autoptr의 소유권을 상실 시킨다.
    AutoPtr(const AutoPtr& other)
    {
        ptr = other.ptr;  // other의 데이터 소유권을 넘겨줌
        other.ptr = nullptr; // other의 소유권을 상실 시킨다.
    }

    // 복사 대입 연산자
    AutoPtr& operator = (AutoPtr& other)
    {
        // 자기 자신일 경우 리턴
        if (&other == this)
            return *this;

        // 존재하는 데이터가 있다면 삭제
        if (ptr != nullptr)
        {
            delete ptr;
        }

        ptr = other.ptr; // other의 데이터 소유권을 넘겨줌
        other.ptr = nullptr; // other의 소유권을 상실 시킨다.

        // 본인의 참조 리턴
        return *this;
    }

    // 테스트용 함수
    void Test() {}

    // 포인터처럼 사용할 수 있게 연산자 재정의
    T& operator * () const { return *ptr; } //dereferencing operator
    T* operator -> () const { return ptr; } //member selection operator //반환타입 포인터


public:
    T* ptr = nullptr;

};