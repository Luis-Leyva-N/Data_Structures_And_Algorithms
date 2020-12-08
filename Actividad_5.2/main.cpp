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

    cout << "--Datos cargados--" << endl << endl;

    //Pasamos las adyaciencias a las tablas hash.
    cout << "Transfiriendo datos a tablas de Hash" << endl;
    IP.adjHash();
    cout << "--Completado--" << endl << endl;

    //Buscamos una IP
    cout << "---Seleccione una opcion---" << endl;
    cout << "1) Buscar" << endl;
    cout << "0) Salir" << endl;

    int op;
    cin >> op;

    while(op != 0){
        cout << "Ingrese una IP encontrar sus adyacencias: (Ej. 36.70.228.110)" << endl;
        string search;
        cin >> search;

        IP.printAdjHash(search);

        cout << endl << "---Seleccione una opcion---" << endl;
        cout << "1) Buscar" << endl;
        cout << "0) Salir" << endl;
        cin >> op;
    }
}