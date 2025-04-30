#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <cerrno>
#include <string>
#include "Sequence.hpp"
#include "Tests/Tests.hpp"

using namespace std;

// Если через cin ввести 1в например, то программа сломается. В лабе есть пункт про некорректные исходные данные
int GetNumber()
{
    string input;
    int num;
    while (true)
    {
        getline(cin, input);
        if (input.empty())
        {
            cout << "Input contain something" << endl;
            continue;
        }
        char *end;
        errno = 0;
        num = strtol(input.c_str(), &end, 10);
        if (end == input.c_str()) // Ничего не прочитано
            cout << "Input must be a number" << endl;
        else if (*end != '\0') // Символы после числа
            cout << "Input must consist of numbers only" << endl;
        else if (errno == ERANGE) // Число слишком большое/маленькое
            cout << "Input must be in the correct range" << endl;
        else
            return num;
        cout << "Input number: ";
    }
}

// тут для положительного числа, границы другие немного, поэтому удобнее в другую функцию,
// чтобы еще и проверку дополнительно потом не делать
size_t GetPositiveNumber()
{
    string input;
    size_t num;
    while (true)
    {
        getline(cin, input);
        if (input.empty())
        {
            cout << "Input contain something" << endl;
            continue;
        }
        char *end;
        errno = 0;
        num = strtol(input.c_str(), &end, 10);
        if (end == input.c_str()) // Ничего не прочитано
            cout << "Input must be a number" << endl;
        else if (*end != '\0') // Символы после числа
            cout << "Input must consist of numbers only" << endl;
        else if (input[0] == '-') // Отрицательное число
            cout << "Input must be a positive number" << endl;
        else if (errno == ERANGE) // Число слишком большое
            cout << "Input must be in correct range" << endl;
        else
            return num;
        cout << "Input positive number: ";
    }
}

void DynamicArrayInterface()
{
    cout << "Enter initial size of the DynamicArray: ";
    size_t size = GetPositiveNumber();
    DynamicArray<int> arr(size);

    int choice, value, index;
    while (true)
    {
        cout << "\nDynamicArray Menu:\n";
        cout << "1. Set Value\n2. Get Value\n3. Resize\n4. Get Size\n5. Print array\n6. Exit\nChoose an option: ";
        choice = GetNumber();

        try
        {
            switch (choice)
            {
                case 1:
                    cout << "Enter index: ";
                    index = GetNumber();
                    cout << "Enter value to set: ";
                    value = GetNumber();
                    arr.Set(index, value);
                    break;
                case 2:
                    cout << "Enter index to get value: ";
                    index = GetNumber();
                    cout << "Value: " << arr.Get(index) << endl;
                    break;
                case 3:
                    cout << "Enter new size: ";
                    size = GetPositiveNumber();
                    arr.Resize(size);
                    break;
                case 4:
                    cout << "Current size: " << arr.GetSize() << endl;
                    break;
                case 5:
                    cout << "Current array: " << arr.ToString() << endl;
                    break;
                case 6:
                    return;
                default:
                    cout << "Invalid option.\n";
                    break;
            }
        }
        catch (const exception& e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }
}

int main()
{
    RunAllTests();

    cout << "All tests completed!\n";

    DynamicArrayInterface();
    
    return 0;
}