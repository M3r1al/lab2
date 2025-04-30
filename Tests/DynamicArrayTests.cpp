#include "../Sequence.hpp"
#include <iostream>
#include <stdexcept>
#include "DynamicArrayTests.hpp"
#include "TestsUtils.hpp"

using namespace std;

void RunDynamicArrayTests()
{
    cout << "Testing DynamicArray" << endl;
    TestConstructorValidSize();
    TestCopyConstructorDynamicArray();
    TestInitializerConstructor();
    TestGetAndSet();
    TestSetOutOfRangeThrows();
    TestResizeLarger();
    TestResizeSmaller();
    TestResizeZeroThrows();
    TestOperatorAddition();
    TestOperatorAdditionSizeMismatchThrows();
    TestOperatorScalarMultiplication();
    TestDotProduct();
    TestDotProductSizeMismatchThrows();
    TestNorm();
}

void TestConstructorValidSize()
{
    DynamicArray<int> arr(10);
    if (arr.GetSize() != 10)
        RED("TestConstructorValidSize failed: Expected size 10, got ", arr.GetSize());
    else
        GREEN("TestConstructorValidSize passed");
}

void TestCopyConstructorDynamicArray()
{
    DynamicArray<int> arr1(5);
    for (size_t i = 0; i < 5; ++i)
        arr1.Set(i, i);
    DynamicArray<int> arr2 = arr1;
    for (size_t i = 0; i < 5; ++i)
    {
        if (arr2.Get(i) != arr1.Get(i))
        {
            RED("TestCopyConstructorDynamicArray failed: Error at index ", i);
            return;
        }
    }
    GREEN("TestCopyConstructorDynamicArray passed");
}

void TestInitializerConstructor()
{
    int values[] = {1, 2, 3, 4};
    DynamicArray<int> arr(values, 4);
    for (size_t i = 0; i < 4; ++i)
    {
        if (arr.Get(i) != values[i])
        {
            RED("TestInitializerConstructor failed: Error at index ", i);
            return;
        }
    }
    GREEN("TestInitializerConstructor passed");
}

void TestGetAndSet()
{
    DynamicArray<int> arr(3);
    arr.Set(0, 10);
    arr.Set(1, 20);
    arr.Set(2, 30);
    if (arr.Get(0) != 10)
    {
        RED("TestGetAndSet failed: Index 0 value mismatch");
        return;
    }
    if (arr.Get(1) != 20)
    {
        RED("TestGetAndSet failed: Index 1 value mismatch");
        return;
    }
    if (arr.Get(2) != 30)
    {
        RED("TestGetAndSet failed: Index 2 value mismatch");
        return;
    }
    GREEN("TestGetAndSet passed");
}

void TestGetOutOfRangeThrowsDynamicArray()
{
    DynamicArray<int> arr(3);
    try
    {
        arr.Get(5);
        RED("TestGetOutOfRangeThrowsDynamicArray failed: Exception not thrown");
    }
    catch (const out_of_range&)
    {
        GREEN("TestGetOutOfRangeThrowsDynamicArray passed");
    }
    catch (...)
    {
        RED("TestGetOutOfRangeThrowsDynamicArray failed: Wrong type of expection");
    }
}

void TestSetOutOfRangeThrows()
{
    DynamicArray<int> arr(3);
    try
    {
        arr.Set(5, 100);
        RED("TestSetOutOfRangeThrows failed: Excetion not thrown");
    }
    catch (const out_of_range&)
    {
        GREEN("TestSetOutOfRangeThrows passed");
    }
    catch (...)
    {
        RED("TestSetOutOfRangeThrows failed: Wrong type of exception");
    }
}

void TestResizeLarger()
{
    DynamicArray<int> arr(3);
    arr.Set(0, 10);
    arr.Set(1, 20);
    arr.Set(2, 30);
    arr.Resize(5);
    if (arr.GetSize() != 5)
    {
        RED("TestResizeLarger failed: Expected size 5, got ", arr.GetSize());
        return;
    }
    if (arr.Get(0) != 10)
    {
        RED("TestResizeLarger failed: Index 0 value mismatch");
        return;
    }
    if (arr.Get(1) != 20)
    {
        RED("TestResizeLarger failed: Index 1 value mismatch");
        return;
    }
    if (arr.Get(2) != 30)
    {
        RED("TestResizeLarger failed: Index 2 value mismatch");
        return;
    }
}

void TestResizeSmaller()
{
    DynamicArray<int> arr(5);
    for (size_t i = 0; i < 5; ++i)
        arr.Set(i, i * 10);
    arr.Resize(3);
    if (arr.GetSize() != 3)
    {
        RED("TestResizeSmaller failed: Expected size 3, got ", arr.GetSize());
        return;
    }
    for (size_t i = 0; i < 3; ++i)
    {
        if (arr.Get(i) != i * 10)
        {
            RED("TestResizeSmaller failed: Error at index ", i);
            return;
        }
    }
    GREEN("TestResizeSmaller passed");
}

void TestResizeZeroThrows()
{
    DynamicArray<int> arr(5);
    try
    {
        arr.Resize(0);
        RED("TestResizeZeroThrows failed: Exception not thrown");
    }
    catch (const invalid_argument&)
    {
        GREEN("TestResizeZeroThrows passed");
    }
    catch (...)
    {
        RED("TestResizeZeroThrows failed: Wrong type of exception");
    }
}

void TestOperatorAddition()
{
    DynamicArray<int> arr1(3);
    DynamicArray<int> arr2(3);
    for (size_t i = 0; i < 3; ++i)
    {
        arr1.Set(i, i + 1);
        arr2.Set(i, (i + 1) * 2);
    }
    DynamicArray<int> result = arr1 + arr2;
    if (result.Get(0) != 3)
    {
        RED("TestOperatorAddition failed: Index 0 value mismatch");
        return;
    }
    if (result.Get(1) != 6)
    {
        RED("TestOperatorAddition failed: Index 1 value mismatch");
        return;
    }
    if (result.Get(2) != 9)
    {
        RED("TestOperatorAddition failed: Index 0 value mismatch");
        return;
    }
    GREEN("TestOperatorAddition passed");
}

void TestOperatorAdditionSizeMismatchThrows()
{
    DynamicArray<int> arr1(3);
    DynamicArray<int> arr2(4);
    try
    {
        arr1 + arr2;
        RED("TestOperatorAdditionSizeMismatchThrows failed: Exception not thrown");
    }
    catch (const invalid_argument&)
    {
        GREEN("TestOperatorAdditionSizeMismatchThrows passed");
    }
    catch (...)
    {
        RED("TestOperatorAdditionSizeMismatchThrows failed: Wrong type of exception");
    }
}

void TestOperatorScalarMultiplication()
{
    DynamicArray<int> arr(3);
    for (size_t i = 0; i < 3; ++i)
        arr.Set(i, i + 1);
    DynamicArray<int> result = arr * 2;
    if (result.Get(0) != 2)
    {
        RED("TestOperatorScalarMultiplication failed: Index 0 value mismatch");
        return;
    }
    if (result.Get(1) != 4)
    {
        RED("TestOperatorScalarMultiplication failed: Index 1 value mismatch");
        return;
    }
    if (result.Get(2) != 6)
    {
        RED("TestOperatorScalarMultiplication failed: Index 2 value mismatch");
        return;
    }
    GREEN("TestOperatorScalarMultiplication");
}

void TestDotProduct()
{
    DynamicArray<int> arr1(3);
    DynamicArray<int> arr2(3);
    for (size_t i = 0; i < 3; ++i)
    {
        arr1.Set(i, i + 1);
        arr2.Set(i, (i + 1) * 2);
    }
    if (arr1.Dot(arr2) != 28)
    {
        RED("TestDotProduct failed: Expected 28, got ", arr1.Dot(arr2));
        return;
    }
    GREEN("TestDotProduct passed");
}

void TestDotProductSizeMismatchThrows()
{
    DynamicArray<int> arr1(3);
    DynamicArray<int> arr2(4);
    try
    {
        arr1.Dot(arr2);
        RED("TestDotProductSizeMismatchThrows failed: Exception not thrown");
    }
    catch (const invalid_argument&)
    {
        GREEN("TestDotProductSizeMismatchThrows passed");
    }
    catch (...)
    {
        RED("TestDotProductSizeMismatchThrows failed: Wrong type of exception");
    }
}

void TestNorm()
{
    DynamicArray<int> arr(3);
    arr.Set(0, 3);
    arr.Set(1, 4);
    arr.Set(2, 12);
    if (fabs(arr.Norm() - 13) > 1e-6)
    {
        RED("TestNorm failed: Expected 13, got ", arr.Norm());
        return;
    }
    GREEN("TestNorm passed");
}