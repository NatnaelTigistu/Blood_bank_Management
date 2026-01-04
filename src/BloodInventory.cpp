#include "../include/BloodInventory.h"
#include <iostream>
#include <fstream>
#include <../include/vector.h>

void BloodInventory::addBloodUnit(string bloodGroup, int expiryDate, int amount)
{
    pq.push(BloodUnit(bloodGroup, expiryDate, amount));
    saveInventory();
}

void BloodInventory::showInventory()
{
    if (pq.empty())
    {
        cout << "Inventory is empty.\n";
        return;
    }

    priority_queue<BloodUnit, MyVector<BloodUnit>, CompareExpiry> temp = pq;
    cout << "Blood Inventory:\n";
    while (!temp.empty())
    {
        BloodUnit unit = temp.top();
        temp.pop();
        cout << "Blood Group: " << unit.bloodGroup
             << ", Expiry: "
             << unit.expiryDate / 10000 << "-"
             << (unit.expiryDate / 100) % 100 << "-"
             << unit.expiryDate % 100
             << ", Amount: " << unit.amount << endl;
    }
}

bool BloodInventory::reduceBlood(string bloodGroup, int requiredAmount)
{
    if (pq.empty())
        return false;

    priority_queue<BloodUnit, MyVector<BloodUnit>, CompareExpiry> temp;
    bool fulfilled = false;

    while (!pq.empty() && requiredAmount > 0)
    {
        BloodUnit unit = pq.top();
        pq.pop();

        if (unit.bloodGroup == bloodGroup)
        {
            if (unit.amount > requiredAmount)
            {
                unit.amount -= requiredAmount;
                requiredAmount = 0;
                fulfilled = true;
            }
            else
            {
                requiredAmount -= unit.amount;
                unit.amount = 0;
            }
        }

        if (unit.amount > 0)
            temp.push(unit);
    }

    while (!pq.empty())
    {
        temp.push(pq.top());
        pq.pop();
    }

    pq = temp;

    if (fulfilled)
    {
        saveInventory();
        cout << "Blood issued successfully.\n";
        return true;
    }
    else
    {
        return false;
    }
}

void BloodInventory::removeExpiredUnits(int today)
{
    priority_queue<BloodUnit, MyVector<BloodUnit>, CompareExpiry> temp;
    while (!pq.empty())
    {
        BloodUnit unit = pq.top();
        pq.pop();
        if (unit.expiryDate >= today)
            temp.push(unit); 
    }
    pq = temp;
    cout << "Expired units removed.\n";
    saveInventory();
}

BloodUnit BloodInventory::getNearestExpiry()
{
    if (pq.empty())
        return BloodUnit(); 
    return pq.top();
}

void BloodInventory::saveInventory(const string &filename)
{
    ofstream out(filename, ios::trunc);
    if (!out)
    {
        cout << "Error saving inventory to file!\n";
        return;
    }

    priority_queue<BloodUnit, MyVector<BloodUnit>, CompareExpiry> temp = pq;
    while (!temp.empty())
    {
        BloodUnit unit = temp.top();
        temp.pop();
        out << unit.bloodGroup << "," << unit.expiryDate << "," << unit.amount << "\n";
    }
    out.close();
}

void BloodInventory::loadInventory(const string &filename)
{
    ifstream in(filename);
    if (!in)
        return;

    string line;
    while (getline(in, line))
    {
        size_t pos = line.find(',');
        if (pos == string::npos)
            continue;

        string bg = line.substr(0, pos);
        int expiry = stoi(line.substr(pos + 1, line.find_last_of(',') - pos - 1));
        int amount = stoi(line.substr(line.find_last_of(',') + 1));
        pq.push(BloodUnit(bg, expiry, amount));
    }
    in.close();
}