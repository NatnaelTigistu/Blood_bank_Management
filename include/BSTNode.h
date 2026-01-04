#ifndef BSTNODE_H
#define BSTNODE_H

#include "Donor.h"

class BSTNode
{
public:
    Donor donor;
    BSTNode *left;
    BSTNode *right;

    BSTNode(Donor d);
};

#endif
