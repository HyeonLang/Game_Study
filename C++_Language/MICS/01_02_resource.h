// 01_02_resource.h
#pragma once

#include <iostream>

class Resource final
{
public:
    Resource()
    {
        std::cout << "Resource constructor" << std::endl;
    }
    ~Resource()
    {
        std::cout << "Resource destructor" << std::endl;
    }
};