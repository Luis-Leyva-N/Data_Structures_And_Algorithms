#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "Queue.h"

class DoublyLinkedList{
    public:
        DoublyLinkedList();
        bool isEmpty();
        void loadData();
        int getSize();
        Node* getNode(int pos);
        void updateAt(int pos, Node temp);
        void merge(int low, int mid, int high);
        void mergeSort(int low, int high);
        void sort();
        void orderedFile();
        long long int valorBusqueda();
        int busquedaBinaria(long long int x);
        void printSearch(int pos1, int pos2);
    private:
        vector<long long int> busqueda;
        Node *head;
        Node *tail;
        int size;
};

DoublyLinkedList::DoublyLinkedList(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}

bool DoublyLinkedList::isEmpty(){
    return size == 0;
}

//Cargamos los datos
void DoublyLinkedList::loadData(){
    ifstream bitacora("Bitacora.txt");
    string line, valor, valortiempo;
    char delim = ' ';
    int col,col2;

    Node *temp;
    head = new Node;
    temp = head;

    while(getline(bitacora,line)){
        stringstream ss(line);
        col = 0;
        col2 = 0;
        while(getline(ss,valor,delim)){
            stringstream ss2(valor);
            switch(col){
                case 0: 
                    temp->mes = valor;
                    if(valor == "Jun"){
                        temp->ordenFecha = 600000000;
                    } else if(valor == "Jul"){
                        temp->ordenFecha = 700000000;
                    } else if(valor == "Aug"){
                        temp->ordenFecha = 800000000;
                    } else if(valor == "Sep"){
                        temp->ordenFecha = 900000000;
                    } else if(valor == "Oct"){
                        temp->ordenFecha = 1000000000;
                    }
                    break;
                case 1: 
                    temp->dia = stoi(valor);
                    temp->ordenFecha += stoi(valor) * 1000000;
                    break;
                case 2: 
                    temp->tiempo = valor;
                    while(getline(ss2,valortiempo,':')){
                        switch(col2){
                            case 0:
                                temp->hora = stoi(valortiempo);
                                temp->ordenFecha += stoi(valortiempo) * 10000;
                                break;
                            case 1:
                                temp->min = stoi(valortiempo);
                                temp->ordenFecha += stoi(valortiempo) * 100;
                                break;
                            case 2:
                                temp->seg = stoi(valortiempo);
                                temp->ordenFecha += stoi(valortiempo);
                                break;
                        }
                        col2++;
                    }
                    break;
                case 3: 
                    temp->ip = valor;
                    break;
                default:
                    temp->event += valor + " "; 
            }
            col++;
        }
        temp->next = new Node;
        tail = temp->next;
        tail->prev = temp;
        temp = tail;
        size++;
    }
    tail = temp->prev;
    delete temp;
}

int DoublyLinkedList::getSize(){
    return size;
}
//Regresamos un apuntador de nodo, esta funcion sirve para el ordenamiento con los queues
Node* DoublyLinkedList::getNode(int pos){
    if(!isEmpty() && pos >= 1 && pos <= size){
        Node* aux = head;
        int posaux = 1;
        while(aux != nullptr){
            if(posaux == pos){
                return aux;
            } else {
                aux = aux->next;
                posaux++;
            }
        }
    }

    return nullptr;
}

//En esta funcion actualizamos los valores con respecto a la funcion de ordenamiento
void DoublyLinkedList::updateAt(int pos, Node temp){
    if(!isEmpty() && pos >= 1 && pos <= size){
        Node *aux = head;
        int posaux = 1;
        while(aux != nullptr){
            if(posaux == pos){
                aux->mes = temp.mes;
                aux->dia = temp.dia;
                aux->seg = temp.seg;
                aux->min = temp.min;
                aux->hora = temp.hora;
                aux->tiempo = temp.tiempo;
                aux->ip = temp.ip;
                aux->event = temp.event;
                aux->ordenFecha = temp.ordenFecha;
                break;
            } else {
                aux = aux->next;
                posaux++;
            }
        }
        return;
    }
}


//ordena la lista, utilizando merge
//O(logn)
void DoublyLinkedList::merge(int low, int mid, int high){
    Queue left;
    Queue right;
    Node temp;
    int i,j,pos,size1,size2;

    pos = low;
    size1 = mid - low + 1;
    size2 = high - mid;

    for(i=1;i<=size1;i++){
        temp = *getNode(low+i-1);
        left.enqueue(temp);
    }

    for(j=1;j<=size2;j++){
        temp = *getNode(mid+1+j-1);
        right.enqueue(temp);
    }

    i = 1;
    j = 1;

    while(i<=size1 && j <= size2){
        if(left.getData()<=right.getData()){
            temp = *left.getNode();
            updateAt(pos,temp);
            left.dequeue();
            i++;
        } else {
            temp = *right.getNode();
            updateAt(pos,temp);
            right.dequeue();
            j++;
        }
        pos++;
    }

    while(i<=size1){
        temp = *left.getNode();
        updateAt(pos,temp);
        left.dequeue();
        i++;
        pos++;
    }

    while(i<=size2){
        temp = *right.getNode();
        updateAt(pos,temp);
        right.dequeue();
        j++;
        pos++;
    }
}

void DoublyLinkedList::mergeSort(int low, int high){
    if(low < high){
        int mid = (low + high) / 2;
        mergeSort(low,mid);
        mergeSort(mid+1,high);

        merge(low,mid,high);

    }
}

void DoublyLinkedList::sort(){
    mergeSort(1,size);
}

//Imprimimos la lista ordenada en el nuevo archivo
void DoublyLinkedList::orderedFile(){
    ofstream ordenada("Bitacora_Ordenada.txt");
    Node *temp = head;

    for(int i = 0; i < size; i++){
        ordenada << temp->mes << " ";
        ordenada << temp->dia << " ";
        ordenada << temp->tiempo << " ";
        ordenada << temp->ip << " ";
        ordenada << temp->event << endl;
        busqueda.push_back(temp->ordenFecha);
        temp = temp->next;
    }
}

//Pregunta al usuario el rango de datos para la busqueda
long long int DoublyLinkedList::valorBusqueda(){
    int dia, hora, min, seg, mes, init, final;
    long long int x;
    cout << "Eliga mes: " << endl;
    cout << "1) Jun" << endl << "2) Jul" << endl << "3) Aug" << endl << "4) Sep" << endl << "5) Oct" << endl;
    cin >> mes;
    while(mes > 5 || mes < 1){
        cout << "Eliga opcion valida" << endl;
        cin >> mes;
    }
    switch(mes){
        case 1:
            x += 600000000;
            break;
        case 2:
            x += 700000000;
            break;
        case 3:
            x += 800000000;
            break;
        case 4:
            x += 900000000;
            break;
        case 5:
            x += 1000000000;
            break;
    }
    cout << "Eliga un dia:" << endl;
    cin >> dia;
    while(dia < 1 || dia > 30){
        cout << "Eliga opcion valida" << endl;
        cin >> dia;
    }
    x += dia * 1000000;
    cout << "Eliga una hora entre 0 y 23:" << endl;
    cin >> hora;
    while(hora < 0 || hora > 23){
        cout << "Eliga opcion valida" << endl;
        cin >> hora;
    }
    x += hora * 10000;

    cout << "Eliga un minuto entre 0 y 59:" << endl;
    cin >> min;
    while(min < 0 || min > 59){
        cout << "Eliga opcion valida" << endl;
        cin >> min;
    }
    x += min * 100;

    cout << "Eliga un segundo entre 0 y 59:" << endl;
    cin >> seg;
    while(seg < 0 || seg > 59){
        cout << "Eliga opcion valida" << endl;
        cin >> seg;
    }
    x += seg;

    return x;
}

//Busca las posiciiones de los numeros solicitados
int DoublyLinkedList::busquedaBinaria(long long int x){
    int min, max, med;
    min = 0;
    max = busqueda.size();

    if(x < busqueda[0]) {
        return 1;
    }
    if(x > busqueda[max-1]) {
        return max;
    }
    
    while(min < max){
        med = (min + (max - 1)) / 2;
        if(x < busqueda[med]){
            max = med - 1;
        } else if(x > busqueda[med]){
            min = med + 1;
        } else {
            return med+1;
        }
    }

    if((busqueda[min] - x) < (x - busqueda[max])){
        return min+1;
    } else {
        return max+1;
    }

    return med+1;
}

//Imprime el resultado de la busqueda
void DoublyLinkedList::printSearch(int pos1, int pos2){
    Node *temp = head;
    cout << endl;
    for(int i = 1; i <= size; i++){
        if(i >= pos1 && i <= pos2){
            cout << temp->mes << " ";
            cout << temp->dia << " ";
            cout << temp->tiempo << " ";
            cout << temp->ip << " ";
            cout << temp->event << endl;
        }
        temp = temp->next;
    }
}

#endif