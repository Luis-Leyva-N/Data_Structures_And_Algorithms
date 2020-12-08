#ifndef Hash_H
#define Hash_H

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Hash{
    public:
        Hash();
        Hash(int size);
        int findData(string data);
        void addData(string data);
        void deleteData(string data);
        void printTable();
    private:
        vector<string> table;
        vector<bool> status;
        int size;
        int hashing(string data);
};

#endif