#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

#include "DoublyLinkedList.h"

//Debido a la cantidad de dato el programa puede tardar 30s en cargar y ordenar los datos. (El tiempo varia dependendiendo de la maquina)
int main(){
    DoublyLinkedList Logs;

    Logs.loadData();
    Logs.sort();
    Logs.orderedFile();

    int a = -1;

    while(a != 0){
        cout << "1) Busqueda de registros" << endl << "0) Salir" << endl;
        cin >> a;
        switch(a){
            case 0:
                break;
            case 1:
                long long int a, b;
                int pos1, pos2;
                cout << "Rango menor" << endl;
                a = Logs.valorBusqueda();
                cout << "Rango mayor" << endl;
                b = Logs.valorBusqueda();

                pos1 = Logs.busquedaBinaria(a);
                pos2 = Logs.busquedaBinaria(b);

                Logs.printSearch(pos1, pos2);
                break;
        }
    }
    return 0;
}