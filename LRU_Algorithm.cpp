#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stack>
#include <iostream>
using namespace std;

//Variables Globales
stack <int> pila;
int memoria[20];

void* genRandNum(void*){

    srand(time(NULL));

    for(int i=0; i<5; i++){

        int num = rand() % (101 - 1);       //Generar numeros aleatorios entre 0-100
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
    int espaciosAtras = 0;

    for(int i=0;i<length; i++){
        
        if(rPagina == memoria[i]){
            //El numero ya esta en el arreglo
        }else if(checkMem(memoria)){         //Si el arreglo esta lleno

            //Buscar cual reemplazar
            //1. Cual fue la referencia mas ultima
            for(int atras=0;atras<20;atras++){

                

            }


        }else{
            
            memoria[i] = rPagina;
            fallos++;

        }

    }


}

void showStack(stack <int> s){

    while(!s.empty()){

        cout<<'\t'<<s.top();
        s.pop();

    }

    cout<<'\n';

}

int main(){

    pthread_t thread1, thread2;
    int iret1, iret2;

    //Creamos hilos independientes
    iret1 = pthread_create(&thread1, NULL, genRandNum, NULL);
    iret2 = pthread_create(&thread2, NULL, getReference, NULL);

    pthread_join(thread1, NULL);

    cout<<"The stack is: ";
    showStack(pila);

    pthread_exit(NULL);    
    return 0;

}