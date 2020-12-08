#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include <initializer_list>

#include "Node.h"
#include "Queue.h"

using std::initializer_list;

template<class T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
    void mergeSort(int ini, int fin);
    void merge(int ini, int mid, int fin);
public:
    DoublyLinkedList();
    void operator=(initializer_list<T> list);
    void operator=(DoublyLinkedList<T> list);
    void loadData();
    void orderedFile();
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
    void duplicate();
    void removeDuplicates();
    int findData(T data);
    void sort();
    void clear();
    void print();
    void printWithCount();
    void printReverse();
    bool isEmpty();
    int getSize();
    int headCount();
};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = NULL;
    tail = NULL;
    size = 0;
}

template<class T>
T& DoublyLinkedList<T>::operator[](int index) {
    if (index >= 1 && index <= size) {
        if (index <= size / 2) {
            Node<T>* aux = head;
            int i = 1; // The list starts with 1
            while (aux != NULL) {
                if (i == index) {
                    return aux->data;
                }
                aux = aux->next;
                i++;
            }
        } else {
            Node<T>* aux = tail;
            int i = size; // The list starts with 1
            while (aux != NULL) {
                if (i == index) {
                    return aux->data;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    throw out_of_range("Invalid position");
}

template<class T>
void DoublyLinkedList<T>::operator=(initializer_list<T> list) {
    if (isEmpty()) {
        for (T i : list) {
            addLast(i);
        }
    } else {
        throw runtime_error("Error: DoublyLinkedList no esta vacia");   
    }
}

template<class T>
void DoublyLinkedList<T>::operator=(DoublyLinkedList<T> list) {
    clear();
    for (int i=1; i<=list.size; i++) {
        addLast(list[i]);
        updateCountAt(i, list.getCount(i));
    }
}

template<class T> //cargamos las ip a la linked list
void DoublyLinkedList<T>::loadData(){
    ifstream bitacora("bitacora2.txt");
    string line, valor;
    char delim = ' ';
    int col;

    while(getline(bitacora,line)){
        stringstream ss(line);
        col = 0;
        while(getline(ss,valor,delim)){
            switch(col){
                case 3:
                    addLast(valor);
                    break;
                default:
                    break;
            }
            col++;
        }
    }
}

template<class T>
void DoublyLinkedList<T>::orderedFile(){
    ofstream ordenada("Ordenada.txt");
    Node<T> *temp = head;
    for(int i = 0; i < size; i++){
        ordenada << temp->data << endl;
        temp = temp->next;
    }
}

template<class T>
void DoublyLinkedList<T>::addFirst(T data) {
    if (!isEmpty()) {
        head->prev = new Node<T>(data, head, NULL); 
        head = head->prev;
    } else {
        head = new Node<T>(data);
        tail = head;
    }
    size++;
}

template<class T>
void DoublyLinkedList<T>::addLast(T data) {
    if (!isEmpty()) {
        tail->next = new Node<T>(data,NULL, tail);
        tail = tail->next;
    } else {
        tail = new Node<T>(data);
        head = tail;
    }
    size++;
}

template<class T>
bool DoublyLinkedList<T>::deleteData(T data) {
    if (!isEmpty()) {
        if (head->data == data) {
            Node<T>* aux = head;
            head = aux->next;
            head->prev = NULL;
            delete aux; // Libera espacio de memoria
            size--;
            if (head == NULL) {
                tail = NULL;
            }
            return true;
        } else {
            if (head->next != NULL) {
                Node<T>* aux = head->next;
                Node<T>* prev = head;
                while (aux != NULL) {
                    if (aux->data == data) {
                        prev->next = aux->next;
                        if (aux->next != NULL) {
                            aux->next->prev = prev;
                        } else {
                            tail = prev;
                        }
                        delete aux;
                        size--;
                        return true;
                    } else {
                        prev = aux;
                        aux = aux->next;
                    }
                }
            }
        }
    }
    return false;
}

template<class T>
bool DoublyLinkedList<T>::deleteAt(int index) {
    if (index >= 1 && index <= size) {
        if (index == 1) {
            Node<T>* aux = head;
            head = aux->next;
            if (head == NULL) {
                tail = NULL;
            } else {
                head->prev = NULL;
            }
            delete aux;
            size--;
            return true;
        } else {
            if (head->next != NULL) {
                Node<T>* aux = head->next;
                Node<T>* prev = head;
                int i = 2;
                while (aux != NULL) {
                    if (i == index) {
                        prev->next = aux->next;
                        if (aux->next != NULL) {
                            aux->next->prev = prev;
                        } else {
                            tail = prev;
                        }
                        delete aux;
                        size--;
                        return true;
                    } else {
                        prev = aux;
                        aux = aux->next;
                    }
                    i++;
                }
            }
        }
    }
    return false;
}

template<class T>
T DoublyLinkedList<T>::getData(int index) {
    if (index >= 1 && index <= size) {
        if (index <= size / 2) {
            Node<T>* aux = head;
            int i = 1; // The list starts with 1
            while (aux != NULL) {
                if (i == index) {
                    return aux->data;
                }
                aux = aux->next;
                i++;
            }
        } else {
            Node<T>* aux = tail;
            int i = size; // The list starts with 1
            while (aux != NULL) {
                if (i == index) {
                    return aux->data;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    throw out_of_range("Invalid position");
}

template<class T>
int DoublyLinkedList<T>::getCount(int index) {
    if (index >= 1 && index <= size) {
        if (index <= size / 2) {
            Node<T>* aux = head;
            int i = 1; // The list starts with 1
            while (aux != NULL) {
                if (i == index) {
                    return aux->count;
                }
                aux = aux->next;
                i++;
            }
        } else {
            Node<T>* aux = tail;
            int i = size; // The list starts with 1
            while (aux != NULL) {
                if (i == index) {
                    return aux->count;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    
    throw out_of_range("Invalid position");
}

template<class T>
Node<T>* DoublyLinkedList<T>::getNode(int index) {
    if (index >= 1 && index <= size) {
        if (index <= size / 2) {
            Node<T>* aux = head;
            int i = 1; // The list starts with 1
            while (aux != NULL) {
                if (i == index) {
                    return aux;
                }
                aux = aux->next;
                i++;
            }
        } else {
            Node<T>* aux = tail;
            int i = size; // The list starts with 1
            while (aux != NULL) {
                if (i == index) {
                    return aux;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    throw out_of_range("Invalid position");
}

template<class T>
void DoublyLinkedList<T>::updateAt(int index, T newData) {
    if (index >= 1 && index <= size) {
        if (index <= size/2) {
            Node<T>* aux = head;
            int i = 1;
            while(aux != NULL) {
                if (i == index) {
                    aux->data = newData;
                    return;
                }
                aux = aux->next;
                i++;
            }
        } else {
            Node<T>* aux = tail;
            int i = size;
            while(aux != NULL) {
                if (i == index) {
                    aux->data = newData;
                    return;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    throw out_of_range("Invalid position");
}

template<class T>
void DoublyLinkedList<T>::addCountAt(int index) {
    if (index >= 1 && index <= size) {
        if (index <= size/2) {
            Node<T>* aux = head;
            int i = 1;
            while(aux != NULL) {
                if (i == index) {
                    aux->count += 1;
                    return;
                }
                aux = aux->next;
                i++;
            }
        } else {
            Node<T>* aux = tail;
            int i = size;
            while(aux != NULL) {
                if (i == index) {
                    aux->count += 1;
                    return;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    throw out_of_range("Invalid position");
}

template<class T>
void DoublyLinkedList<T>::updateCountAt(int index, int newCount) {
    if (index >= 1 && index <= size) {
        if (index <= size/2) {
            Node<T>* aux = head;
            int i = 1;
            while(aux != NULL) {
                if (i == index) {
                    aux->count = newCount;
                    return;
                }
                aux = aux->next;
                i++;
            }
        } else {
            Node<T>* aux = tail;
            int i = size;
            while(aux != NULL) {
                if (i == index) {
                    aux->count = newCount;
                    return;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    throw out_of_range("Invalid position");
}

template<class T>
void DoublyLinkedList<T>::updateData(T data, T newData) {
    Node<T>* aux = head;
    while(aux != NULL) {
        if (aux->data == data) {
            aux->data = newData;
            return;
        }
        aux = aux->next;
    }
    throw out_of_range("Data not found");
}

template<class T>
void DoublyLinkedList<T>::insertAt(int index, T newData) {
    if (index >= 1 && index <= size) {
        if (index == 1) {
            head->prev = new Node<T>(newData,head,NULL);
            head = head->prev;
            size++;
            return;
        } else {
            if (index == size) {
                tail->next = new Node<T>(newData, NULL, tail);
                tail = tail->next;
                size++;
                return;
            } else {
                Node<T>* aux = head->next;
                Node<T>* prev = head;
                int i = 2;
                while(aux->next != NULL) {
                    if (i == index) {
                        prev->next = new Node<T>(newData,aux,prev);
                        size++;
                        return;
                    }
                    prev = aux;
                    aux = aux->next;
                    i++;
                }
            }
        }
    }
    throw out_of_range("Invalid position");
}

template<class T>
void DoublyLinkedList<T>::merge(int ini, int mid, int fin) {
    Queue<T> listL;
    Queue<T> listR;
    int pos,f1,f2,i,j;
    pos = ini;
    f1 = mid - ini + 1;
    f2 = fin - mid;   
    for (i=1;i<=f1;i++) {
        listL.enqueue(getData(ini+i-1));
    }
    for (j=1;j<=f2;j++) {
        listR.enqueue(getData(mid+1+j-1));
    }
    i = 1;
    j = 1;
    while (i<=f1 && j<=f2) {
        if (listL.front()<=listR.front()) {
            updateAt(pos,listL.dequeue());
            i++;
        } else {
            updateAt(pos,listR.dequeue());
            j++;
        }
        pos++;
    }
    while (i<=f1) {
        updateAt(pos,listL.dequeue());
        i++;
        pos++;
    }
    while (j<=f2) {
        updateAt(pos,listR.dequeue());
        j++;
        pos++;
    }
}

template<class T>
void DoublyLinkedList<T>::mergeSort(int ini, int fin) {
    if (ini < fin) {
        int mid = (ini + fin) / 2;
        mergeSort(ini,mid);
        mergeSort(mid+1,fin);

        merge(ini,mid,fin);
    }
}

template<class T>
void DoublyLinkedList<T>::sort() {
    mergeSort(1,size);
}

template<class T>
int DoublyLinkedList<T>::findData(T data) {
    int posI = 1;
    int posF = size;
    int posM = (posI + posF) / 2;
    bool found = false;
    sort();
    while (posI <= posF && !found) {
        if (data < getData(posM)) {
            posF = posM - 1;
        } else {
            if (data > getData(posM)) {
                posI = posM + 1;
            } else {
                if (data == getData(posM)) {
                    found = true;
                }
            }
        }
        posM = (posI + posF) / 2;
    }
    if (found) {
        return posM;
    } else {
        throw runtime_error("Not found in list");
    }
}

template<class T>
void DoublyLinkedList<T>::duplicate() {
    // Node<T>* aux = head;
    // while (aux != NULL) {
    //     aux->next = new Node<T>(aux->data,aux->next);
    //     size++;
    //     aux = aux->next->next;
    // }
}

template<class T>
void DoublyLinkedList<T>::removeDuplicates() {
    // Node<T>* aux = head;
    // DoublyLinkedList<T> list = *this;
    // clear();
    // for (int i=1; i<list.size; i++) {
    //     if (!findData(aux->data)) {
    //         addLast(aux->data);
    //     }
    // }
}

template<class T>
void DoublyLinkedList<T>::print() {
    Node<T>* aux = head;
    for (int i=1; i<=size; i++) {
        cout << aux->data << " ";
        aux = aux->next;
    }
    cout << endl;
}

template<class T>
void DoublyLinkedList<T>::printWithCount() {
    ofstream ordenada("OrdenadaCount.txt");
    Node<T> *temp = head;
    for(int i = 0; i < size; i++){
        ordenada << temp->data << " " << temp->count << endl;
        temp = temp->next;
    }
}

template<class T>
void DoublyLinkedList<T>::printReverse() {
    Node<T>* aux = tail;
    for (int i=size; i>=1; i--) {
        cout << aux->data << " ";
        aux = aux->prev;
    }
    cout << endl;
}

template<class T>
void DoublyLinkedList<T>::clear() {
    int i = 1;
    while (i<=size) {
        Node<T>* aux = head;
        head = aux->next;
        delete aux;
        i++;
    }
    size = 0;
    tail = NULL;
}

template<class T>
bool DoublyLinkedList<T>::isEmpty() {
    return size == 0;
}

template<class T>
int DoublyLinkedList<T>::getSize() {
    return size;
}

template<class T>
int DoublyLinkedList<T>::headCount(){
    return head->count;
}
#endif