#include "BloodQueue.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

BloodQueue::BloodQueue()
{
    front = rear = nullptr;
}

void BloodQueue::enqueue(string bg, int units)
{
    Request *r = new Request{bg, units, nullptr};
    if (!rear)
        front = rear = r;
    else
    {
        rear->next = r;
        rear = r;
    }
}

void BloodQueue::dequeue(int bloodStock[], const string bloodGroups[], int size)
{
    if (!front)
    {
        cout << "No requests in the queue.\n";
        return;
    }

    Request *temp = front;
    front = front->next;
    if (!front)
        rear = nullptr;

    int idx = -1;
    for (int i = 0; i < size; i++)
        if (bloodGroups[i] == temp->bloodGroup)
        {
            idx = i;
            break;
        }

    if (idx == -1)
    {
        cout << "Error: Blood group not found.\n";
    }
    else if (bloodStock[idx] >= temp->units)
    {
        bloodStock[idx] -= temp->units;
        cout << "Processed request: " << temp->bloodGroup
             << " (" << temp->units << " units). Remaining: "
             << bloodStock[idx] << " units.\n";
    }
    else
    {
        cout << "Not enough stock for " << temp->bloodGroup
             << ". Requested: " << temp->units
             << ", Available: " << bloodStock[idx] << "\n";
    }

    delete temp;
}

void BloodQueue::display()
{
    if (!front)
    {
        cout << "No requests in the queue.\n";
        return;
    }

    cout << "Pending Requests:\n";
    Request *temp = front;
    while (temp)
    {
        cout << temp->bloodGroup << " - " << temp->units << " units\n";
        temp = temp->next;
    }
}

void BloodQueue::saveToFile(const string &filename)
{
    ofstream out(filename, ios::trunc);
    Request *temp = front;
    while (temp)
    {
        out << temp->bloodGroup << "," << temp->units << endl;
        temp = temp->next;
    }
    out.close();
}

void BloodQueue::loadFromFile(const string &filename)
{
    ifstream in(filename);
    if (!in.is_open())
        return;

    string line;
    while (getline(in, line))
    {
        size_t pos = line.find(',');
        if (pos == string::npos)
            continue;

        string bg = line.substr(0, pos);
        int units = stoi(line.substr(pos + 1));
        enqueue(bg, units);
    }
    in.close();
}

MyVector<Request> BloodQueue::getAllRequests()
{
    MyVector<Request> v;
    Request *temp = front;
    while (temp)
    {
        v.push_back({temp->bloodGroup, temp->units, nullptr});
        temp = temp->next;
    }
    return v;
}

Request *BloodQueue::get_front()
{
    return front;
}