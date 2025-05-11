#ifndef SEQUENCETESTS_HPP
#define SEQUENCETESTS_HPP

#include "../Sequence.hpp"
#include "../AdaptiveSequence.hpp"
#include "../SegmentedList.hpp"
#include "TestsUtils.hpp"

void RunSequenceTests();

template <typename T>
ImmutableArraySequence<T>* CreateImmutableArray(const T* values, size_t length)
{
    return new ImmutableArraySequence<T>(values, length);
}

template <typename T>
ImmutableListSequence<T>* CreateImmutableList(const T* values, size_t length)
{
    return new ImmutableListSequence<T>(values, length);
}

template <typename T>
MutableArraySequence<T>* CreateMutableArray(const T* values, size_t length)
{
    return new MutableArraySequence<T>(values, length);
}

template <typename T>
MutableListSequence<T>* CreateMutableList(const T* values, size_t length)
{
    return new MutableListSequence<T>(values, length);
}

template <typename T>
AdaptiveSequence<T>* CreateAdaptiveSequence(const T* values, size_t length)
{
    return new AdaptiveSequence<T>(values, length);
}

template <typename T>
SegmentedList<T>* CreateSegmentedList(const T* values, size_t length, size_t segment_size)
{
    return new SegmentedList<T>(values, length, segment_size);
}

template <typename T>
void TestMutableAppend(Sequence<T>* seq, const T* values, size_t length, const T& newValue, const T* expectedValues, size_t expectedLength, const std::string& functionName)
{
    auto newSeq = seq->Append(newValue);
    
    if (newSeq->GetLength() != expectedLength)
    {
        RED(functionName, " failed: New sequence length mismatch. Expected ", expectedLength, ", got: ", newSeq->GetLength());
        delete newSeq;
        return;
    }

    for (size_t i = 0; i < expectedLength; ++i)
    {
        if (newSeq->Get(i) != expectedValues[i])
        {
            RED(functionName, " failed: Value mismatch at index ", i, ". Expected ", expectedValues[i], ", got: ", newSeq->Get(i));
            delete newSeq;
            return;
        }
    }
    
    GREEN(functionName, " passed");
    delete newSeq;
}

template <typename T>
void TestImmutableAppend(Sequence<T>* seq, const T* values, size_t length, const T& newValue, const T* expectedValues, size_t expectedLength, const std::string& functionName)
{
    auto newSeq = seq->Append(newValue);
    
    if (seq->GetLength() != length)
    {
        RED(functionName, " failed: Original sequence length modified. Was ", expectedLength, ", now: ", newSeq->GetLength());
        delete seq;
        return;
    }
    
    if (newSeq->GetLength() != expectedLength)
    {
        RED(functionName, " failed: New sequence length mismatch. Expected ", expectedLength, ", got: ", newSeq->GetLength());
        delete seq;
        return;
    }
    
    for (size_t i = 0; i < expectedLength; ++i)
    {
        if (newSeq->Get(i) != expectedValues[i])
        {
            RED(functionName, " failed: Value mismatch at index ", i, ". Expected ", expectedValues[i], ", got: ", newSeq->Get(i));
            delete seq;
            return;
        }
    }
    
    GREEN(functionName, " passed");
    delete seq;
}

template <typename T>
void TestMutablePrepend(Sequence<T>* seq, const T* values, size_t length, const T& newValue, const T* expectedValues, size_t expectedLength, const std::string& functionName)
{
    auto newSeq = seq->Prepend(newValue);
    
    if (newSeq->GetLength() != expectedLength)
    {
        RED(functionName, " failed: New sequence length mismatch. Expected ", expectedLength, ", got: ", newSeq->GetLength());
        delete newSeq;
        return;
    }
    
    for (size_t i = 0; i < expectedLength; ++i)
    {
        if (newSeq->Get(i) != expectedValues[i])
        {
            RED(functionName, " failed: Value mismatch at index ", i, ". Expected ", expectedValues[i], ", got: ", newSeq->Get(i));
            delete newSeq;
            return;
        }
    }
    
    GREEN(functionName, " passed");
    delete newSeq;
}

template <typename T>
void TestImmutablePrepend(Sequence<T>* seq, const T* values, size_t length, const T& newValue, const T* expectedValues, size_t expectedLength, const std::string& functionName)
{
    auto newSeq = seq->Prepend(newValue);
    
    if (seq->GetLength() != length)
    {
        RED(functionName, " failed: Original sequence length modified. Was ", expectedLength, ", now: ", newSeq->GetLength());
        delete seq;
        return;
    }
    
    if (newSeq->GetLength() != expectedLength)
    {
        RED(functionName, " failed: New sequence length mismatch. Expected ", expectedLength, ", got: ", newSeq->GetLength());
        delete seq;
        return;
    }
    
    for (size_t i = 0; i < expectedLength; ++i)
    {
        if (newSeq->Get(i) != expectedValues[i])
        {
            RED(functionName, " failed: Value mismatch at index ", i, ". Expected ", expectedValues[i], ", got: ", newSeq->Get(i));
            delete seq;
            return;
        }
    }
    
    GREEN(functionName, " passed");
    delete seq;
}

template <typename T>
void TestGetSubsequence(Sequence<T>* seq, const T* values, size_t length, size_t start, size_t end, const T* expectedValues, size_t expectedLength, const std::string& functionName)
{
    try
    {
        auto sub = seq->GetSubsequence(start, end);
        
        if (sub->GetLength() != expectedLength)
        {
            RED(functionName, " failed: New sequence length mismatch. Expected ", expectedLength, ", got: ", sub->GetLength());
            delete seq;
            return;
        }
        
        for (size_t i = 0; i < expectedLength; ++i)
        {
            if (sub->Get(i) != expectedValues[i])
            {
                RED(functionName, " failed: Value mismatch at index ", i, ". Expected ", expectedValues[i], ", got: ", sub->Get(i));
                delete seq;
                return;
            }
        }
        
        GREEN(functionName, " passed");
        delete seq;
    }
    catch (const std::out_of_range& e)
    {
        delete seq;
        // Должны были получить ошибку
        if (expectedLength == 0)
        {
            GREEN(functionName, " passed");
            return;
        }
        RED(functionName, " failed: Unexpected exception: ", e.what());
    }
}

template <typename T>
void TestMutableConcat(Sequence<T>* seq, Sequence<T>* otherSeq, T* values1, size_t length1, const T* values2, size_t length2, const T* expectedValues, size_t expectedLength, const std::string& functionName)
{
    auto concatSeq = seq->Concat(otherSeq);

    if (concatSeq->GetLength() != expectedLength || seq->GetLength() != expectedLength)
    {
        RED(functionName, " failed: Sequence length mismatch. Expected ", expectedLength, ", got: ", concatSeq->GetLength());
        delete otherSeq;
        delete concatSeq;
        return;
    }

    for (size_t i = 0; i < expectedLength; ++i)
    {
        if (concatSeq->Get(i) != expectedValues[i])
        {
            RED(functionName, " failed: Value mismatch at index ", i, ". Expected ", expectedValues[i], ", got: ", concatSeq->Get(i));
            delete otherSeq;
            delete concatSeq;
            return;
        }
    }

    GREEN(functionName, " passed");
    delete otherSeq;
    delete concatSeq;
}

template <typename T>
void TestImmutableConcat(Sequence<T>* seq, Sequence<T>* otherSeq, const T* values1, size_t length1, const T* values2, size_t length2, const T* expectedValues, size_t expectedLength, const std::string& functionName)
{
    auto concatSeq = seq->Concat(otherSeq);

    if (seq->GetLength() != length1)
    {
        RED(functionName, " failed: Original sequence length modified. Expected ", length1, ", got: ", seq->GetLength());
        delete otherSeq;
        delete concatSeq;
        return;
    }

    if (concatSeq->GetLength() != expectedLength)
    {
        RED(functionName, " failed: New sequence length mismatch. Expected ", expectedLength, ", got: ", concatSeq->GetLength());
        delete otherSeq;
        delete concatSeq;
        return;
    }

    for (size_t i = 0; i < expectedLength; ++i)
    {
        if (concatSeq->Get(i) != expectedValues[i])
        {
            RED(functionName, " failed: Value mismatch at index ", i, ". Expected ", expectedValues[i], ", got: ", concatSeq->Get(i));
            delete otherSeq;
            delete concatSeq;
            return;
        }
    }

    GREEN(functionName, " passed");
    delete otherSeq;
    delete concatSeq;
}

#endif