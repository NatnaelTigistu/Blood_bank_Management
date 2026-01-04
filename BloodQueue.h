#ifndef BLOODQUEUE_H
#define BLOODQUEUE_H

#include <string>
#include <vector.h>
using namespace std;

struct Request
{
    string bloodGroup;
    int units;
    Request *next;
};

class BloodQueue
{
private:
    Request *front;
    Request *rear;

public:
    BloodQueue();
    void enqueue(string bg, int units);
    void dequeue(int bloodStock[], const string bloodGroups[], int size);
    void display();

    void saveToFile(const string &filename = "data/requests.txt");
    void loadFromFile(const string &filename = "data/requests.txt");

    Request *get_front();
    MyVector<Request> getAllRequests();
};

#endif
