#include "../include/DonorBST.h"
#include <iostream>
#include <iomanip>
#include <../include/vector.h>
#include <limits>
using namespace std;

DonorBST::DonorBST()
{
    root = nullptr;
}

BSTNode *DonorBST::insert(BSTNode *node, Donor d)
{
    if (!node)
        return new BSTNode(d);

    if (d.id < node->donor.id)
        node->left = insert(node->left, d);
    else
        node->right = insert(node->right, d);

    return node;
}

void DonorBST::insertDonor(Donor d)
{
    root = insert(root, d);
}

BSTNode *DonorBST::deleteNode(BSTNode *node, int id)
{
    if (!node)
        return nullptr;

    if (id < node->donor.id)
        node->left = deleteNode(node->left, id);
    else if (id > node->donor.id)
        node->right = deleteNode(node->right, id);
    else
    {
        
        if (!node->left)
        { 
            BSTNode *temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right)
        { 
            BSTNode *temp = node->left;
            delete node;
            return temp;
        }
        else
        {
            
            BSTNode *temp = node->right;
            while (temp->left)
                temp = temp->left;

            node->donor = temp->donor;
            node->right = deleteNode(node->right, temp->donor.id); 
        }
    }
    return node;
}

void DonorBST::deleteDonor(int id)
{
    root = deleteNode(root, id);
    cout << "Donor with ID " << id << " deleted (if existed).\n";
}

void DonorBST::inorder(BSTNode *node)
{
    if (!node)
        return;

    inorder(node->left);

    cout << right
         << setw(4) << setfill('0') << node->donor.id << "  "
         << setfill(' ') << left
         << setw(20) << node->donor.name
         << setw(5) << node->donor.age
         << setw(10) << node->donor.bloodGroup
         << setw(15) << node->donor.contact
         << endl;

    inorder(node->right);
}

void DonorBST::displayDonors()
{
    if (!root)
    {
        cout << "No donors available\n";
        return;
    }

    
    cout << left << setfill(' ')
         << setw(6) << "ID"
         << setw(20) << "Name"
         << setw(5) << "Age"
         << setw(10) << "BloodGrp"
         << setw(15) << "Contact"
         << endl;

    cout << string(50, '-') << endl;

    inorder(root);
}
BSTNode *DonorBST::search(BSTNode *node, int id)
{
    if (!node || node->donor.id == id)
        return node;
    if (id < node->donor.id)
        return search(node->left, id);
    return search(node->right, id);
}

bool DonorBST::searchDonor(int id)
{
    BSTNode *res = search(root, id);
    if (res)
    {
        cout << "Found: " << res->donor.name
             << "\n"
             << "Age : " << res->donor.age
             << "\n"
             << "Blood Group : " << res->donor.bloodGroup
             << "\n"
             << "Contact : " << res->donor.contact
             << endl;
        return true;
    }
    else
        cout << "Donor not found\n";
    return false;
}


Donor *DonorBST::searchDonorPointer(int id)
{
    BSTNode *current = root;
    while (current)
    {
        if (id == current->donor.id)
            return &(current->donor);
        else if (id < current->donor.id)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

void DonorBST::updateDonor(int id)
{
    Donor *d = searchDonorPointer(id);
    if (!d)
    {
        cout << "Donor not found\n";
        return;
    }

    cout << "Updating donor: " << d->name << endl;
    cout << "Press any key to continue ... ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter new name (or '-' to skip): ";
    string name;
    getline(cin, name);
    if (name != "-")
        d->name = name;

    cout << "Enter new age (or -1 to skip): ";
    int age;
    cin >> age;
    if (age != -1)
        d->age = age;

    cout << "Enter new blood group (or '-' to skip): ";
    string blood;
    cin >> blood;
    if (blood != "-")
        d->bloodGroup = blood;

    cout << "Enter new contact (or '-' to skip): ";
    string contact;
    cin >> contact;
    if (contact != "-")
        d->contact = contact;

    cout << "Donor info updated successfully.\n";
}

void DonorBST::getAllDonorsHelper(BSTNode *node, MyVector<Donor> &donors)
{
    if (!node)
        return;
    getAllDonorsHelper(node->left, donors);
    donors.push_back(node->donor);
    getAllDonorsHelper(node->right, donors);
}

void DonorBST::getAllDonors(MyVector<Donor> &donors)
{
    getAllDonorsHelper(root, donors);
}
