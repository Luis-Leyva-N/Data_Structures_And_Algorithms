#ifndef Queue_h
#define Queue_h

#include "Node.h"

template<class T>
class Queue{
    public:
        Queue();
        void dequeue();
        void enqueue(T data);
        T front();
        T back();
        int getSize();
        void clear();
        void print();
        bool isEmpty();
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
};

#endif