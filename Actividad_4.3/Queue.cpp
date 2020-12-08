#include <iostream>
#include <string>
#include <exception>

using std::cout;
using std::endl;
using std::string;
using std::runtime_error;

#include "Queue.h"

template<class T>
Queue<T>::Queue(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}

//Elimina el el elemento al frente de la queue.
template<class T> //O(1) 
void Queue<T>::dequeue(){
    if(!isEmpty()){
        Node<T> *aux = head->next;
        delete head;
        head = aux;
        size--;
    } else {
        throw runtime_error("No hay elementos");
    }
}

//Agrega un elemento a la cola de queue.
template<class T> //O(1) 
void Queue<T>::enqueue(T data){
    if(size == 0){
        head = new Node<T>(data);
        tail = head;
        size++;
    } else {
        tail->next = new Node<T>(data);
        tail = tail->next;
        size++;
    }  
}

//Devuelve el elemento al frente.
template<class T> //O(1) 
T Queue<T>::front(){
    if(!isEmpty()){
       return head->data; 
    }
    throw runtime_error("No hay elementos");
}

//Devuelve el elemento en la cola.
template<class T> //O(1) 
T Queue<T>::back(){
    if(!isEmpty()){
       return tail->data; 
    }
    throw runtime_error("No hay elementos");
}

//Regresa el tamano de la lista.
template<class T> //O(1) 
int Queue<T>::getSize(){
    return size;
}

//limpia la lista
template<class T> //O(n) 
void Queue<T>::clear(){
    if(!isEmpty()){
        Node<T> *aux;
        while(head != nullptr){
            aux = head->next;
            delete head;
            head = aux;
        }
        size = 0;
    }
}

//imprime la queue
template<class T> //O(n) 
void Queue<T>::print(){
    if(!isEmpty()){
        Node<T> *aux = head;
        for(int i = 0; i<size; i++){
            cout << aux->data << " ";
            aux = aux->next;
        }
        cout << endl; 
    } else {
        cout << "La lista esta vacia" << endl;;
    }
}

//verifica que la lista este vacia.
template<class T>
bool Queue<T>::isEmpty(){
    return size == 0;
}

template class Queue<string>;