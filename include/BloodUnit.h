#ifndef BLOODUNIT_H
#define BLOODUNIT_H

#include <string>
using namespace std;

class BloodUnit
{
public:
    string bloodGroup;
    int amount;
    int expiryDate;

    BloodUnit(string bg = "", int exp = 0, int amt = 1);
};

#endif
