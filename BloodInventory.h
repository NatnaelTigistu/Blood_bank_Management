#ifndef BLOODINVENTORY_H
#define BLOODINVENTORY_H

#include <queue.h>
#include <vector.h>
#include <string>
#include "BloodUnit.h"

using namespace std;

struct CompareExpiry
{
    bool operator()(const BloodUnit &a, const BloodUnit &b)
    {
        return a.expiryDate > b.expiryDate;
    }
};

class BloodInventory
{
private:
    priority_queue<BloodUnit, MyVector<BloodUnit>, CompareExpiry> pq;

public:
    void addBloodUnit(string bloodGroup, int expiryDate, int amount);
    void showInventory();
    void removeExpiredUnits(int today);
    BloodUnit getNearestExpiry();
    bool reduceBlood(string bloodGroup, int requiredAmount);

    void saveInventory(const string &filename = "data/blood_inventory.txt");
    void loadInventory(const string &filename = "data/blood_inventory.txt");
};

#endif
