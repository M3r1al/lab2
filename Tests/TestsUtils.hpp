#ifndef TESTSUTILS_HPP
#define TESTSUTILS_HPP

#include <iostream>
#include <string>

void GREEN(std::string s);

void GREEN(std::string s1, std::string s2);

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

template<typename T1, typename T2>
void RED(std::string s1, T1 l1, T2 l2)
{
    std::cout << "\033[31m" << s1 << l1 << l2 << "\033[0m" << std::endl;
}

template<typename T1, typename T2>
void RED(std::string s1, std::string s2, T1 l1, std::string s3, T2 l2)
{
    std::cout << "\033[31m" << s1 << s2 << l1 << s3 << l2 << "\033[0m" << std::endl;
}

template<typename T1, typename T2>
void RED(std::string s1, std::string s2, size_t i, std::string s3, T1 l1, std::string s4, T2 l2)
{
    std::cout << "\033[31m" << s1 << s2 << i << s3 << l1 << s4 << l2 << "\033[0m" << std::endl;
}

#endif