#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

//Estrcutura de datos para las entradas
struct log{
    string mes;
    int dia, seg, min, hora;
    string tiempo;
    string ip;
    string event;
    long long int ordenFecha;
};

//Se usa list preordenada
//Orden O(n)
int BusquedaBinaria(vector<log*> &list, long long int x){
    int min, max, med;
    min = 0;
    max = list.size();

    if(x < list[0]->ordenFecha) {
        return 0;
    }
    if(x > list[max-1]->ordenFecha) {
        return max-1;
    }
    
    while(min < max){
        med = (min + (max - 1)) / 2;
        if(x < list[med]->ordenFecha){
            max = med - 1;
        } else if(x > list[med]->ordenFecha){
            min = med + 1;
        } else {
            return med;
        }
    }

    if((list[min]->ordenFecha - x) < (x - list[max]->ordenFecha)){
        return min;
    } else {
        return max;
    }

    return med;
}

//O(nlogn) Recursivo. Funcion para el punto de referencia
int rebote(vector<log*> &list, int low, int high) {  
    long long int punto = list[high]->ordenFecha;//se modifico el algoritmo ligeramente para cumplir con los requisitos
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++){   
        if (list[j]->ordenFecha < punto){  
            i++;
            swap(list[i], list[j]); 
        }  
    }  
    swap(list[i + 1], list[high]);  
    return (i + 1);  
}  

void quickSort(vector<log*> &list, int low, int high){  
    if (low < high)  
    {  
        int reb = rebote(list,low,high);  
  
        quickSort(list,low,reb - 1);  
        quickSort(list,reb + 1,high);  
    }  
}

int main(){
    vector<log*> logs;
    ifstream bitacora("Bitacora.txt");
    ofstream ordenada("Bitacora_Ordenada.txt");
    string line, valor, valortiempo;
    char delim = ' ';
    int col,col2;
    log* temp;

    //Leemos los datos
    while(getline(bitacora,line)){
        stringstream ss(line);
        col = 0;
        col2 = 0;
        temp = new log();
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
                    break;
                case 2: 
                    temp->tiempo = valor;
                    while(getline(ss2,valortiempo,':')){
                        switch(col2){
                            case 0:
                                temp->hora = stoi(valortiempo);
                                break;
                            case 1:
                                temp->min = stoi(valortiempo);
                                break;
                            case 2:
                                temp->seg = stoi(valortiempo);
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
        logs.push_back(temp);
    }
    //Variable para ordenar las estructuras
    for(int i = 0; i < logs.size(); i++){
        logs[i] -> ordenFecha += logs[i]->seg + logs[i]->min * 100 + logs[i]->hora * 10000 + logs[i]->dia * 1000000;
    }
    
    quickSort(logs,0,logs.size()-1);

    //Pasar datos ordenados al nuevo archivo
    for(int i = 0; i < logs.size(); i++){
        ordenada << logs[i] -> ordenFecha << " ";
        ordenada << logs[i] -> mes << " ";
        ordenada << logs[i] -> dia << " ";
        ordenada << logs[i] -> tiempo << " ";
        ordenada << logs[i] -> ip << " ";
        ordenada << logs[i] -> event << endl;
    }

    int a = -1;
    int dia, hora, mes, init, final;
    long long int x;

    while(a != 0){
        x = 0;
        cout << "1) Busqueda de registros" << endl << "0) Salir" << endl;
        cin >> a;
        switch(a){
            case 0:
                break;
            case 1:
                cout << "Rango Inicial" << endl;
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
                init = BusquedaBinaria(logs,x);
                
                cout << "Rango Final" << endl;
                x = 0;
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
                final = BusquedaBinaria(logs,x);

                for(int i = init; i <= final;i++){
                    cout << logs[i] -> mes << " ";
                    cout << logs[i] -> dia << " ";
                    cout << logs[i] -> tiempo << " ";
                    cout << logs[i] -> ip << " ";
                    cout << logs[i] -> event << endl;
                }
                break;
            default:
                cout << "Eliga opcion valida" << endl;
                break;
        }
    }


    return 0;
}