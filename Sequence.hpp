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
    virtual ArraySequence<T>* Self()
    {
        return this;
    }

public:
    ArraySequence() : data(0) {}

    ArraySequence(const T* items, size_t count) : data(items, count) {}

    ArraySequence(const DynamicArray<T>& arr) : data(arr) {}

    ArraySequence(const LinkedList<T>& list) : data(list.GetLength())
    {
        for (size_t i = 0; i < list.GetLength(); i++)
            data.Set(i, list.Get(i));
    }
    
    ArraySequence(const ArraySequence<T>& other) : data(other.GetLength())
    {
        for (size_t i = 0; i < data.GetSize(); i++)
            data.Set(i, other.Get(i));
    }

    ArraySequence(const Sequence<T>* other) : data(other->GetLength())
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
        return data.GetSize();
    }

    Sequence<T>* GetSubsequence(size_t start, size_t end) const override
    {
        if (start > end || end >= GetLength())
            throw std::out_of_range("Invalid range");
        T* temp = new T[end - start + 1];
        for (size_t i = 0; i <= end - start; i++)
            temp[i] = data.Get(start + i);
        auto* sub = new ArraySequence<T>(temp, end - start + 1);
        delete[] temp;
        return sub;
    }

    Sequence<T>* Append(const T& item) override
    {
        auto self = Self();
        self->data.Resize(self->data.GetSize() + 1);
        self->data.Set(self->data.GetSize() - 1, item);
        return self;
    }

    Sequence<T>* Prepend(const T& item) override
    {
        auto self = Self();
        size_t size = self->data.GetSize();
        self->data.Resize(size + 1);
        for (size_t i = size; i > 0; i--)
            self->data.Set(i, self->data.Get(i - 1));
        self->data.Set(0, item);
        return self;
    }

    Sequence<T>* InsertAt(const T& item, size_t index) override
    {
        auto self = Self();
        if (index > data.GetSize())
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
        T* combined = new T[total];
        for (size_t i = 0; i < GetLength(); i++)
            combined[i] = Get(i);
        for (size_t i = 0; i < list->GetLength(); i++)
            combined[GetLength() + i] = list->Get(i);
        auto* result = new ArraySequence<T>(combined, total);
        delete[] combined;
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
        return new ArraySequence<T>(result);
    }

    Sequence<T>* MultiplyByScalar(T scalar) const
    {
        DynamicArray<T> result = data * scalar;
        return new ArraySequence<T>(result);
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
        return data.ToString();
    }
};

// ListSequence Class
template <typename T>
class ListSequence : public Sequence<T>
{
private:
    LinkedList<T> list;
    virtual ListSequence<T>* Self()
    {
        return this;
    }

public:
    ListSequence() {}

    ListSequence(const T* items, size_t count) : list(items, count) {}

    ListSequence(const LinkedList<T>& linked) : list(linked) {}

    ListSequence(const ListSequence<T>& linked) : list(*GetSubList(0, linked.GetLength())) {}

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
        return new ListSequence<T>(*list.GetSubList(start, end));
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
        return new ListSequence<T>(*newList);
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
private:
    ArraySequence<T>* Self() override
    {
        return new ArraySequence<T>(*this); // Создаёт копию текущего объекта
    }
};

template <typename T>
class ImmutableArraySequence : public ArraySequence<T>
{
private:
    ArraySequence<T>* Self() override
    {
        return new ImmutableArraySequence<T>(*this);
    }
public:
    // ImmutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
    ImmutableArraySequence(const T* items, size_t count) : ArraySequence<T>(items, count) {}
};

// Mutable and Immutable ListSequence
template <typename T>
class MutableListSequence : public ListSequence<T>
{
public:

    Sequence<T>* Append(const T& item) override
    {
        ListSequence<T>::Append(item);
        return this;
    }

    Sequence<T>* Prepend(const T& item) override
    {
        ListSequence<T>::Prepend(item);
        return this;
    }

    Sequence<T>* InsertAt(const T& item, size_t index) override
    {
        ListSequence<T>::InsertAt(item, index);
        return this;
    }
};

template <typename T>
class ImmutableListSequence : public ListSequence<T>
{
private:
    ListSequence<T>* Self() override
    {
        return new ListSequence<T>(static_cast<const Sequence<T>*>(this));
    }
};

#endif