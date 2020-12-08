#include <iostream>
#include <string>
#include <exception>

using std::cout;
using std::endl;
using std::string;
using std::runtime_error;

#include "DoublyLinkedList.h"
#include "Heap.h"

template<class T>
Heap<T>::Heap(){
    size = 0;
}

template<class T>
Heap<T>::Heap(DoublyLinkedList<T> &list){
    if(!list.isEmpty()){
        heap = list;
        size = list.getSize();
        int index = size / 2;
        if(heap.headCount() != 0){
            countDownSort(index);
        } else {
            downSort(index);
        }
        
    } else {
        throw runtime_error("The list is empty");
    }
}

template<class T>
bool Heap<T>::isEmpty(){
    return size == 0;
}

template<class T>
void Heap<T>::insert(T data){
    if(!isEmpty()){
        heap.addLast(data);
        size = heap.getSize();
        int index = size / 2;
        downSort(index);
    }
}

template<class T>
T Heap<T>::remove(){
    if(!isEmpty()){
        T aux = heap[1];
        swap(1,size);
        heap.deleteAt(size);
        size--;
        downSort(1);
        return aux;
    }
    throw runtime_error("The heap is empty");
}

template<class T>
T Heap<T>::removeCount(){
    if(!isEmpty()){
        T aux = heap[1];
        swap(1,size);
        heap.deleteAt(size);
        size--;
        countDownSort(1);
        return aux;
    }
    throw runtime_error("The heap is empty");
}


template<class T>
void Heap<T>::HeapSort(string order){
    if(!isEmpty()){
        Heap<T> heapAux(heap);
        heap.clear();
        int pos = 1;
        int count;
        while(!heapAux.isEmpty()){
            if(order == "ascending"){
                count = heapAux.getCount(1);
                heap.addFirst(heapAux.removeCount());
                heap.updateCountAt(1,count);
            } else {
                count = heapAux.getCount(1);
                heap.addLast(heapAux.removeCount());
                heap.updateCountAt(pos,count);
                pos++;
            }
        }
        return;
    } else {
       throw runtime_error("The heap is empty"); 
    }
}

template<class T>
void Heap<T>::print(){
    heap.print();
}

template<class T>
int Heap<T>::getCount(int index){
    return heap.getCount(index);
}

template<class T>
void Heap<T>::printfive(){
    for(int i = 1; i <= 5; i++){
        cout << heap.getData(i) << " " << heap.getCount(i) << endl;
    }
}

template<class T>
void Heap<T>::printHigh(){
    cout << heap.getData(1) << " " << heap.getCount(1) << endl;
}

template<class T>
void Heap<T>::downSort(int index){
    while(index >= 1){
        int pos = index;
        while(pos*2 <= size){
            int s1 = pos*2;
            int s2 = pos*2+1;
            int max;
            if(s2 > size){
                max = s1;
            } else {
                heap[s1] > heap[s2] ? max = s1 : max = s2;
            }
            if(heap[max] > heap[pos]){
                swap(pos, max);
                pos = max;
            } else {
                pos = size;
            }
        }
        index--;
    }
}

template<class T>
void Heap<T>::countDownSort(int index){
    while(index >= 1){
        int pos = index;
        while(pos*2 <= size){
            int s1 = pos*2;
            int s2 = pos*2+1;
            int max;
            if(s2 > size){
                max = s1;
            } else {
                heap.getCount(s1) > heap.getCount(s2) ? max = s1 : max = s2;
            }
            if(heap.getCount(max) > heap.getCount(pos)){
                swap(pos, max);
                pos = max;
            } else {
                pos = size;
            }
        }
        index--;
    } 
}

template<class T>
void Heap<T>::swap(int a, int b){
    T aux = heap[a];
    heap[a] = heap[b];
    heap[b] = aux;

    int aux2 = heap.getCount(a);
    heap.updateCountAt(a,heap.getCount(b));
    heap.updateCountAt(b,aux2);
}

template class Heap<string>;