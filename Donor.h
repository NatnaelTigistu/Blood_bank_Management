#ifndef DONOR_H
#define DONOR_H

#include <string>
using namespace std;

class Donor
{
public:
    int id;
    string name;
    string bloodGroup;
    int age;
    string contact;

    Donor();
    Donor(int, string, string, int, string);
};

#endif
