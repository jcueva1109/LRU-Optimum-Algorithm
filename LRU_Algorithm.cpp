#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stack>
#include <vector>
#include <unistd.h>
#include <iostream>
using namespace std;

//Variables Globales
stack <int> pila;
vector <int> checkR;

int fallosG;
int memoria[20];

void* genRandNum(void*){

    srand(time(NULL));

    //El ciclo genera n cantidad de referencias
    for(int i=0; i<5; i++){

        int num = rand() % (101 - 1);       //Generar numeros aleatorios entre 1-100
        cout<<"Numero de referencia de pagina: "<<num<<endl;
        pila.push(num);



    }
    
}

bool checkMem(int arreglo[]){

    int length = (sizeof(arreglo)/ sizeof(*arreglo));
    bool lleno = false;

    //Recorrer arreglo y saber si esta lleno
    for(int i=0;i<length;i++){
        if(memoria[i] == NULL){
            lleno = false;
        }else{
            lleno = true;
        }

    }

    return lleno;

}

void* getReference(void*){

    int rPagina = pila.top();     //Agarro el primero que esta en la pila
    pila.pop();             //y luego lo saco

    int length = (sizeof(memoria)/ sizeof(*memoria));
    int fallos = 0;

    for(int i=0;i<length; i++){
        
        if(rPagina == memoria[i]){
            
            //El numero ya esta en el arreglo

        }else if(checkMem(memoria)){         //Si el arreglo esta lleno

            //Buscar cual reemplazar
            //El menos recientemente usado es el que esta en la ultima posicion del vector 
            for(int j=0;j<20;j++){

                if(memoria[i] == checkR.back()){

                    memoria[i] = rPagina;
                    fallos++;

                }

            }


        }else{
            
            //La referencia no esta en memoria, la agregamos y incrementamos los fallos
            memoria[i] = rPagina;
            checkR.push_back(rPagina);  //Meto al vector, esto es auxiliar para saber cuales son mis referencias ya ingresadas. 
            fallos++;

        }

    }

    fallosG = fallos;

}

void* printFallos(void*){

    cout<<"Fallos: "<<fallosG<<endl;

}

//Mostrar contenido de la pila
void showStack(stack <int> s){

    while(!s.empty()){

        cout<<'\t'<<s.top();
        s.pop();

    }

    cout<<'\n';

}

int main(){

    pthread_t thread1, thread2, thread3;
    int iret1, iret2, iret3;

    //Creamos hilos independientes
    iret1 = pthread_create(&thread1, NULL, genRandNum, NULL);
    iret2 = pthread_create(&thread2, NULL, getReference, NULL);
    iret2 = pthread_create(&thread3, NULL, printFallos, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    usleep(30000);                  //Hilo 2 espera 3 segundos
    pthread_join(thread3, NULL);
    usleep(100000);                 //Hilo 3 espera 10 segundos

    pthread_exit(NULL);    
    return 0;

}