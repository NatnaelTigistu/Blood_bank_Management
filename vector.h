#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;

template <typename T>
class MyVector
{
private:
    T *data;
    size_t capacity;
    size_t length;

    void reallocate(size_t new_capacity)
    {
        T *new_data = new T[new_capacity];
        for (size_t i = 0; i < length; ++i)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
        MyVector() : data(nullptr), capacity(0), length(0) {}

    explicit MyVector(size_t n) : data(new T[n]), capacity(n), length(n)
    {
        for (size_t i = 0; i < n; ++i)
            data[i] = T();
    }

    MyVector(size_t n, const T &val) : data(new T[n]), capacity(n), length(n)
    {
        for (size_t i = 0; i < n; ++i)
            data[i] = val;
    }

    MyVector(const MyVector &other) : data(new T[other.capacity]), capacity(other.capacity), length(other.length)
    {
        for (size_t i = 0; i < length; ++i)
            data[i] = other.data[i];
    }

    ~MyVector()
    {
        delete[] data;
    }

    MyVector &operator=(const MyVector &other)
    {
        if (this != &other)
        {
            delete[] data;
            capacity = other.capacity;
            length = other.length;
            data = new T[capacity];
            for (size_t i = 0; i < length; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    T &operator[](size_t index)
    {
        return data[index];
    }

    const T &operator[](size_t index) const
    {
        return data[index];
    }

    T &at(size_t index)
    {
        if (index >= length)
        {
            cerr << "Error: MyVector index out of bounds\n";
            static T dummy;
            return dummy;
        }
        return data[index];
    }

    const T &at(size_t index) const
    {
        if (index >= length)
        {
            cerr << "Error: MyVector index out of bounds\n";
            static T dummy;
            return dummy;
        }
        return data[index];
    }

    T &front()
    {
        if (empty())
        {
            cerr << "Error: MyVector is empty\n";
            static T dummy;
            return dummy;
        }
        return data[0];
    }

    const T &front() const
    {
        if (empty())
        {
            cerr << "Error: MyVector is empty\n";
            static T dummy;
            return dummy;
        }
        return data[0];
    }

    T &back()
    {
        if (empty())
        {
            cerr << "Error: MyVector is empty\n";
            static T dummy;
            return dummy;
        }
        return data[length - 1];
    }

    const T &back() const
    {
        if (empty())
        {
            cerr << "Error: MyVector is empty\n";
            static T dummy;
            return dummy;
        }
        return data[length - 1];
    }

    bool empty() const { return length == 0; }
    size_t size() const { return length; }

    void reserve(size_t new_capacity)
    {
        if (new_capacity > capacity)
        {
            reallocate(new_capacity);
        }
    }

    size_t get_capacity() const { return capacity; }

    void clear()
    {
        length = 0;
    }

    void push_back(const T &value)
    {
        if (length >= capacity)
        {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            reallocate(new_capacity);
        }
        data[length++] = value;
    }

    void pop_back()
    {
        if (length > 0)
            --length;
    }

    void resize(size_t new_size)
    {
        if (new_size > capacity)
            reserve(new_size);
        for (size_t i = length; i < new_size; ++i)
            data[i] = T();
        length = new_size;
    }

    void resize(size_t new_size, const T &value)
    {
        if (new_size > capacity)
            reserve(new_size);
        for (size_t i = length; i < new_size; ++i)
            data[i] = value;
        length = new_size;
    }

    T *begin() { return data; }
    const T *begin() const { return data; }
    T *end() { return data + length; }
    const T *end() const { return data + length; }

    typedef T value_type;
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;
};

template <typename T>
struct MyLess
{
    bool operator()(const T &a, const T &b) const
    {
        return a < b;
    }
};

#endif