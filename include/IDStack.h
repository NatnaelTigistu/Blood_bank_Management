#ifndef IDSTACK_H
#define IDSTACK_H

class IDStack
{
private:
    int *arr;
    int top;
    int capacity;

public:
    IDStack(int size = 1000);
    ~IDStack();

    bool isEmpty() const;
    bool isFull() const;

    void push(int value);
    int pop();
    int peek() const;

    int size() const;
};

#endif
