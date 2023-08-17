// 01_03_auto_ptr.h
#pragma once

#include <iostream>

/*
   std::auto_ptr<T>
   - c++98 ó�� �߰�
   - c++11 �Ⱦ���� ��.
   - c++17 ����
*/

// �����ϰ� ������ autoptr
template <class T>
class AutoPtr final
{
public:

    AutoPtr(T* ptr = nullptr)
        : ptr(ptr)
    {}

    // �Ҹ�� �ڵ����� �����ϵ��� ����
    ~AutoPtr()
    {
        if (ptr != nullptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }

    // ���� ������ (move)
    // autoptr�� �ϳ��� �����͸� �������� autoptr�� ������ ���ϰ� �����.
    // unique point - ������ �������� �ϳ��� ���� ��
    // ������ �Ͽ� ���� autoptr�� �������� ��� ��Ų��.
    AutoPtr(const AutoPtr& other)
    {
        ptr = other.ptr;  // other�� ������ �������� �Ѱ���
        other.ptr = nullptr; // other�� �������� ��� ��Ų��.
    }

    // ���� ���� ������
    AutoPtr& operator = (AutoPtr& other)
    {
        // �ڱ� �ڽ��� ��� ����
        if (&other == this)
            return *this;

        // �����ϴ� �����Ͱ� �ִٸ� ����
        if (ptr != nullptr)
        {
            delete ptr;
        }

        ptr = other.ptr; // other�� ������ �������� �Ѱ���
        other.ptr = nullptr; // other�� �������� ��� ��Ų��.

        // ������ ���� ����
        return *this;
    }

    // �׽�Ʈ�� �Լ�
    void Test() {}

    // ������ó�� ����� �� �ְ� ������ ������
    T& operator * () const { return *ptr; } //dereferencing operator
    T* operator -> () const { return ptr; } //member selection operator //��ȯŸ�� ������


public:
    T* ptr = nullptr;

};