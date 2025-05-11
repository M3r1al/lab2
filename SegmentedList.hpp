#ifndef SEGMENTEDLIST_HPP
#define SEGMENTEDLIST_HPP

#include "Sequence.hpp"

template <typename T>
class SegmentedList : public Sequence<T>
{
private:
    LinkedList<DynamicArray<T>> segments;
    size_t segmentSize;
    size_t size;

    size_t GetSegmentIndex(size_t index) const
    {
        return index / segmentSize;
    }

    size_t GetPositionInSegment(size_t index) const
    {
        return index % segmentSize;
    }

    DynamicArray<T>& GetSegment(size_t segmentIndex)
    {
        return segments.GetLinked(segmentIndex);
    }

    const DynamicArray<T>& GetSegment(size_t segmentIndex) const
    {
        return segments.GetLinked(segmentIndex);
    }

    void EnsureCapacity(size_t index)
    {
        size_t requiredSegments = GetSegmentIndex(index) + 1;
        while (segments.GetLength() < requiredSegments)
        {
            segments.Append(DynamicArray<T>(segmentSize));
        }
    }

public:
    SegmentedList(size_t segmentSize = 1024) : segmentSize(segmentSize), size(0)
    {
        if (segmentSize == 0)
            throw std::invalid_argument("Segment size must be positive");
    }

    SegmentedList(const T* items, size_t count, size_t segmentSize = 1024) : segmentSize(segmentSize), size(0)
    {
        if (segmentSize == 0)
            throw std::invalid_argument("Segment size must be positive");

        for (size_t i = 0; i < count; i++)
        {
            Append(items[i]);
        }
    }

    SegmentedList(const Sequence<T>* other, size_t segmentSize = 1024) : segmentSize(segmentSize), size(0)
    {
        if (segmentSize == 0)
            throw std::invalid_argument("Segment size must be positive");

        for (size_t i = 0; i < other->GetLength(); i++)
        {
            Append(other->Get(i));
        }
    }

    T GetFirst() const override
    {
        if (segments.GetLength() == 0)
            throw std::out_of_range("List is empty");
        return segments.GetLinked(0).Get(0);
    }

    T GetLast() const override
    {
        if (segments.GetLength() == 0)
            throw std::out_of_range("List is empty");

        size_t lastSegmentIndex = segments.GetLength() - 1;
        DynamicArray<T> lastSegment = segments.GetLinked(lastSegmentIndex);
        return lastSegment.Get(lastSegment.GetSize() - 1);
    }

    T Get(size_t index) const override
    {
        size_t segmentIndex = GetSegmentIndex(index);
        size_t position = GetPositionInSegment(index);
        return GetSegment(segmentIndex).Get(position);
    }

    size_t GetLength() const override
    {
        return size;
    }

    Sequence<T>* GetSubsequence(size_t start, size_t end) override
    {
        auto* result = new SegmentedList<T>(segmentSize);
        for (size_t i = start; i <= end; i++)
        {
            result->Append(Get(i));
        }
        return result;
    }

    Sequence<T>* Append(const T& item) override
    {
        size_t currentLength = GetLength();
        EnsureCapacity(currentLength);
        size_t segmentIndex = GetSegmentIndex(currentLength);
        size_t position = GetPositionInSegment(currentLength);
        GetSegment(segmentIndex).Set(position, item);
        size++;
        return this;
    }

    Sequence<T>* Prepend(const T& item) override
    {
        InsertAt(item, 0);
        return this;
    }

    Sequence<T>* InsertAt(const T& item, size_t index) override
    {
        EnsureCapacity(index);
        
        // Shift elements to the right
        for (size_t i = GetLength(); i > index; i--)
        {
            Set(i, Get(i - 1));
        }
        
        Set(index, item);
        size++;
        return this;
    }

    Sequence<T>* Concat(Sequence<T>* list) override
    {
        // auto* result = new SegmentedList<T>(segmentSize);
        // for (size_t i = 0; i < GetLength(); i++)
        //     result->Append(Get(i));
        
        for (size_t i = 0; i < list->GetLength(); i++)
            this->Append(list->Get(i));
        return this;
    }

    void Set(size_t index, const T& value)
    {
        EnsureCapacity(index);
        size_t segmentIndex = GetSegmentIndex(index);
        size_t position = GetPositionInSegment(index);
        GetSegment(segmentIndex).Set(position, value);
    }

    std::string ToString() const override
    {
        std::string result = "[";
        for (size_t i = 0; i < GetLength(); i++)
        {
            if (i > 0) result += ", ";
            result += std::to_string(Get(i));
        }
        result += "]";
        return result;
    }
};

#endif