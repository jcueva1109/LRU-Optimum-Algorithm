#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <queue> 
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

void genRandNum(void*){

    srand(time(NULL));

    //El ciclo genera n cantidad de referencias
    for(int i=0; i<5; i++){

        int num = rand() % 5 + 1;       //Generar numeros aleatorios entre 1-100
        cout<<"Numero de referencia de pagina: "<<num<<endl;
		cola.push(num);
        
	}
}

bool checkMem(int arreglo[]){

    return memoria[19]!=NULL?true : false;

}

bool checkRef(int ref, int arreglo[]){

    bool esta = false;

    for(int i=0;i<20;i++){

        if(memoria[i] == ref){  //Si la referencia ya esta en memoria
            return true;
        }

    }

    return esta;

}

int nextPos(int arreglo[]){

    int i;

    for(i=0;i<20;i++){

        if(arreglo[i] == NULL){
            return i;
        }

    }

    return -1;

}

void updateRef(int ref){

	int veces = 0;

	for(int i=0;i<checkR.size();i++){

        if(checkR[i].referencia==ref){
                veces++;
            
        }

    }

    for(int i=0;i<checkR.size();i++){

        if(checkR[i].referencia==ref){
                
            checkR[i].cReferenciado = veces;
		}
	}




}

int getReferenced(int ref){

    

    for(int i=0; i<checkR.size(); i++){

        if(checkR[i].referencia == ref){
			return checkR[i].cReferenciado;
		}
	}

    

}

void* getReference(void *){

	//cout<<"Entramos al hilo 2..."<<endl;
    //cout<<"Entramos al hilo 2..."<<endl;
    int fallos = 0;
	
    int ref = cola.front();
	struct LRU toRefer;
	toRefer.referencia = ref;
	cola.pop();

	//if referencia == memoria[i]
	if (checkRef(ref, memoria))
	{

		//El numero ya esta en el arreglo

		cout << "ya esta" << endl;
		}

		else if (checkMem(memoria)){ //Si el arreglo esta lleno

			cout << "lleno" << endl;
			// //Buscar cual reemplazar
			// //El menos recientemente usado es el que esta en la ultima posicion del vector
			int numero=0;
			int actual = memoria[0];
			for (int j = 0; j < 5; j++)
			{
                
				for (int i = checkR.size() - 1; i > -1; i--)
				{
                    if(actual<)
				}
			}
		}
		else
		{

			//La referencia no esta en memoria, la agregamos y incrementamos los fallos
            int i = nextPos(memoria);
            memoria[i] = ref;
            fallosG++;
            cout<<"La referencia es: "<<ref<<" y esta en la posicion "<<i<<endl;
		}

        //Meto al vector, esto es auxiliar para saber cuales son mis referencias ya ingresadas. 
        checkR.push_back(toRefer);
        updateRef(ref);
}

void* printFallos(void*){

    cout<<"Fallos: "<<fallosG<<endl;

}

// int main(){

//     pthread_t thread1, thread2, thread3;
//     int iret1, iret2, iret3;

//     //Creamos hilos independientes
//     iret1 = pthread_create(&thread1, NULL, genRandNum, (void*) NULL);
//     iret1 = pthread_create(&thread1, NULL, getReference, (void*) NULL);

//     pthread_join(thread1, NULL);
//     pthread_join(thread1, NULL);
//     usleep(30000);   

//     iret1 = pthread_create(&thread1, NULL, printFallos, (void*) NULL);

//     pthread_join(thread1, NULL);
//     usleep(100000);                 //Hilo 3 espera 10 segundos

//     pthread_exit(NULL);    
//     return 0;

// }

int main(){

    cout<<"Generando referencias..."<<endl;
    genRandNum(NULL);
    cout<<"Referencias generadas..."<<endl;
    

    while(!cola.empty()){
        getReference(NULL);
    }
    
    printFallos(NULL);
    
    return 0;

}