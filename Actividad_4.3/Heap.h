#ifndef Heap_H
#define Heap_H

#include "DoublyLinkedList.h"

template<class T>
class Heap{
    public:
        Heap();
        Heap(DoublyLinkedList<T> &list);
        bool isEmpty();
        void insert(T data);
        T remove();
        T removeCount();
        void HeapSort(string order);
        void print();
        int getCount(int index);
        void printfive();
        void printHigh();
    private:
        void downSort(int index);
        void countDownSort(int index);
        void swap(int a, int b);
        int size;
        DoublyLinkedList<T> heap;
};

#endif