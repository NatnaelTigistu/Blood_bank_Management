#ifndef QUEUE_H
#define QUEUE_H

#include "vector.h"
#include <iostream>
using namespace std;

template <typename T, typename Container = MyVector<T>, typename Compare = less<typename Container::value_type>>
class priority_queue
{
private:
    Container data;
    Compare cmp;

    void heapify_up(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (cmp(data[parent], data[index]))
            {
                swap(data[parent], data[index]);
                index = parent;
            }
            else
                break;
        }
    }

    void heapify_down(int index)
    {
        int n = data.size();
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < n && cmp(data[largest], data[left]))
                largest = left;
            if (right < n && cmp(data[largest], data[right]))
                largest = right;

            if (largest != index)
            {
                swap(data[index], data[largest]);
                index = largest;
            }
            else
                break;
        }
    }

public:
    priority_queue() {}

    explicit priority_queue(const Compare &comp) : cmp(comp) {}

    template <class InputIterator>
    priority_queue(InputIterator first, InputIterator last, const Compare &comp = Compare()) : cmp(comp)
    {
        while (first != last)
        {
            data.push_back(*first);
            ++first;
        }
        for (int i = (data.size() / 2) - 1; i >= 0; --i)
            heapify_down(i);
    }

    bool empty() const { return data.empty(); }

    size_t size() const { return data.size(); }

    const T &top() const
    {
        if (data.empty())
        {
            cerr << "Error: priority_queue is empty\n";
            static T dummy;
            return dummy;
        }
        return data[0];
    }

    T &top()
    {
        if (data.empty())
        {
            cerr << "Error: priority_queue is empty\n";
            static T dummy;
            return dummy;
        }
        return data[0];
    }

    void push(const T &item)
    {
        data.push_back(item);
        heapify_up(data.size() - 1);
    }

    void pop()
    {
        if (data.empty())
            return;
        data[0] = data.back();
        data.pop_back();
        if (!data.empty())
            heapify_down(0);
    }
};

template <typename T>
class queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &d) : data(d), next(nullptr) {}
    };

    Node *front;
    Node *rear;
    size_t count;

public:
    queue() : front(nullptr), rear(nullptr), count(0) {}

    ~queue()
    {
        while (!empty())
            pop();
    }

    bool empty() const { return count == 0; }

    size_t size() const { return count; }

    T &front_element()
    {
        if (empty())
        {
            cerr << "Error: queue is empty\n";
            static T dummy;
            return dummy;
        }
        return front->data;
    }

    const T &front_element() const
    {
        if (empty())
        {
            cerr << "Error: queue is empty\n";
            static T dummy;
            return dummy;
        }
        return front->data;
    }

    T &back()
    {
        if (empty())
        {
            cerr << "Error: queue is empty\n";
            static T dummy;
            return dummy;
        }
        return rear->data;
    }

    const T &back() const
    {
        if (empty())
        {
            cerr << "Error: queue is empty\n";
            static T dummy;
            return dummy;
        }
        return rear->data;
    }

    void push(const T &item)
    {
        Node *newNode = new Node(item);
        if (rear)
        {
            rear->next = newNode;
            rear = newNode;
        }
        else
        {
            front = rear = newNode;
        }
        count++;
    }

    void pop()
    {
        if (empty())
            return;
        Node *temp = front;
        front = front->next;
        if (!front)
            rear = nullptr;
        delete temp;
        count--;
    }
};

#endif