#include "../include/IDStack.h"
#include <iostream>

IDStack::IDStack(int size)
{
    capacity = size;
    arr = new int[capacity];
    top = -1;
}

IDStack::~IDStack()
{
    delete[] arr;
}

bool IDStack::isEmpty() const
{
    return top == -1;
}

bool IDStack::isFull() const
{
    return top == capacity - 1;
}

void IDStack::push(int value)
{
    if (isFull())
    {
        std::cout << "ID stack overflow!\n";
        return;
    }
    arr[++top] = value;
}

int IDStack::pop()
{
    if (isEmpty())
    {
        std::cout << "ID stack underflow!\n";
        return -1;
    }
    return arr[top--];
}

int IDStack::peek() const
{
    if (isEmpty())
        return -1;
    return arr[top];
}

int IDStack::size() const
{
    return top + 1;
}
