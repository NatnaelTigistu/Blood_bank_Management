#include "../include/BloodBankSystem.h"
#include <iostream>
#include <iomanip> 
#include <limits>
#include "../include/FileManager.h"
#include <sstream>
#include <cmath>
#include <fstream>

using namespace std;


void BloodBankSystem::menu()
{
    loadDonors(); 
    inventory.loadInventory();
    requestQueue.loadFromFile();
    loadBloodStock();
    loadReusableIDs();

    int ch, id;
    do
    {
        cout << "\n===== Blood Bank Management System =====\n";
        cout << "1  Add Donor\n"
             << "2  Display Donors\n"
             << "3  Search Donor\n"
             << "4  Add Request\n"
             << "5  Show all Requests\n"
             << "6  Process Request\n"
             << "7  Update Donor Info\n"
             << "8  Delete Donor\n"
             << "9  Add Blood Stock\n"        
             << "10 View Inventory\n"          
             << "11 Blood Expiry Management\n" 
             << "0  Exit\n";

        while (true)
        {
            cout << "Enter choice: ";

            if (!(cin >> ch))
            {
                cout << "Invalid input, please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue; 
            }
            else
            {
                break;
            }
        }

        switch (ch)
        {
        case 1:
        {
            int age;
            string name, bg, contact;

            if (!reusableIDs.isEmpty())
            {
                id = reusableIDs.peek();
                reusableIDs.pop();
            }
            else
            {
                id = generateNextDonorID();
            }

            cout << "Donor ID : " << setw(4) << setfill('0') << id << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Name: ";
            getline(cin, name);

            while (true)
            {
                cout << "Blood Group (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
                cin >> bg;

                if (bg == "A+" || bg == "A-" ||
                    bg == "B+" || bg == "B-" ||
                    bg == "AB+" || bg == "AB-" ||
                    bg == "O+" || bg == "O-")
                    break;

                cout << "Invalid blood group. Please re-enter.\n";
            }

            while (true)
            {
                cout << "Age (18 - 65): ";
                cin >> age;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number.\n";
                    continue;
                }

                if (age >= 18 && age <= 65)
                    break;

                cout << "Age must be between 18 and 65.\n";
            }

            string input;

            while (true)
            {
                cout << "Contact : 09";
                cin >> input;

                
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                bool valid = (input.length() == 8);

                for (char c : input)
                {
                    if (!isdigit(c))
                    {
                        valid = false;
                        break;
                    }
                }

                if (valid)
                {
                    contact = "09" + input;
                    break;
                }

                cout << "Invalid contact. Enter exactly 8 digits.\n";
            }

            donorTree.insertDonor(Donor(id, name, bg, age, contact));

            cout << "Donor have been added successfully!\n";
            break;
        }

        case 2:
            donorTree.displayDonors();
            break;

        case 3:
        {
            cout << "ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            bool found = donorTree.searchDonor(id);
            break;
        }
        case 4:
        {
            string bg;
            int u;

            cout << "Available Blood Groups and Stock:\n";
            for (int i = 0; i < size; i++)
                cout << bloodGroups[i] << ": " << bloodStock[i] << " units\n";

            cout << "Enter Blood Group: ";
            cin >> bg;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            bool valid = false;
            for (int i = 0; i < size; i++)
            {
                if (bg == bloodGroups[i])
                {
                    valid = true;
                    break;
                }
            }
            if (!valid)
            {
                cout << "Invalid blood group.\n";
                break;
            }

            cout << "Enter Units: ";
            cin >> u;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (u <= 0)
            {
                cout << "Units must be positive.\n";
                break;
            }

            requestQueue.enqueue(bg, u);
            cout << "Request added: " << bg << " (" << u << " units)\n";
            break;
        }

        case 5:
            requestQueue.display();
            break;

        case 6:
            if (!requestQueue.get_front())
            {
                cout << "No requests in the queue.\n";
                break;
            }
            inventory.reduceBlood(requestQueue.get_front()->bloodGroup, requestQueue.get_front()->units);
            requestQueue.dequeue(bloodStock, bloodGroups, size);
            saveBloodStock();
            break;

        case 7:
            cout << "ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline
            donorTree.updateDonor(id);
            break;

        case 8:
        {
            cout << "ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

            bool found = donorTree.searchDonor(id);
            if (found)
            {
                char confirm;
                cout << "Are you sure you want to permanently delete this donor? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y')
                {
                    donorTree.deleteDonor(id);
                    reusableIDs.push(id);
                    cout << "Donor deleted successfully.\n";
                }
                else
                {
                    cout << "Deletion cancelled.\n";
                }
            }
        }
        break;
        case 9: 
        {
            string bg;
            int year, month, day, amount;

            bool validBG = false;
            do
            {
                cout << "Enter Blood Group (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
                cin >> bg;
                if (bg == "A+" || bg == "A-" || bg == "B+" || bg == "B-" ||
                    bg == "AB+" || bg == "AB-" || bg == "O+" || bg == "O-")
                {
                    validBG = true;
                }
                else
                {
                    cout << "Invalid blood group! Try again.\n";
                }
            } while (!validBG);

            do
            {
                cout << "Enter Amount of Blood Units (positive number): ";
                cin >> amount;
                if (amount <= 0)
                    cout << "Invalid amount! Must be positive.\n";
            } while (amount <= 0);

            do
            {
                cout << "Enter Year (YYYY): ";
                cin >> year;
                if (9999 <= year || year < 1900)
                {
                    cout << "Invalid year! Must be 1900 or later and not further than 9998.\n";
                    continue;
                }

                cout << "Enter Month (1-12): ";
                cin >> month;
                if (month < 1 || month > 12)
                {
                    cout << "Invalid month! Must be between 1 and 12.\n";
                    continue;
                }

                cout << "Enter Day (1-31): ";
                cin >> day;
                if (day < 1 || day > 31)
                {
                    cout << "Invalid day! Must be between 1 and 31.\n";
                    continue;
                }

                break;

            } while (true);

            cout << "You entered: " << year << "-" << month << "-" << day << endl;

            day += 42; 

            while (day > 30)
            {
                day -= 30;
                month += 1;
            }
            while (month > 12)
            {
                month -= 12;
                year += 1;
            }

            int expiryDate = year * 10000 + month * 100 + day;

            inventory.addBloodUnit(bg, expiryDate, amount);

            for (int i = 0; i < size; i++)
            {
                if (bloodGroups[i] == bg)
                {
                    bloodStock[i] += amount;
                    break;
                }
            }

            cout << amount << " units of " << bg << " added successfully!\n";
        }
        break;

        case 10: 
            inventory.showInventory();
            cout << "Available Blood Groups and Stock:\n";
            for (int i = 0; i < size; i++)
                cout << bloodGroups[i] << ": " << bloodStock[i] << " units\n";
            break;

        case 11: 
        {
            BloodUnit nearest = inventory.getNearestExpiry();
            if (nearest.bloodGroup == "")
                cout << "No blood units in stock.\n";
            else
                cout << "Nearest expiry: " << nearest.bloodGroup
                     << ", Expiry: "
                     << nearest.expiryDate / 10000 << "-"
                     << (nearest.expiryDate / 100) % 100 << "-"
                     << nearest.expiryDate % 100
                     << " Remaining Units: " << nearest.amount
                     << endl;

            break;
        }

        case 0:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (ch != 0);
    saveDonors();
    saveBloodStock();
    saveReusableIDs();
    requestQueue.saveToFile();
}

void BloodBankSystem::loadDonors()
{
    MyVector<string> lines = FileManager::readLines("data/donors.txt");

    for (auto &line : lines)
    {
        int id, age;
        string name, bg, contact;

        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos)
            continue; 

        id = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        bg = line.substr(pos2 + 1, pos3 - pos2 - 1);
        age = stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
        contact = line.substr(pos4 + 1);

        donorTree.insertDonor(Donor(id, name, bg, age, contact));
    }
}

void BloodBankSystem::saveDonors()
{
    MyVector<Donor> allDonors;
    donorTree.getAllDonors(allDonors);

    ofstream out("data/donors.txt", ios::trunc);
    for (auto &d : allDonors)
    {
        out << d.id << "," << d.name << "," << d.bloodGroup << ","
            << d.age << "," << d.contact << endl;
    }
    out.close();
}

int BloodBankSystem::generateNextDonorID()
{
    MyVector<string> lines = FileManager::readLines("data/donor_id.txt");

    int n = 0; 
    if (!lines.empty())
        n = stoi(lines.back());

    const int MAX = 10000;

    int L = 0;
    while ((1 << (L + 1)) - 1 <= n)
        L++;

    int firstIndexAtLevel = (1 << L) - 1;
    int k = n - firstIndexAtLevel;

    int step = MAX / (1 << (L + 1));
    int id = (2 * k + 1) * step;

    if (id <= 0 || id >= MAX)
    {
        cerr << "Donor ID limit reached\n";
        return -1;
    }

    FileManager::save("data/donor_id.txt", to_string(n + 1));

    return id;
}

void BloodBankSystem::saveBloodStock()
{
    ofstream out("data/blood_stock.txt", ios::trunc); 

    if (!out.is_open())
    {
        cout << "Error: Unable to save blood stock file.\n";
        return;
    }

    for (int i = 0; i < size; i++)
    {
        out << bloodStock[i] << endl; 
    }

    out.close();
}

void BloodBankSystem::loadBloodStock()
{
    MyVector<string> lines = FileManager::readLines("data/blood_stock.txt");
    for (int i = 0; i < size && i < lines.size(); i++)
    {
        bloodStock[i] = stoi(lines[i]); 
    }
}

void BloodBankSystem::loadReusableIDs()
{
    ifstream in("data/deleted_ids.txt");
    if (!in)
        return;

    int id;
    while (in >> id)
        reusableIDs.push(id);

    in.close();
}

void BloodBankSystem::saveReusableIDs()
{
    ofstream out("data/deleted_ids.txt", ios::trunc);
    while (!reusableIDs.isEmpty())
    {
        out << reusableIDs.peek() << endl;
        reusableIDs.pop();
    }
    out.close();
}
