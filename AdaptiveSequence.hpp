#ifndef ADAPTIVESEQUENCE_HPP
#define ADAPTIVESEQUENCE_HPP

#include "Sequence.hpp"

template <typename T>
class AdaptiveSequence : public Sequence<T>
{
private:
    mutable Sequence<T>* currentImplementation;
    mutable size_t arrayAccessCount;
    mutable size_t listModificationCount;
    size_t ratio;

    void SwitchImplementation() const
    {
        if (arrayAccessCount > ratio * listModificationCount && dynamic_cast<MutableListSequence<T>*>(currentImplementation))
        {
            // Переключаемся на ArraySequence при преимуществе доступа по индексу
            Sequence<T>* old = currentImplementation;
            currentImplementation = new MutableArraySequence<T>(old);
            delete old;
        }
        else if (listModificationCount > ratio * arrayAccessCount && dynamic_cast<MutableArraySequence<T>*>(currentImplementation))
        {
            // Переключаемся на ListSequence при преимуществе модификаций
            Sequence<T>* old = currentImplementation;
            currentImplementation = new MutableListSequence<T>(currentImplementation);
            delete old;
        }
    }

public:
    AdaptiveSequence(size_t ratio = 3) : currentImplementation(new MutableArraySequence<T>()), arrayAccessCount(0), listModificationCount(0), ratio(ratio) {}

    AdaptiveSequence(const T* items, size_t count, size_t ratio = 3) : currentImplementation(new MutableArraySequence<T>(items, count)), arrayAccessCount(0), listModificationCount(0), ratio(ratio) {}

    AdaptiveSequence(const Sequence<T>* other, size_t ratio = 3) : currentImplementation(new MutableArraySequence<T>(other)), arrayAccessCount(0), listModificationCount(0), ratio(ratio) {}

    T GetFirst() const override { return currentImplementation->GetFirst(); }

    T GetLast() const override { return currentImplementation->GetLast(); }

    T Get(size_t index) const override
    {
        arrayAccessCount++;
        SwitchImplementation();
        return this->currentImplementation->Get(index);
    }

    size_t GetLength() const override { return currentImplementation->GetLength(); }

    Sequence<T>* GetSubsequence(size_t start, size_t end) override
    {
        return currentImplementation->GetSubsequence(start, end); 
    }

    Sequence<T>* Append(const T& item) override
    {
        listModificationCount++;
        SwitchImplementation();
        return currentImplementation->Append(item);
    }

    Sequence<T>* Prepend(const T& item) override
    {
        listModificationCount++;
        SwitchImplementation();
        return currentImplementation->Prepend(item);
    }

    Sequence<T>* InsertAt(const T& item, size_t index) override
    {
        listModificationCount++;
        SwitchImplementation();
        return currentImplementation->InsertAt(item, index);
    }

    Sequence<T>* Concat(Sequence<T>* list) override
    {
        return currentImplementation->Concat(list);
    }

    std::string ToString() const override { return currentImplementation->ToString(); }

    ~AdaptiveSequence()
    {
        delete currentImplementation;
    }
};

#endif