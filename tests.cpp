
#include "Sequence.hpp"
#include <iostream>
#include <stdexcept>
#include "Tests.hpp"

using namespace std;

#define GREEN(s) std::cout << "\033[32m" << s << "\033[0m" << std::endl;
#define RED(s, p) std::cout << "\033[31m" << s << p << "\033[0m" << std::endl;

void RunAllTests()
{
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

    TestConstructorEmpty();
    TestConstructorWithItems();
    TestCopyConstructorLinkedList();
    TestAppend();
    TestPrepend();
    TestInsertAt();
    TestInsertAtOutOfRangeThrows();
    TestGetFirstAndLast();
    TestGetOutOfRangeThrowsLinkedList();
    TestGetSubList();
    TestGetSubListInvalidThrows();
    TestConcat();

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

// Tests for dymanic array
void TestConstructorValidSize()
{
    DynamicArray<int> arr(10);
    if (arr.GetSize() != 10)
        RED("TestConstructorValidSize failed: Expected size 10, got ", arr.GetSize())
    else
        GREEN("TestConstructorValidSize passed")
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
    GREEN("TestCopyConstructorDynamicArray passed")
}

void TestInitializerConstructor()
{
    int values[] = {1, 2, 3, 4};
    DynamicArray<int> arr(values, 4);
    for (size_t i = 0; i < 4; ++i)
    {
        if (arr.Get(i) != values[i])
        {
            RED("TestInitializerConstructor failed: Error at index ", i)
            return;
        }
    }
    GREEN("TestInitializerConstructor passed")
}

void TestGetAndSet()
{
    DynamicArray<int> arr(3);
    arr.Set(0, 10);
    arr.Set(1, 20);
    arr.Set(2, 30);
    if (arr.Get(0) != 10)
    {
        RED("TestGetAndSet failed: Index 0 value mismatch", "")
        return;
    }
    if (arr.Get(1) != 20)
    {
        RED("TestGetAndSet failed: Index 1 value mismatch", "")
        return;
    }
    if (arr.Get(2) != 30)
    {
        RED("TestGetAndSet failed: Index 2 value mismatch", "")
        return;
    }
    GREEN("TestGetAndSet passed")
}

void TestGetOutOfRangeThrowsDynamicArray()
{
    DynamicArray<int> arr(3);
    try
    {
        arr.Get(5);
        RED("TestGetOutOfRangeThrowsDynamicArray failed: Exception not thrown", "")
    }
    catch (const out_of_range&)
    {
        GREEN("TestGetOutOfRangeThrowsDynamicArray passed")
    }
    catch (...)
    {
        RED("TestGetOutOfRangeThrowsDynamicArray failed: Wrong type of expection", "")
    }
}

void TestSetOutOfRangeThrows()
{
    DynamicArray<int> arr(3);
    try
    {
        arr.Set(5, 100);
        RED("TestSetOutOfRangeThrows failed: Excetion not thrown", "")
    }
    catch (const out_of_range&)
    {
        GREEN("TestSetOutOfRangeThrows passed")
    }
    catch (...)
    {
        RED("TestSetOutOfRangeThrows failed: Wrong type of exception", "")
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
        RED("TestResizeLarger failed: Expected size 5, got ", arr.GetSize())
        return;
    }
    if (arr.Get(0) != 10)
    {
        RED("TestResizeLarger failed: Index 0 value mismatch", "")
        return;
    }
    if (arr.Get(1) != 20)
    {
        RED("TestResizeLarger failed: Index 1 value mismatch", "")
        return;
    }
    if (arr.Get(2) != 30)
    {
        RED("TestResizeLarger failed: Index 2 value mismatch", "")
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
        RED("TestResizeSmaller failed: Expected size 3, got ", arr.GetSize())
        return;
    }
    for (size_t i = 0; i < 3; ++i)
    {
        if (arr.Get(i) != i * 10)
        {
            RED("TestResizeSmaller failed: Error at index ", i)
            return;
        }
    }
    GREEN("TestResizeSmaller passed")
}

void TestResizeZeroThrows()
{
    DynamicArray<int> arr(5);
    try
    {
        arr.Resize(0);
        RED("TestResizeZeroThrows failed: Exception not thrown", "")
    }
    catch (const invalid_argument&)
    {
        GREEN("TestResizeZeroThrows passed")
    }
    catch (...)
    {
        RED("TestResizeZeroThrows failed: Wrong type of exception", "")
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
        RED("TestOperatorAddition failed: Index 0 value mismatch", "")
        return;
    }
    if (result.Get(1) != 6)
    {
        RED("TestOperatorAddition failed: Index 1 value mismatch", "")
        return;
    }
    if (result.Get(2) != 9)
    {
        RED("TestOperatorAddition failed: Index 0 value mismatch", "")
        return;
    }
    GREEN("TestOperatorAddition passed")
}

void TestOperatorAdditionSizeMismatchThrows()
{
    DynamicArray<int> arr1(3);
    DynamicArray<int> arr2(4);
    try
    {
        arr1 + arr2;
        RED("TestOperatorAdditionSizeMismatchThrows failed: Exception not thrown", "")
    }
    catch (const invalid_argument&)
    {
        GREEN("TestOperatorAdditionSizeMismatchThrows passed")
    }
    catch (...)
    {
        RED("TestOperatorAdditionSizeMismatchThrows failed: Wrong type of exception", "")
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
        RED("TestOperatorScalarMultiplication failed: Index 0 value mismatch", "")
        return;
    }
    if (result.Get(1) != 4)
    {
        RED("TestOperatorScalarMultiplication failed: Index 1 value mismatch", "")
        return;
    }
    if (result.Get(2) != 6)
    {
        RED("TestOperatorScalarMultiplication failed: Index 2 value mismatch", "")
        return;
    }
    GREEN("TestOperatorScalarMultiplication")
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
        RED("TestDotProduct failed: Expected 28, got ", arr1.Dot(arr2))
        return;
    }
    GREEN("TestDotProduct passed")
}

void TestDotProductSizeMismatchThrows()
{
    DynamicArray<int> arr1(3);
    DynamicArray<int> arr2(4);
    try
    {
        arr1.Dot(arr2);
        RED("TestDotProductSizeMismatchThrows failed: Exception not thrown", "")
    }
    catch (const invalid_argument&)
    {
        GREEN("TestDotProductSizeMismatchThrows passed")
    }
    catch (...)
    {
        RED("TestDotProductSizeMismatchThrows failed: Wrong type of exception", "")
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
        RED("TestNorm failed: Expected 13, got ", arr.Norm())
        return;
    }
    GREEN("TestNorm passed")
}

// Tests for linked list
void TestConstructorEmpty()
{
    LinkedList<int> list;
    if (list.GetLength() != 0)
        RED("TestConstructorEmpty failed: Expected length 0, got ", list.GetLength())
    else
        GREEN("TestConstructorEmpty passed")
}

void TestConstructorWithItems()
{
    int values[] = {1, 2, 3, 4};
    LinkedList<int> list(values, 4);
    if (list.GetLength() != 4)
    {
        RED("TestConstructorWithItems failed: Expected length 4, got ", list.GetLength())
        return;
    }
    for (size_t i = 0; i < 4; i++)
    {
        if (list.Get(i) != values[i])
        {
            RED("TestConstructorWithItems failed: Error at index ", i)
            return;
        }
    }
    GREEN("TestConstructorWithItems passed")
}

void TestCopyConstructorLinkedList()
{
    LinkedList<int> list1;
    list1.Append(10);
    list1.Append(20);
    LinkedList<int> list2 = list1;
    if (list2.GetLength() != 2)
    {
        RED("TestCopyConstructorLinkedList failed: Expected length 2, got ", list2.GetLength())
        return;
    }
    if (list2.Get(0) != 10)
    {
        RED("TestCopyConstructorLinkedList failed: Index 0 value mismatch", "")
        return;
    }
    if (list2.Get(1) != 20)
    {
        RED("TestCopyConstructorLinkedList failed: Index 0 value mismatch", "")
        return;
    }
    GREEN("TestCopyConstructorLinkedList passed")
}

void TestAppend()
{
    LinkedList<int> list;
    list.Append(5);
    list.Append(10);
    if (list.GetLength() != 2)
    {
        RED("TestAppend failed: Expected length 2, got ", list.GetLength())
        return;
    }
    if (list.Get(0) != 5)
    {
        RED("TestAppend failed: Index 0 value mismatch", "")
        return;
    }
    if (list.Get(1) != 10)
    {
        RED("TestAppend failed: Index 0 value mismatch", "")
        return;
    }
    GREEN("TestAppend passed")
}

void TestPrepend()
{
    LinkedList<int> list;
    list.Prepend(20);
    list.Prepend(10);
    if (list.GetLength() != 2)
    {
        RED("TestPrepend failed: Expected length 2, got ", list.GetLength())
        return;
    }
    if (list.Get(0) != 10)
    {
        RED("TestPrepend failed: Index 0 value mismatch. Expected 10, got ", list.Get(0))
        return;
    }
    if (list.Get(1) != 20)
    {
        RED("TestPrepend failed: Index 1 value mismatch. Expected 20, got ", list.Get(1))
        return;
    }
    GREEN("TestPrepend passed")
}

void TestInsertAt()
{
    LinkedList<int> list;
    list.Append(10);
    list.Append(30);
    list.InsertAt(20, 1);
    if (list.GetLength() != 3)
    {
        RED("TestInsertAt failed: Expected length 3, got ", list.GetLength())
        return;
    }
    if (list.Get(0) != 10)
    {
        RED("TestInsertAt failed: Index 0 value mismatch. Expected 10, got ", list.Get(0))
        return;
    }
    if (list.Get(1) != 20)
    {
        RED("TestInsertAt failed: Index 1 value mismatch. Expected 20, got ", list.Get(1))
        return;
    }
    if (list.Get(2) != 30)
    {
        RED("TestInsertAt failed: Index 2 value mismatch. Expected 30, got ", list.Get(2))
        return;
    }
    GREEN("TestInsertAt passed")
}

void TestInsertAtOutOfRangeThrows()
{
    LinkedList<int> list;
    try
    {
        list.InsertAt(10, 5);
        RED("TestInsertAtOutOfRangeThrows failed: Exception not thrown", "")
    }
    catch (const out_of_range&)
    {
        GREEN("TestInsertAtOutOfRangeThrows passed")
    }
    catch (...)
    {
        RED("TestInsertAtOutOfRangeThrows failed: Wrong type of exception", "")
    }
}

void TestGetFirstAndLast()
{
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    list.Append(30);
    if (list.GetFirst() != 10)
    {
        RED("TestGetFirstAndLast failed: First value mismatch. Expected 10, got ", list.GetFirst())
        return;
    }
    if (list.GetLast() != 30)
    {
        RED("TestGetFirstAndLast failed: Last value mismatch. Expected 20, got ", list.GetLast())
        return;
    }
    GREEN("TestGetFirstAndLast passed")
}

void TestGetOutOfRangeThrowsLinkedList()
{
    LinkedList<int> list;
    list.Append(10);
    try
    {
        list.Get(2);
        RED("TestGetOutOfRangeThrowsLinkedList failed: Exception not thrown", "")
    }
    catch (const out_of_range&)
    {
        GREEN("TestGetOutOfRangeThrowsLinkedList passed")
    }
    catch (...)
    {
        RED("TestGetOutOfRangeThrowsLinkedList failed: Wrong type of exception", "")
    }
}

void TestGetSubList()
{
    int values[] = {10, 20, 30, 40, 50};
    LinkedList<int> list(values, 5);
    LinkedList<int>* sublist = list.GetSubList(1, 3);
    if (sublist->GetLength() != 3)
    {
        RED("TestGetSubList failed: Expected length 3, got ", sublist->GetLength())
        return;
    }
    if (sublist->Get(0) != 20)
    {
        RED("TestGetSubList failed: Index 0 value mismatch. Expected 20, got ", sublist->Get(0))
        return;
    }
    if (sublist->Get(1) != 30)
    {
        RED("TestGetSubList failed: Index 1 value mismatch. Expected 30, got ", sublist->Get(1))
        return;
    }
    if (sublist->Get(2) != 40)
    {
        RED("TestGetSubList failed: Index 2 value mismatch. Expected 40, got ", sublist->Get(2))
        return;
    }
    GREEN("TestGetSubList passed")
}

void TestGetSubListInvalidThrows()
{
    LinkedList<int> list;
    list.Append(10);
    try
    {
        list.GetSubList(1, 3);
        RED("TestGetSubListInvalidThrows failed: Exception not thrown", "")
    }
    catch (const out_of_range&)
    {
        GREEN("TestGetSubListInvalidThrows passed")
    }
    catch (...)
    {
        RED("TestGetSubListInvalidThrows failed: Wrong type of exception", "")
    }
    GREEN("TestGetSubListInvalidThrows passed")
}

void TestConcat()
{
    LinkedList<int> list1;
    LinkedList<int> list2;
    list1.Append(10);
    list1.Append(20);
    list2.Append(30);
    list2.Append(40);
    LinkedList<int>* result = list1.Concat(&list2);
    if (result->GetLength() != 4)
    {
        RED("TestConcat failed: Expected length 4, got ", result->GetLength())
        return;
    }
    if (result->Get(0) != 10)
    {
        RED("TestConcat failed: Index 0 value mismatch. Expected 10, got ", result->Get(0))
        return;
    }
    if (result->Get(1) != 20)
    {
        RED("TestConcat failed: Index 1 value mismatch. Expected 20, got ", result->Get(1))
        return;
    }
    if (result->Get(2) != 30)
    {
        RED("TestConcat failed: Index 2 value mismatch. Expected 30, got ", result->Get(2))
        return;
    }
    if (result->Get(3) != 40)
    {
        RED("TestConcat failed: Index 3 value mismatch. Expected 40, got ", result->Get(3))
        return;
    }
    GREEN("TestConcat passed")
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