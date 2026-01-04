#include "../include/FileManager.h"
#include <fstream>
#include <iostream>

void FileManager::save(string file, string data)
{
    ofstream out(file, ios::app);
    out << data << endl;
    out.close();
}

MyVector<string> FileManager::readLines(string file)
{
    MyVector<string> lines;
    ifstream in(file);
    if (!in)
    {
        cerr << "Warning: File " << file << " not found.\n";
        return lines;
    }
    string line;
    while (getline(in, line))
    {
        if (!line.empty())
            lines.push_back(line);
    }
    in.close();
    return lines;
}
