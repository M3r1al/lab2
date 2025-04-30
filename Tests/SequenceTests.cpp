#include <iostream>
#include <stdexcept>
#include "SequenceTests.hpp"

using namespace std;

void RunSequenceTests()
{
    cout << "Testing Sequence" << endl;
    // Тесты для Immutable
    TestImmutableArrayAppend();
    TestImmutableArrayPrepend();
    TestImmutableListAppend();
    TestImmutableListPrepend();

    // Тесты для Mutable
    TestMutableArrayAppend();
    TestMutableArrayPrepend();
    TestMutableListAppend();
    TestMutableListPrepend();

    // Общие тесты
    TestConcatWithEmpty();
}

// Тесты для ImmutableArraySequence
void TestImmutableArrayAppend()
{
    int values_a[] = {1, 2};
    ImmutableArraySequence<int> a(values_a, 2);
    auto newA = a.Append(3);
    if (a.GetLength() != 2)
    {
        RED("TestImmutableArrayAppend failed: Expected original length 2, got ", a.GetLength());
        return;
    }
    if (newA->GetLength() != 3)
    {
        RED("TestImmutableArrayAppend failed: Expected new length 3, got ", newA->GetLength());
        return;
    }
    GREEN("TestImmutableArrayAppend passed");
}

void TestImmutableArrayPrepend()
{
    int values_a[] = {2, 3};
    ImmutableArraySequence<int> a(values_a, 2);
    auto newA = a.Prepend(1);
    if (newA->Get(0) != 1 || newA->Get(1) != 2)
    {
        RED("TestImmutableArrayPrepend failed: Values mismatch");
        return;
    }
    if (a.GetLength() != 2)
    {
        RED("TestImmutableArrayPrepend failed: Expected original length 2, got ", a.GetLength());
        return;
    }
    GREEN("TestImmutableArrayPrepend passed");
}

// Тесты для MutableListSequence
void TestMutableArrayAppend()
{
    int values_a[] = {1, 2};
    MutableArraySequence<int> a(values_a, 2);
    TestMutableSequenceAppend(a, 3, 3);
}

void TestMutableArrayPrepend()
{
    int values_a[] = {2, 3};
    MutableArraySequence<int> a(values_a, 2);
    auto newA = a.Prepend(1);
    if (newA != &a || a.Get(0) != 1 || a.Get(1) != 2)
    {
        RED("TestMutableArrayPrepend failed: Values mismatch");
        return;
    }
    GREEN("TestMutableArrayPrepend passed");
}

// Тесты для List-версий
void TestImmutableListAppend()
{
    int values_a[] = {1, 2};
    ImmutableListSequence<int> a(values_a, 2);
    auto newA = a.Append(3);
    if (newA->GetLength() != 3)
    {
        RED("TestImmutableListAppend failed: Expected length 3, got ", newA->GetLength());
        return;
    }
    if (a.GetLength() != 2)
    {
        RED("TestImmutableListAppend failed: Expected original length 2, got ", a.GetLength());
        return;
    }
    GREEN("TestImmutableListAppend passed");
}

void TestMutableListAppend()
{
    int values_a[] = {1, 2};
    MutableListSequence<int> a(values_a, 2);
    TestMutableSequenceAppend(a, 3, 3);
}

// Аналогично для Prepend
void TestImmutableListPrepend()
{
    int values_a[] = {2, 3};
    ImmutableListSequence<int> a(values_a, 2);
    auto newA = a.Prepend(1);
    if (newA->Get(0) != 1 || newA->Get(1) != 2)
    {
        RED("TestImmutableListPrepend failed: Values mismatch");
        return;
    }
    if (a.GetLength() != 2)
    {
        RED("TestImmutableListPrepend failed: Original length changed to ", a.GetLength());
        return;
    }
    GREEN("TestImmutableListPrepend passed");
}

void TestMutableListPrepend()
{
    int values_a[] = {2, 3};
    MutableListSequence<int> a(values_a, 2);
    auto newA = a.Prepend(1);
    if (newA != &a || a.Get(0) != 1 || a.Get(1) != 2)
    {
        RED("TestMutableListPrepend failed: Values mismatch");
        return;
    }
    GREEN("TestMutableListPrepend passed");
}

/* 
 * Тесты для проверки различий
 */
void TestMutabilityDifferences()
{
    int values_a[] = {2, 3};
    int values_b[] = {1, 2};
    // Проверка Array
    MutableArraySequence<int> mutableArr(values_a, 2);
    ImmutableArraySequence<int> immutableArr(values_a, 2);

    // Изменение Mutable
    mutableArr.Append(3);
    if (mutableArr.GetLength() != 3)
    {
        RED("TestMutabilityDifferences failed (Array): Mutable length mismatch");
        return;
    }

    // Проверка, что Immutable не изменился
    immutableArr.Append(3);
    if (immutableArr.GetLength() != 2)
    {
        RED("TestMutabilityDifferences failed (Array): Immutable was modified");
        return;
    }

    // Проверка List
    MutableListSequence<int> mutableList(values_b, 2);
    ImmutableListSequence<int> immutableList(values_b, 2);

    // Изменение Mutable
    mutableList.Append(3);
    if (mutableList.GetLength() != 3)
    {
        RED("TestMutabilityDifferences failed (List): Mutable length mismatch");
        return;
    }

    // Проверка, что Immutable не изменился
    immutableList.Append(3);
    if (immutableList.GetLength() != 2)
    {
        RED("TestMutabilityDifferences failed (List): Immutable was modified");
        return;
    }

    GREEN("TestMutabilityDifferences passed");
}

// Дополнительные тесты
void TestConcatWithEmpty()
{
    int values_a[] = {1, 2};
    MutableListSequence<int> a(values_a, 2);
    MutableListSequence<int> b; // Используем базовый класс для теста
    auto concat1 = a.Concat(&b);
    if (concat1->GetLength() != 2)
    {
        RED("TestConcatWithEmpty failed: Concat a + empty length expected 2, got ", concat1->GetLength());
        return;
    }
    GREEN("TestConcatWithEmpty passed");
}