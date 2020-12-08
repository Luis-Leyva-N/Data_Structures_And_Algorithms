#ifndef Graph_h
#define Graph_h

#include <vector>

using std::vector;

template<class T>
class Graph {
    public:
        Graph(int size);
        Graph(vector<vector<T>> list);
        void addVertex(T vert, T adj);
        vector<int> exportCount();
        vector<string> exportVertex();
        void print();
    private:
        vector<vector<string>> adjList;
        vector<T> vertex;
        int findVertex(T vert);
};

#endif