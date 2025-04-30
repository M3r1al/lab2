#include "TestsUtils.hpp"

void GREEN(std::string s)
{
    std::cout << "\033[32m" << s << "\033[0m" << std::endl;
}

void RED(std::string s)
{
    std::cout << "\033[31m" << s << "\033[0m" << std::endl;
}