#ifndef DONORBST_H
#define DONORBST_H

#include "BSTNode.h"
#include <vector.h>
using namespace std;

class DonorBST
{
private:
    BSTNode *root;

    BSTNode *insert(BSTNode *, Donor);
    void inorder(BSTNode *);
    BSTNode *search(BSTNode *, int);
    BSTNode *deleteNode(BSTNode *, int);
    void getAllDonorsHelper(BSTNode *node, MyVector<Donor> &donors);

public:
    DonorBST();

    void insertDonor(Donor);
    void displayDonors();
    bool searchDonor(int);
    void deleteDonor(int id);
    void updateDonor(int id);

    Donor *searchDonorPointer(int id);
    void getAllDonors(MyVector<Donor> &donors);
};

#endif
