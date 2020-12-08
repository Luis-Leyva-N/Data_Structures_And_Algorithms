#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

#include "Hash.h"

Hash::Hash(){

}

Hash::Hash(int size){
    this -> size = size;
    vector<string> tmpTable(size);
    vector<bool> tmpStatus(size,false);
    
    table = tmpTable;
    status = tmpStatus;
}

void Hash::addData(string data){
    int index = hashing(data);
    status[index] = true;
    table[index] = data;
}

void Hash::deleteData(string data){
    int index = findData(data);
    if(index >= 0){
        table[index].erase();
        status[index] = false;
        cout << endl << "El elemento " << data << " se elimino." << endl << endl;
    } else {
        cout << endl << "No se encontro el elemeno." << endl << endl; 
    }
}

int Hash::findData(string data){
    int sum = 0;
    int key = 0;
    for(auto c : data){
        sum += abs(int(c));
    }
    key = sum % size;

    if(status[key]){
        if(table[key] == data){
            return key;
        }
    } else {
        for(int i = 0; i < size; i++){
            int newKey = (key + i) % size;
            if(status[newKey]){
                if(table[newKey] == data){
                    return newKey;    
                }
            }
        }
    }
    return -1;
}

void Hash::printTable(){
    for (int i = 0; i < size; i++) { 
        cout << i << " -> " << table[i] << endl;
    }

    cout << endl;
}

// Manejo de colision lineal.
int Hash::hashing(string data){
    int sum = 0;
    int key = 0;
    for(auto c : data){
        sum += abs(int(c));
    }
    key = sum % size;

    if(!status[key]){
        return key;
    } else {
        for(int i = 1; i <= size; i++){
            int newKey = (key + i) % size;
            if(!status[newKey]){
                return newKey;
            }
        }
    }
    return -1;
}
