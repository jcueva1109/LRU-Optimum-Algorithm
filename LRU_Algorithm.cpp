#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <queue> 
#include <iostream>
using namespace std;

struct LRU {

    int referencia;
    int cReferenciado;

};

//Variables Globales
vector <LRU> checkR;
queue <int> cola;
int fallosG;
int memoria[20];

void* genRandNum(void*) {

    srand(time(NULL));

    //El ciclo genera n cantidad de referencias
    //for (int i = 0; i < 20; i++) {

        int num = rand() % (101 - 1);       //Generar numeros aleatorios entre 1-100
        cout << "Numero de referencia de pagina: " << num << endl;
        cola.push(num);

    //}

    return NULL;

}

bool checkMem(int arreglo[]) {

    return memoria[19] != NULL ? true : false;

}

bool checkRef(int ref, int arreglo[]) {

    bool esta = false;

    for (int i = 0; i < 5; i++) {

        if (memoria[i] == ref) {  //Si la referencia ya esta en memoria
            return true;
        }

    }

    return esta;

}

int nextPos(int arreglo[]) {

    int i;

    for (i = 0; i < 20; i++) {

        if (arreglo[i] == NULL) {
            return i;
        }

    }

    return -1;

}

void* updateRef(int ref) {

    int veces = 0;

    for (int i = 0; i < checkR.size(); i++) {

        if (checkR[i].referencia == ref) {
            veces++;

        }

    }

    for (int i = 0; i < checkR.size(); i++) {

        if (checkR[i].referencia == ref) {
            checkR[i].cReferenciado = veces;
        }
    }

    return NULL;

}

int getReferenced(int ref) {

    for (int i = 0; i < checkR.size(); i++) {

        if (checkR[i].referencia == ref) {
            return checkR[i].cReferenciado;
        }
    }

}

void* getReference(void*) {

    int fallos = 0;

    int ref = cola.front();
    struct LRU toRefer;
    toRefer.referencia = ref;
    cola.pop();

    if (checkRef(ref, memoria))
    {

        cout<<"HIT!"<<endl;
        
    }

    else if (checkMem(memoria)) { //Si el arreglo esta lleno

        int numero = getReferenced(memoria[0]);
        int actual = memoria[0];
        for (int j = 0; j < 20; j++)
        {
            bool tochange = false;
            for (int i = checkR.size() - 1; i > -1; i--)
            {
                
                if (checkRef(checkR[i].referencia, memoria)) {
                    if (numero>checkR[i].cReferenciado && actual != ref) {
                        numero = getReferenced(memoria[j]);
                        actual = memoria[j];
                        tochange = true;
                        break;
                    }
                }
            }
        }

        fallosG++;
        
        for (int p = 0; p < 20; p++) {
            if (memoria[p] == actual) {
                cout << "Se reemplazo: " << memoria[p] << " por: " << ref << endl;
            }
        }

    }
    else
    {

        //La referencia no esta en memoria, la agregamos y incrementamos los fallos
        int i = nextPos(memoria);
        memoria[i] = ref;
        fallosG++;
        //cout << "La referencia es: " << ref << " y esta en la posicion " << i << endl;
    }

    //Meto al vector, esto es auxiliar para saber cuales son mis referencias ya ingresadas. 
    checkR.push_back(toRefer);
    updateRef(ref);
    return NULL;
}

void* printFallos(void*) {

    cout << "Fallos: " << fallosG << endl;
    return NULL;
}

int main() {

    pthread_t thread1, thread2, thread3;
    int iret1, iret2, iret3;

    while (true){ 
    
        iret1 = pthread_create(&thread1, NULL, genRandNum, (void*)NULL);
            pthread_join(thread1, NULL);
            cout<<endl;
        iret2 = pthread_create(&thread2, NULL, getReference, (void*) NULL);
            pthread_join(thread2, NULL);
            sleep(3);
            cout<<endl;
        iret3 = pthread_create(&thread3, NULL, printFallos, (void*) NULL);
            pthread_join(thread3, NULL);
            sleep(10);
            cout<<endl;

    }

    pthread_exit(NULL);
    return 0;

}