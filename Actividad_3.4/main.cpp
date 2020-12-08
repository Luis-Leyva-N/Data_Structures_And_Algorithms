#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

#include "Heap.h"

template<class T> //El ordenamiento puede tomar hasta 10-15 segundos.
void HeapSort(DoublyLinkedList<T> &list, string order){ //Ordenamos la lista.
    if(!list.isEmpty()){
        Heap<T> heapAux(list);
        list.clear();
        while(!heapAux.isEmpty()){
            T aux = heapAux.remove();
            if(order == "ascending"){
                list.addFirst(aux);
            } else {
                list.addLast(aux);
            }
        }
    }
}

//Quitamos los puertos de las IP para poder contar la cantidad de veces que aparecen en el registro
template<class T>
void erasePort(DoublyLinkedList<T> &list){ 
    for(int i = 1; i <= list.getSize();i++){
        string IP;
        IP = list[i];
        IP.erase(13,17);
        list.updateAt(i,IP);
    }
}


int main(){
    DoublyLinkedList<string> logs;
    DoublyLinkedList<string> count;
    
    logs.loadData();
    HeapSort(logs, "ascending");
    erasePort(logs);
    logs.orderedFile();

    int pos = 0;
    for(int i = 1; i <= logs.getSize();i++){
        if(i == 1){
            count.addLast(logs[i]);
            pos = 1;
            count.addCountAt(pos);
        }

        if(i+1 <= logs.getSize()){
            if(logs[i] == logs[i+1]){
                count.addCountAt(pos);
            } else {
                count.addLast(logs[i+1]);
                pos += 1;
                count.addCountAt(pos);
            }
        }
    }
    count.printWithCount();

    Heap<string> IPcount(count);
    IPcount.countFile();
    IPcount.HeapSort("descending");
    IPcount.countFile();

    cout << "Imprimiendo las 5 IPs mas repetidas:" << endl;
    IPcount.printfive();



    return 0;
}