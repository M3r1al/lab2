#include "TestsUtils.hpp"

void GREEN(std::string s)
{
    std::cout << "\033[32m" << s << "\033[0m" << std::endl;
}

void GREEN(std::string s1, std::string s2)
{
    std::cout << "\033[32m" << s1 << s2 << "\033[0m" << std::endl;
}

void RED(std::string s)
{
    std::cout << "\033[31m" << s << "\033[0m" << std::endl;
}