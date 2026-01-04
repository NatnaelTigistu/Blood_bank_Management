#include "../include/Donor.h"

Donor::Donor() {}

Donor::Donor(int i, string n, string bg, int a, string c)
{
    id = i;
    name = n;
    bloodGroup = bg;
    age = a;
    contact = c;
}
