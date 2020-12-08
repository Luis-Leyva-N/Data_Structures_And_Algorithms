#ifndef Queue_h
#define Queue_h

#include "Node.h"

//Usado para la dos listas del ordenamiento
class Queue{
    public:
        Queue();
        bool isEmpty();
        void enqueue(Node temp);
        void dequeue();
        long long int getData();
        Node* getNode();
        void print();
    private:
        Node* head;
        Node* tail;
        int size;
};

Queue::Queue(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}

bool Queue::isEmpty(){
    return size == 0;
}

//Agregamos un nuevo elemento de la queue
/*asignar el head a temp con o sin apuntador causaba problemas al desplegar datos
 por ende tuve que asignar cada valor individualmente para evitar este tipo de problemas.*/
void Queue::enqueue(Node temp){
    if(size == 0){
        head = new Node;
        head->mes = temp.mes;
        head->dia = temp.dia;
        head->seg = temp.seg;
        head->min = temp.min;
        head->hora = temp.hora;
        head->tiempo = temp.tiempo;
        head->ip = temp.ip;
        head->event = temp.event;
        head->ordenFecha = temp.ordenFecha;
        tail = head;
        size++;
    } else {
        tail->next = new Node;
        tail = tail->next;
        tail->mes = temp.mes;
        tail->dia = temp.dia;
        tail->seg = temp.seg;
        tail->min = temp.min;
        tail->hora = temp.hora;
        tail->tiempo = temp.tiempo;
        tail->ip = temp.ip;
        tail->event = temp.event;
        tail->ordenFecha = temp.ordenFecha;
        size++;
    }  
}

//Eliminamos el primer elemento de la queue
void Queue::dequeue(){
    if(!isEmpty()){
        Node *aux = head->next;
        delete head;
        head = aux;
        size--;
    } 
}

//regresamos el dato usado para el ordenamiento
long long int Queue::getData(){
    if(!isEmpty()){
        Node *aux = head;
        return aux->ordenFecha;
    }
    return 0;
}

Node* Queue::getNode(){
    return head;
}

void Queue::print(){
    Node *temp = head;

    for(int i = 0; i < size; i++){
        cout << temp->ordenFecha << " ";
        cout << temp->mes << " ";
        cout << temp->dia << " ";
        cout << temp->tiempo << " ";
        cout << temp->ip << " ";
        cout << temp->event << endl;

        temp = temp->next;
    }
}

#endif