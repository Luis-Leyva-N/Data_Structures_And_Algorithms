#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using std::cout;
using std::endl;
using std::find;
using std::iterator;
using std::vector;
using std::queue;
using std::string;

#include "Graph.h"
#include "Hash.h"

//Inicializamos el grafo sin ningun elemento
template<class T> //O(1)
Graph<T>::Graph(int size){
    vector<T> temp;
    vector<vector<T>> tempList(size,temp);
    adjList = tempList;
}

//Inicializamos el grafo con una lista predeterminada
template<class T> //O(n)
Graph<T>::Graph(vector<vector<T>> list){
    int source = 0;
    int target = 1;

    for(vector<T> adj : list){
        T temp = adj[source];
        int pos = findVertex(temp);
        if(pos < 0){
            vertex.push_back(temp);
        }
        temp = adj[target];
        pos = findVertex(temp);
        if(pos < 0){
            vertex.push_back(temp);
        }
    }
    
    sort(vertex.begin(),vertex.end());

    vector<T> temp;
    vector<vector<T>> tempList(vertex.size(),temp);
    adjList = tempList;

    for(auto path:list){
        int pos = findVertex(path[source]);
        T adj;
        adj = path[target];
        adjList[pos].push_back(adj);
    }
}

//Agregamos un nuevo vertice y su adyaciencia
template<class T> //O(1)
void Graph<T>::addVertex(T vert, T adj){
    int pos = findVertex(vert);
    if(pos < 0){
        vertex.push_back(vert);
    }
    pos = findVertex(adj);
    if(pos < 0){
        vertex.push_back(adj);
    }

    pos = findVertex(vert);
    adjList[pos].push_back(adj);    
}

//Transformamos la lista en hash tables para cada vertice
template<class T>
void Graph<T>::adjHash(){
    for(int i = 0; i < adjList.size();i++){
        Hash temp(adjList[i].size());
        for(auto j : adjList[i]){
            temp.addData(j);
        }

        adjHashLists.push_back(temp);
    }
}

//Imprimimos la hash table que contiene las adyacencias del vertice seleccionado.
template<class T>
void Graph<T>::printAdjHash(T vert){
    int pos = findVertex(vert);
    if(pos >= 0){
        adjHashLists[pos].printTable();
    } else {
        cout << "No se encontro el vertice" << endl;
    }
}

//Funcion para imprimir el grafo
template<class T> //O(n)
void Graph<T>::print(){
    for(int i = 0; i < vertex.size(); i++){
        cout << vertex[i] << " -> ";
        for(T adj : adjList[i]){
            cout << adj << " ";
        }
        cout << endl;
    }
}

template<class T>
int Graph<T>::findVertex(T vert){
    typename vector<T>::iterator it = find(vertex.begin(),vertex.end(), vert);

    if(it != vertex.end()){
        return it - vertex.begin();
    } else {
        return -1;
    }
}

template class Graph<string>;