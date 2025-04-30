#ifndef SEQUENCETESTS_HPP
#define SEQUENCETESTS_HPP

#include "../Sequence.hpp"
#include "TestsUtils.hpp"

void RunSequenceTests();
void TestImmutableArrayAppend();
void TestImmutableArrayPrepend();
void TestImmutableListAppend();
void TestImmutableListPrepend();
void TestMutableArrayAppend();
void TestMutableArrayPrepend();
void TestMutableListAppend();
void TestMutableListPrepend();
void TestConcatWithEmpty();

template<typename T>
void TestMutableSequenceAppend(Sequence<T>& seq, int expectedLengthAfter, const T& value)
{
    auto newSeq = seq.Append(value);
    if (newSeq != &seq)
    {
        RED("TestMutableSequenceAppend failed: Expected to return the same instance");
        return;
    }
    if (seq.GetLength() != expectedLengthAfter)
    {
        RED("TestMutableSequenceAppend failed: Expected length ", expectedLengthAfter, ", got ", seq.GetLength());
        return;
    }
    if (seq.Get(seq.GetLength() - 1) != value)
    {
        RED("TestMutableSequenceAppend failed: Last element mismatch. Expected ", value, ", got ", seq.Get(seq.GetLength() - 1));
        return;
    }
    GREEN("TestMutableSequenceAppend passed");
}

#endif