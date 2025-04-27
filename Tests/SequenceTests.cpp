#include "../Sequence.hpp"
#include <iostream>
#include <stdexcept>
#include "SequenceTests.hpp"

using namespace std;

#define GREEN(s) std::cout << "\033[32m" << s << "\033[0m" << std::endl;
#define RED(s, p) std::cout << "\033[31m" << s << p << "\033[0m" << std::endl;

void RunSequenceTests()
{
    cout << "Testing Sequence" << endl;
    TestAddVectors();
    TestScalarMultiply();
    TestArraySequenceNorm();

    TestImmutableAppend();
    TestImmutablePrepend();

    TestGetSubsequenceEdgeCases();

    TestConcatWithEmpty();

    TestInsertAtOutOfRange();
    TestGetOutOfRange();
    TestConcatSizeMismatchAdd();
}

// Тесты для sequence

// Тесты для векторных операций
void TestAddVectors()
{
    int values_a[] = {1, 2, 3};
    int values_b[] = {4, 5, 6};
    ArraySequence<int> a(values_a, 3);
    ArraySequence<int> b(values_b, 3);
    auto result = a.Add(&b);
    if (result->Get(0) != 5)
    {
        RED("TestAddVectors failed: Index 0 expected 5, got ", result->Get(0))
        return;
    }
    if (result->Get(1) != 7)
    {
        RED("TestAddVectors failed: Index 1 expected 7, got ", result->Get(1))
        return;
    }
    if (result->Get(2) != 9)
    {
        RED("TestAddVectors failed: Index 2 expected 9, got ", result->Get(2))
        return;
    }
    GREEN("TestAddVectors passed")
}

void TestScalarMultiply()
{
    int values_a[] = {1, 2, 3};
    ArraySequence<int> a(values_a, 3);
    auto result = a.MultiplyByScalar(2);
    if (result->Get(0) != 2)
    {
        RED("TestScalarMultiply failed: Index 0 expected 2, got ", result->Get(0))
        return;
    }
    if (result->Get(1) != 4)
    {
        RED("TestScalarMultiply failed: Index 1 expected 4, got ", result->Get(1))
        return;
    }
    if (result->Get(2) != 6)
    {
        RED("TestScalarMultiply failed: Index 2 expected 6, got ", result->Get(2))
        return;
    }
    GREEN("TestScalarMultiply passed")
}

void TestArraySequenceNorm()
{
    double values_a[] = {3.0, 4.0};
    ArraySequence<double> a(values_a, 2);
    double norm = a.Norm();
    if (fabs(norm - 5.0) > 1e-6)
    {
        RED("TestArraySequenceNorm failed: expected norm 5.0, got ", norm)
        return;
    }
    GREEN("TestArraySequenceNorm passed")
}

// Тесты для ImmutableArraySequence
void TestImmutableAppend()
{
    int values_a[] = {1, 2};
    ImmutableArraySequence<int> a(values_a, 2);
    auto newA = a.Append(3);
    if (newA->GetLength() != 3)
    {
        RED("TestImmutableAppend failed: Expected length 3, got ", newA->GetLength())
        return;
    }
    if (newA->Get(2) != 3)
    {
        RED("TestImmutableAppend failed: Index 2 value mismatch. Expected 3, got ", newA->Get(2))
        return;
    }
    if (a.GetLength() != 2)
    {
        RED("TestImmutableAppend failed: Expected (original sequence) length 2, got ", a.GetLength())
        return;
    }
    GREEN("TestImmutableAppend passed")
}

void TestImmutablePrepend()
{
    int values_a[] = {2, 3};
    ImmutableArraySequence<int> a(values_a, 2);
    auto newA = a.Prepend(1);
    if (newA->GetLength() != 3)
    {
        RED("TestImmutablePrepend failed: Expected length 3, got ", newA->GetLength())
        return;
    }
    if (newA->Get(0) != 1)
    {
        RED("TestImmutablePrepend failed: Index 0 value mismatch. Expected 1, got ", newA->Get(0))
        return;
    }
    if (newA->Get(1) != 2)
    {
        RED("TestImmutablePrepend failed: Index 1 value mismatch. Expected 2, got ", newA->Get(1))
        return;
    }
    if (a.GetLength() != 2)
    {
        RED("TestImmutablePrepend failed: Expected (original sequence) length 2, got ", a.GetLength())
        return;
    }
    GREEN("TestImmutablePrepend passed")
}

// Тесты для GetSubsequence
void TestGetSubsequenceEdgeCases()
{
    int values_a[] = {0, 1, 2, 3, 4};
    ArraySequence<int> a(values_a, 5);
    auto sub1 = a.GetSubsequence(0, 4);
    if (sub1->GetLength() != 5)
    {
        RED("TestGetSubsequenceEdgeCases failed: Expected (sub1) length 5, got ", sub1->GetLength())
        return;
    }

    auto sub2 = a.GetSubsequence(2, 2);
    if (sub2->GetLength() != 1)
    {
        RED("TestGetSubsequenceEdgeCases failed: Expected (sub2) length 1, got ", sub2->GetLength())
        return;
    }
    if (sub2->Get(0) != 2)
    {
        RED("TestGetSubsequenceEdgeCases failed: Index 0 value mismatch. Expected 2, got ", sub2->Get(0))
        return;
    }

    try
    {
        a.GetSubsequence(5, 5);
        RED("TestGetSubsequenceEdgeCases failed: Exception not thrown", "")
        return;
    }
    catch (const std::out_of_range&) {}
    catch (...)
    {
        RED("TestGetSubsequenceEdgeCases failed: Wrong type of exception", "")
        return;
    }

    GREEN("TestGetSubsequenceEdgeCases passed")
}

// Тесты для Concat
void TestConcatWithEmpty()
{
    int values_a[] = {1, 2};
    ListSequence<int> a(values_a, 2);
    ListSequence<int> b;
    auto concat1 = a.Concat(&b);
    if (concat1->GetLength() != 2)
    {
        RED("TestConcatWithEmpty failed: Concat a + empty length expected 2, got ", concat1->GetLength())
        return;
    }
    if (concat1->Get(0) != 1)
    {
        RED("TestConcatWithEmpty failed: concat1 index 0 expected 1, got ", concat1->Get(0))
        return;
    }
    if (concat1->Get(1) != 2)
    {
        RED("TestConcatWithEmpty failed: concat1 index 1 expected 2, got ", concat1->Get(1))
        return;
    }

    auto concat2 = b.Concat(&a);
    if (concat2->GetLength() != 2)
    {
        RED("TestConcatWithEmpty failed: Concat empty + a length expected 2, got ", concat2->GetLength())
        return;
    }
    if (concat2->Get(0) != 1)
    {
        RED("TestConcatWithEmpty failed: concat2 index 0 expected 1, got ", concat2->Get(0))
        return;
    }
    if (concat2->Get(1) != 2)
    {
        RED("TestConcatWithEmpty failed: concat2 index 1 expected 2, got ", concat2->Get(1))
        return;
    }
    GREEN("TestConcatWithEmpty passed")
}

// Тесты для исключений
void TestInsertAtOutOfRange()
{
    int values_a[] = {1};
    ArraySequence<int> a(values_a, 1);
    try
    {
        a.InsertAt(5, -1);
        RED("TestInsertAtOutOfRange failed: Negative index did not throw", "")
        return;
    }
    catch (const std::out_of_range&) {}
    catch (...)
    {
        RED("TestInsertAtOutOfRange failed: Wrong exception type on negative index", "")
        return;
    }

    try
    {
        a.InsertAt(5, 2);
        RED("TestInsertAtOutOfRange failed: Index 2 did not throw", "")
        return;
    }
    catch (const std::out_of_range&) {}
    catch (...)
    {
        RED("TestInsertAtOutOfRange failed: Wrong exception type on index 2", "")
        return;
    }

    GREEN("TestInsertAtOutOfRange passed")
}

void TestGetOutOfRange()
{
    int values_a[] = {10, 20};
    ListSequence<int> a(values_a, 2);
    try
    {
        a.Get(-1);
        RED("TestGetOutOfRange (-1) failed: Exception not thrown", "")
        return;
    }
    catch (const std::out_of_range&) {}
    catch (...)
    {
        RED("TestGetOutOfRange (-1) failed: Wrong type of exception", "")
    }

    try
    {
        a.Get(2);
        RED("TestGetOutOfRange (2) failed: Exception not thrown", "")
        return;
    }
    catch (const std::out_of_range&) {}
    catch (...)
    {
        RED("TestGetOutOfRange (2) failed: Wrong type of exception", "")
    }

    GREEN("TestGetOutOfRange passed")
}

void TestConcatSizeMismatchAdd()
{
    int values_a[] = {1, 2};
    int values_b[] = {3};
    ArraySequence<int> a(values_a, 2);
    ArraySequence<int> b(values_b, 1);
    try
    {
        a.Add(&b);
        RED("TestConcatSizeMismatchAdd failed: Exception not thrown", "")
    }
    catch (const std::invalid_argument&)
    {
        GREEN("TestConcatSizeMismatchAdd passed")
    }
    catch (...)
    {
        RED("TestConcatSizeMismatchAdd failed: Wrong type of exception", "")
    }
}