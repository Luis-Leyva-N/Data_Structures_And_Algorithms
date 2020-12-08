#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::cout;
using std::cin;
using std::endl;

#include "Graph.h"
#include "DoublyLinkedList.h"
#include "Heap.h"

int main(){
    //Cargamos los datos
    cout << "Cargando datos..." << endl;
    ifstream IPs("bitacoraACT4_3.txt");
    string line, valor;
    char delim = ' ';
    int col, cantIP, cantEventos;

    //Cargamos la primera linea que contiene las cantidades de datos
    getline(IPs, line);
    stringstream ss(line);
    col = 0;
    while(getline(ss,valor,delim)){
        switch(col){
            case 0:
                cantIP = stoi(valor);
                break;
            case 1:
                cantEventos = stoi(valor);
                break;
        }
        col++;
    }

    //Saltamos las primeras lineas
    int i;
    for(i = 0; i < cantIP; i++){
        getline(IPs, line);
    }

    //Creamos el grafo
    Graph<string> IP(cantIP);

    //Cargamos los eventos y agregamos las ips origen y destino a la estructura de grafos
    //Los datos pueden tardar unos segundos en cargar
    string orig, dest;
    for(i = 0; i < cantEventos; i++){
        getline(IPs, line);
        stringstream ss(line);
        col = 0;
        while(getline(ss,valor,delim)){
            if(col < 5){
                switch(col){
                    case 3:
                        orig = valor.substr(0,valor.find(":",0));
                        break;
                    case 4:
                        dest = valor.substr(0,valor.find(":",0));
                        break;
                }
                col++;                
            } else {
                break;
            }
        }
        IP.addVertex(orig,dest);
    }

    cout << "--Datos cargados--" << endl;

    //Exportaremos dos vectores, uno con las ips de origen y otro con la cuenta de cada ip.
    cout << endl << "Contando adyacencias..." << endl;

    vector<int> adjcount = IP.exportCount();
    vector<string> ipVertex = IP.exportVertex(); 

    //Convertimos los vectores en un doubly linked list para poder usarlo en un heap.
    DoublyLinkedList<string> ipCount;
    ipCount = ipVertex;
    
    for(int i = 0; i < ipVertex.size(); i++){
        ipCount.updateCountAt(i+1,adjcount[i]);
    }

    cout << "--Adyacencias contadas--" << endl;

    cout << endl << "Imprimiendo la IP con mas adyacencias" << endl;
    //Convertimos la lista en heap y lo ordenamos descendientemente por la cuenta
    Heap<string> heap(ipCount);
    heap.HeapSort("descending");

    //Imprimimos la que tenga mas adyacencias
    heap.printHigh();

    cout << endl << "Imprimiendo las 5 IP con mas adyacencias" << endl;

    heap.printfive();
    return 0;
}