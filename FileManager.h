#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector.h>
using namespace std;

class FileManager
{
public:
    static void save(string file, string data);
    static MyVector<string> readLines(string file);
};

#endif
