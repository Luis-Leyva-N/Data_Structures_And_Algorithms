#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include <vector>

using std::vector;

#include "Node.h"

template<class T>
class DoublyLinkedList {
    public:
        DoublyLinkedList();
        void operator=(vector<T> list);
        void operator=(DoublyLinkedList<T> list);
        T& operator[](int index);
        void addFirst(T data);
        void addLast(T data);
        bool deleteData(T data); 
        bool deleteAt(int index); 
        T getData(int index);
        int getCount(int index);
        Node<T>* getNode(int index); 
        void updateAt(int index, T newData);
        void updateCountAt(int index, int newCount);
        void addCountAt(int index);
        void updateData(T data, T newData);
        void insertAt(int index, T newData);
        void clear();
        void print();
        void printReverse();
        bool isEmpty();
        int getSize();
        int headCount();
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
};

#endif