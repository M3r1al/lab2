
#include "../Sequence.hpp"
#include <iostream>
#include <stdexcept>
#include "LinkedListTests.hpp"
#include "TestsUtils.hpp"

using namespace std;

void RunLinkedListTests()
{
    cout << "Testing LinkedList" << endl;
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
}

void TestConstructorEmpty()
{
    LinkedList<int> list;
    if (list.GetLength() != 0)
        RED("TestConstructorEmpty failed: Expected length 0, got ", list.GetLength());
    else
        GREEN("TestConstructorEmpty passed");
}

void TestConstructorWithItems()
{
    int values[] = {1, 2, 3, 4};
    LinkedList<int> list(values, 4);
    if (list.GetLength() != 4)
    {
        RED("TestConstructorWithItems failed: Expected length 4, got ", list.GetLength());
        return;
    }
    for (size_t i = 0; i < 4; i++)
    {
        if (list.Get(i) != values[i])
        {
            RED("TestConstructorWithItems failed: Error at index ", i);
            return;
        }
    }
    GREEN("TestConstructorWithItems passed");
}

void TestCopyConstructorLinkedList()
{
    LinkedList<int> list1;
    list1.Append(10);
    list1.Append(20);
    LinkedList<int> list2 = list1;
    if (list2.GetLength() != 2)
    {
        RED("TestCopyConstructorLinkedList failed: Expected length 2, got ", list2.GetLength());
        return;
    }
    if (list2.Get(0) != 10)
    {
        RED("TestCopyConstructorLinkedList failed: Index 0 value mismatch");
        return;
    }
    if (list2.Get(1) != 20)
    {
        RED("TestCopyConstructorLinkedList failed: Index 0 value mismatch");
        return;
    }
    GREEN("TestCopyConstructorLinkedList passed");
}

void TestAppend()
{
    LinkedList<int> list;
    list.Append(5);
    list.Append(10);
    if (list.GetLength() != 2)
    {
        RED("TestAppend failed: Expected length 2, got ", list.GetLength());
        return;
    }
    if (list.Get(0) != 5)
    {
        RED("TestAppend failed: Index 0 value mismatch");
        return;
    }
    if (list.Get(1) != 10)
    {
        RED("TestAppend failed: Index 0 value mismatch");
        return;
    }
    GREEN("TestAppend passed");
}

void TestPrepend()
{
    LinkedList<int> list;
    list.Prepend(20);
    list.Prepend(10);
    if (list.GetLength() != 2)
    {
        RED("TestPrepend failed: Expected length 2, got ", list.GetLength());
        return;
    }
    if (list.Get(0) != 10)
    {
        RED("TestPrepend failed: Index 0 value mismatch. Expected 10, got ", list.Get(0));
        return;
    }
    if (list.Get(1) != 20)
    {
        RED("TestPrepend failed: Index 1 value mismatch. Expected 20, got ", list.Get(1));
        return;
    }
    GREEN("TestPrepend passed");
}

void TestInsertAt()
{
    LinkedList<int> list;
    list.Append(10);
    list.Append(30);
    list.InsertAt(20, 1);
    if (list.GetLength() != 3)
    {
        RED("TestInsertAt failed: Expected length 3, got ", list.GetLength());
        return;
    }
    if (list.Get(0) != 10)
    {
        RED("TestInsertAt failed: Index 0 value mismatch. Expected 10, got ", list.Get(0));
        return;
    }
    if (list.Get(1) != 20)
    {
        RED("TestInsertAt failed: Index 1 value mismatch. Expected 20, got ", list.Get(1));
        return;
    }
    if (list.Get(2) != 30)
    {
        RED("TestInsertAt failed: Index 2 value mismatch. Expected 30, got ", list.Get(2));
        return;
    }
    GREEN("TestInsertAt passed");
}

void TestInsertAtOutOfRangeThrows()
{
    LinkedList<int> list;
    try
    {
        list.InsertAt(10, 5);
        RED("TestInsertAtOutOfRangeThrows failed: Exception not thrown");
    }
    catch (const out_of_range&)
    {
        GREEN("TestInsertAtOutOfRangeThrows passed");
    }
    catch (...)
    {
        RED("TestInsertAtOutOfRangeThrows failed: Wrong type of exception");
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
        RED("TestGetFirstAndLast failed: First value mismatch. Expected 10, got ", list.GetFirst());
        return;
    }
    if (list.GetLast() != 30)
    {
        RED("TestGetFirstAndLast failed: Last value mismatch. Expected 20, got ", list.GetLast());
        return;
    }
    GREEN("TestGetFirstAndLast passed");
}

void TestGetOutOfRangeThrowsLinkedList()
{
    LinkedList<int> list;
    list.Append(10);
    try
    {
        list.Get(2);
        RED("TestGetOutOfRangeThrowsLinkedList failed: Exception not thrown");
    }
    catch (const out_of_range&)
    {
        GREEN("TestGetOutOfRangeThrowsLinkedList passed");
    }
    catch (...)
    {
        RED("TestGetOutOfRangeThrowsLinkedList failed: Wrong type of exception");
    }
}

void TestGetSubList()
{
    int values[] = {10, 20, 30, 40, 50};
    LinkedList<int> list(values, 5);
    LinkedList<int>* sublist = list.GetSubList(1, 3);
    if (sublist->GetLength() != 3)
    {
        RED("TestGetSubList failed: Expected length 3, got ", sublist->GetLength());
        return;
    }
    if (sublist->Get(0) != 20)
    {
        RED("TestGetSubList failed: Index 0 value mismatch. Expected 20, got ", sublist->Get(0));
        return;
    }
    if (sublist->Get(1) != 30)
    {
        RED("TestGetSubList failed: Index 1 value mismatch. Expected 30, got ", sublist->Get(1));
        return;
    }
    if (sublist->Get(2) != 40)
    {
        RED("TestGetSubList failed: Index 2 value mismatch. Expected 40, got ", sublist->Get(2));
        return;
    }
    GREEN("TestGetSubList passed");
    delete sublist;
}

void TestGetSubListInvalidThrows()
{
    LinkedList<int> list;
    list.Append(10);
    try
    {
        list.GetSubList(1, 3);
        RED("TestGetSubListInvalidThrows failed: Exception not thrown");
    }
    catch (const out_of_range&)
    {
        GREEN("TestGetSubListInvalidThrows passed");
    }
    catch (...)
    {
        RED("TestGetSubListInvalidThrows failed: Wrong type of exception");
    }
    GREEN("TestGetSubListInvalidThrows passed");
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
        RED("TestConcat failed: Expected length 4, got ", result->GetLength());
        return;
    }
    if (result->Get(0) != 10)
    {
        RED("TestConcat failed: Index 0 value mismatch. Expected 10, got ", result->Get(0));
        return;
    }
    if (result->Get(1) != 20)
    {
        RED("TestConcat failed: Index 1 value mismatch. Expected 20, got ", result->Get(1));
        return;
    }
    if (result->Get(2) != 30)
    {
        RED("TestConcat failed: Index 2 value mismatch. Expected 30, got ", result->Get(2));
        return;
    }
    if (result->Get(3) != 40)
    {
        RED("TestConcat failed: Index 3 value mismatch. Expected 40, got ", result->Get(3));
        return;
    }
    GREEN("TestConcat passed");
    delete result;
}