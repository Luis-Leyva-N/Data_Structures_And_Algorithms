#pragma once

template<class T>
struct Node{
    T data;
    int count;
    Node<T> *next;
    Node<T> *prev;
    Node(T data);
    Node(T data, Node<T>* next);
    Node(T data, Node<T>* next, Node<T>* prev);
};

template<class T>
Node<T>::Node(T data) {
    count = 0;
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
Node<T>::Node(T data, Node<T>* next){
    count = 0;
    this -> data = data;
    this -> next = next;
    this -> prev = nullptr;
}

template<class T>
Node<T>::Node(T data, Node<T>* next, Node<T>* prev){
    count = 0;
    this->data = data;
    this->next = next;
    this->prev = prev;
}


