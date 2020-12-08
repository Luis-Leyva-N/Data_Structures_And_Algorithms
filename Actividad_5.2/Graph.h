#ifndef Graph_h
#define Graph_h

#include <vector>

using std::vector;

#include "Hash.h"

template<class T>
class Graph {
    public:
        Graph(int size);
        Graph(vector<vector<T>> list);
        void addVertex(T vert, T adj);
        void adjHash();
        void printAdjHash(T vert);
        void print();
    private:
        vector<vector<string>> adjList;
        vector<Hash> adjHashLists;
        vector<T> vertex;
        int findVertex(T vert);
};

#endif