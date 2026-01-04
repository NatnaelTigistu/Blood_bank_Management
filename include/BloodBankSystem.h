#ifndef BLOODBANKSYSTEM_H
#define BLOODBANKSYSTEM_H

#include "DonorBST.h"
#include "BloodQueue.h"
#include "BloodInventory.h"
#include "IDStack.h"

class BloodBankSystem
{
private:
    static const int size = 8;
    string bloodGroups[size] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    int bloodStock[size] = {0};
    IDStack reusableIDs;

    DonorBST donorTree;
    BloodQueue requestQueue;
    BloodInventory inventory;

    void loadDonors();
    void saveDonors();
    void saveBloodStock();
    void loadBloodStock();
    int generateNextDonorID();

    void loadReusableIDs();
    void saveReusableIDs();

public:
    void menu();
};

#endif
