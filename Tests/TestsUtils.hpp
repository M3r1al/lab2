#ifndef TESTSUTILS_HPP
#define TESTSUTILS_HPP

#include <iostream>
#include <string>

void GREEN(std::string s);

void RED(std::string s);

template<typename T>
void RED(std::string s, T p)
{
    std::cout << "\033[31m" << s << p << "\033[0m" << std::endl;
}

template<typename T1, typename T2>
void RED(std::string s1, T1 l1, std::string s2, T2 l2)
{
    std::cout << "\033[31m" << s1 << l1 << s2 << l2 << "\033[0m" << std::endl;
}

#endif