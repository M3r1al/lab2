#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include "DynamicArray.hpp"
#include "LinkedList.hpp"

template <typename T>
class Sequence
{
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(size_t index) const = 0;
    virtual size_t GetLength() const = 0;
    virtual std::string ToString() const = 0;
    virtual Sequence<T>* GetSubsequence(size_t start, size_t end) const = 0;
    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, size_t index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) const = 0;
    virtual ~Sequence() {}
};

// ArraySequence Class
template <typename T>
class ArraySequence : public Sequence<T>
{
private:
    DynamicArray<T> data;
    size_t size;
    size_t capacity;

protected:
    virtual ArraySequence<T>* Self() const = 0;

public:
    ArraySequence() : data(0), size(0), capacity(0) {}
    ArraySequence(int cap) : data(0), size(0), capacity(cap) {}

    ArraySequence(const T* items, size_t count) : data(items, count), size(count), capacity(count) {}

    ArraySequence(const DynamicArray<T>& arr) : data(arr), size(arr.GetSize()), capacity(arr.GetSize()) {}

    ArraySequence(const LinkedList<T>& list) : data(list.GetLength()), size(list.GetLength()), capacity(list.GetLength())
    {
        for (size_t i = 0; i < list.GetLength(); i++)
            data.Set(i, list.Get(i));
    }
    
    ArraySequence(const ArraySequence<T>& other) : data(other.GetLength()), size(other.GetLength()), capacity(other.GetLength())
    {
        for (size_t i = 0; i < data.GetSize(); i++)
            data.Set(i, other.Get(i));
    }

    ArraySequence(const Sequence<T>* other) : data(other->GetLength()), size(other->GetLength()), capacity(other->GetLength())
    {
        for (size_t i = 0; i < other->GetLength(); i++)
            data.Set(i, other->Get(i));
    }

    T GetFirst() const override
    {
        return data.Get(0);
    }

    T GetLast() const override
    {
        return data.Get(data.GetSize() - 1);
    }

    T Get(size_t index) const override
    {
        return data.Get(index);
    }

    size_t GetLength() const override
    {
        return size;
    }

    Sequence<T>* GetSubsequence(size_t start, size_t end) const override
    {
        if (start > end || end >= GetLength())
            throw std::out_of_range("Invalid range");
        auto* sub = Self();
        
        size_t newSize = end - start + 1;
        sub->data.Resize(newSize);
        for (size_t i = 0; i < newSize; i++)
            sub->data.Set(i, sub->data.Get(start + i));
        return sub;
    }

    Sequence<T>* Append(const T& item) override
    {
        auto self = Self();
        if (self->size >= self->capacity)
        {
            // Увеличить вместимость (экспоненциальный рост)
            capacity = (capacity == 0) ? 1 : capacity * 2;
            self->data.Resize(capacity);
        }
        self->data.Set(self->size, item);
        self->size++;
        return self;
    }

    Sequence<T>* Prepend(const T& item) override
    {
        auto self = Self();
        if (self->size >= self->capacity)
        {
            size_t newCapacity = (self->capacity == 0) ? 1 : self->capacity * 2;
            self->data.Resize(newCapacity);
            self->capacity = newCapacity;
        }
        for (size_t i = self->size; i > 0; i--)
            self->data.Set(i, self->data.Get(i - 1));

        self->data.Set(0, item);
        self->size++;
        return self;
    }

    Sequence<T>* InsertAt(const T& item, size_t index) override
    {
        auto self = Self();
        if (index > size)
            throw std::out_of_range("Index out of range");
        self->data.Resize(self->data.GetSize() + 1);
        for (size_t i = self->data.GetSize() - 1; i > index; i--)
            self->data.Set(i, self->data.Get(i - 1));
        self->data.Set(index, item);
        return self;
    }

    Sequence<T>* Concat(Sequence<T>* list) const override
    {
        size_t total = GetLength() + list->GetLength();
        auto* result = Self(); // Create derived type
        result->data.Resize(total);
        for (size_t i = 0; i < GetLength(); i++)
            result->data.Set(i, Get(i));
        for (size_t i = 0; i < list->GetLength(); i++)
            result->data.Set(GetLength() + i, list->Get(i));
        return result;
    }

    Sequence<T>* Add(const Sequence<T>* other) const
    {
        if (GetLength() != other->GetLength())
            throw std::invalid_argument("Size mismatch in addition");
        DynamicArray<T> otherData(GetLength());
        for (size_t i = 0; i < GetLength(); i++)
            otherData.Set(i, other->Get(i));
        DynamicArray<T> result = data + otherData;

        auto* newSeq = Self();
        newSeq->data = result;
        return newSeq;
    }

    Sequence<T>* MultiplyByScalar(T scalar) const
    {
        DynamicArray<T> result = data * scalar;
        auto* newSeq = Self();
        newSeq->data = result;
        return newSeq;
    }

    T Dot(const Sequence<T>* other) const
    {
        if (GetLength() != other->GetLength())
            throw std::invalid_argument("Size mismatch in dot product");
        DynamicArray<T> otherData(GetLength());
        for (size_t i = 0; i < GetLength(); i++)
            otherData.Set(i, other->Get(i));
        return data.Dot(otherData);
    }

    double Norm() const
    {
        return data.Norm();
    }

    // Оператор [] для записи (non-const версия)
    T& operator[](size_t index)
    {
        return data[index];
    }

    // Оператор [] для чтения (const версия)
    const T& operator[](size_t index) const
    {
        return data[index];
    }

    std::string ToString() const override
    {
        if (size == 0)
            return "[]";
        
        std::string s = "[";
        for (int i = 0; i < size - 1; i++)
            s += std::to_string(Get(i)) + ", ";
        s += std::to_string(Get(size - 1)) + "]";
        return s;
    }
};

// ListSequence Class
template <typename T>
class ListSequence : public Sequence<T>
{
private:
    LinkedList<T> list;

protected:
    virtual ListSequence<T>* Self() const = 0;

public:
    ListSequence() {}

    ListSequence(const T* items, size_t count) : list(items, count) {}

    ListSequence(const LinkedList<T>& linked) : list(linked) {}

    ListSequence(const ListSequence<T>& linked) : list(*linked.list.GetSubList(0, linked.GetLength() - 1)) {}

    ListSequence(const Sequence<T>* other) : list()
    {
        for (size_t i = 0; i < other->GetLength(); i++)
            list.Append(other->Get(i));
    }

    T GetFirst() const override
    {
        return list.GetFirst();
    }

    T GetLast() const override
    {
        return list.GetLast();
    }

    T Get(size_t index) const override
    {
        return list.Get(index);
    }

    size_t GetLength() const override
    {
        return list.GetLength();
    }

    Sequence<T>* GetSubsequence(size_t start, size_t end) const override
    {
        if (start > end || end >= GetLength())
            throw std::out_of_range("Invalid range");
        auto* sub = Self();
        sub->list = *list.GetSubList(start, end);
        return sub;
    }

    Sequence<T>* Append(const T& item) override
    {
        auto self = Self();
        self->list.Append(item);
        return self;
    }

    Sequence<T>* Prepend(const T& item) override
    {
        auto self = Self();
        self->list.Prepend(item);
        return self;
    }

    Sequence<T>* InsertAt(const T& item, size_t index) override
    {
        auto self = Self();
        self->list.InsertAt(item, index);
        return self;
    }

    Sequence<T>* Concat(Sequence<T>* other) const override
    {
        auto* newList = list.Concat(&(dynamic_cast<ListSequence<T>*>(other)->list));
        auto* result = Self();
        result->list = *newList;
        return result;
    }

    // Оператор [] для записи (non-const версия)
    T& operator[](size_t index)
    {
        return list[index];
    }

    // Оператор [] для чтения (const версия)
    const T& operator[](size_t index) const
    {
        return list[index];
    }

    std::string ToString() const override
    {
        return list.ToString();
    }
};

// Mutable and Immutable ArraySequence
template <typename T>
class MutableArraySequence : public ArraySequence<T>
{
protected:
    ArraySequence<T>* Self() const override
    {
        return const_cast<MutableArraySequence<T>*>(this);
    }
public:
    MutableArraySequence() : ArraySequence<T>() {}

    MutableArraySequence(const T* items, size_t count) : ArraySequence<T>(items, count) {}

    MutableArraySequence(const DynamicArray<T>& arr) : ArraySequence<T>(arr) {}

    MutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
    
    MutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}

    MutableArraySequence(const Sequence<T>* other) : ArraySequence<T>(other) {}
};

template <typename T>
class ImmutableArraySequence : public ArraySequence<T>
{
protected:
    ArraySequence<T>* Self() const override
    {
        return new ImmutableArraySequence<T>(*this);
    }
public:
    ImmutableArraySequence() : ArraySequence<T>() {}

    ImmutableArraySequence(const T* items, size_t count) : ArraySequence<T>(items, count) {}

    ImmutableArraySequence(const DynamicArray<T>& arr) : ArraySequence<T>(arr) {}

    ImmutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
    
    ImmutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}

    ImmutableArraySequence(const Sequence<T>* other) : ArraySequence<T>(other) {}
};

// Mutable and Immutable ListSequence
template <typename T>
class MutableListSequence : public ListSequence<T>
{
protected:
    ListSequence<T>* Self() const override
    {
        return const_cast<MutableListSequence<T>*>(this);
    }
public:
    // ImmutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
    MutableListSequence() : ListSequence<T>() {}

    MutableListSequence(const T* items, size_t count) : ListSequence<T>(items, count) {}

    MutableListSequence(const LinkedList<T>& linked) : ListSequence<T>(linked) {}

    MutableListSequence(const ListSequence<T>& linked) : ListSequence<T>(linked) {}

    MutableListSequence(const Sequence<T>* other) : ListSequence<T>(other) {}
};

template <typename T>
class ImmutableListSequence : public ListSequence<T>
{
protected:
    ListSequence<T>* Self() const override
    {
        return new ImmutableListSequence<T>(*this);
    }
public:
    ImmutableListSequence() : ListSequence<T>() {}

    ImmutableListSequence(const T* items, size_t count) : ListSequence<T>(items, count) {}

    ImmutableListSequence(const LinkedList<T>& linked) : ListSequence<T>(linked) {}

    ImmutableListSequence(const ListSequence<T>& linked) : ListSequence<T>(linked) {}

    ImmutableListSequence(const Sequence<T>* other) : ListSequence<T>(other) {}
};

#endif