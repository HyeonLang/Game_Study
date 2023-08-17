// 02_02_resource.h
#pragma once

#include <iostream>

class Resource
{
public:
    Resource()
    {
        std::cout << "Resource constructor" << std::endl;
    }

    Resource(unsigned length)
    {
        std::cout << "Resource length constructor" << std::endl;

        this->data = new int[length];
        this->length = length;
    }

    Resource(const Resource& rhs) // ±Ì¿∫ ∫πªÁ
    {
        std::cout << "Resource copy constructor" << std::endl;

        this->data = new int[rhs.length];
        this->length = rhs.length;

        for (unsigned i = 0; i < length; i++)
            data[i] = rhs.data[i];
    }

    ~Resource()
    {
        std::cout << "Resource destructor" << std::endl;

        if (data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }

    Resource& operator = (const Resource& rhs) // ±Ì¿∫ ∫πªÁ
    {
        std::cout << "Resource copy assignment operator" << std::endl;

        if (&rhs == this)
            return *this;

        if (data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }

        length = rhs.length;
        data = new int[length];

        for (unsigned i = 0; i < length; i++)
            data[i] = rhs.data[i];

        return *this;
    }

    void Print()
    {
        for (unsigned i = 0; i < length; i++)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }

    void SetAll(const int& value)
    {
        for (unsigned i = 0; i < length; i++)
            data[i] = value;
    }

private:
    int* data = nullptr;
    unsigned length = 0;
};