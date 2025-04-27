#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

#include <cmath>
#include <stdexcept>
#include <new>
#include <string>

template <typename T>
class DynamicArray
{
private:
    T* data;
    size_t size;

public:
    DynamicArray(size_t size) : size(size)
    {
        try
        {
            data = new T[size];
        }
        catch (const std::bad_alloc& e)
        {
            throw std::runtime_error("Memory allocation failed in constructor");
        }
    }

    DynamicArray(const T* items, size_t count) : size(count)
    {
        try
        {
            data = new T[count];
            for (size_t i = 0; i < count; i++)
                data[i] = items[i];
        }
        catch (const std::bad_alloc& e)
        {
            throw std::runtime_error("Memory allocation failed in initializer");
        }
    }

    DynamicArray(const DynamicArray& other) : size(other.size)
    {
        try
        {
            data = new T[size];
            for (size_t i = 0; i < size; i++)
                data[i] = other.data[i];
        }
        catch (const std::bad_alloc& e)
        {
            throw std::runtime_error("Memory allocation failed in copy constructor");
        }
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    T Get(size_t index) const
    {
        if (index >= size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    void Set(size_t index, const T& value)
    {
        if (index >= size)
            throw std::out_of_range("Index out of range");
        data[index] = value;
    }

    size_t GetSize() const
    {
        return size;
    }

    void Resize(size_t newSize)
    {
        if (newSize == 0)
            throw std::invalid_argument("Resize size cannot be zero");
        try
        {
            T* newData = new T[newSize];
            for (size_t i = 0; i < (newSize < size ? newSize : size); i++)
                newData[i] = data[i];
            delete[] data;
            data = newData;
            size = newSize;
        }
        catch (const std::bad_alloc& e)
        {
            throw std::runtime_error("Memory allocation failed in Resize");
        }
    }

    // Vector Addition
    DynamicArray operator+(const DynamicArray& other) const
    {
        if (size != other.size)
            throw std::invalid_argument("Size mismatch in addition");
        DynamicArray result(size);
        for (size_t i = 0; i < size; i++)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    // Scalar Multiplication
    DynamicArray operator*(const T& scalar) const
    {
        DynamicArray result(size);
        for (size_t i = 0; i < size; i++)
            result.data[i] = data[i] * scalar;
        return result;
    }

    // Оператор [] для записи (non-const версия)
    T& operator[](size_t index)
    {
        if (index >= size)
            throw std::out_of_range("Index out of bounds");
        
        return data[index];
    }

    // Оператор [] для чтения (const версия)
    const T& operator[](size_t index) const
    {
        if (index >= size)
            throw std::out_of_range("Index out of bounds");
        
        return data[index];
    }

    DynamicArray<T> ScalarMultiply(int scalar) const
    {
        return (*this) * scalar;
        // DynamicArray<T> new_array(size);
        // for (int i = 0; i < size; i++)
        //     new_array.Set(i, this->Get(i) * scalar);
        // return new_array;
    }

    // Dot Product
    T Dot(const DynamicArray& other) const
    {
        if (size != other.size)
            throw std::invalid_argument("Size mismatch in dot product");
        T result = T();
        for (size_t i = 0; i < size; i++)
            result += data[i] * other.data[i];
        return result;
    }

    // L2 Norm
    double Norm() const
    {
        if (size == 0)
            throw std::invalid_argument("Cannot compute norm of an empty array");
        double sum = 0;
        for (size_t i = 0; i < size; i++)
            sum += static_cast<double>(data[i]) * data[i]; // приводим к double, чтобы не было целочисленного умножения. И повышает точность в случае float
        return std::sqrt(sum);
    }

    std::string ToString() const
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

#endif