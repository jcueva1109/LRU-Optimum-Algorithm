#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

//Variables globales
int memoria[20];
vector<int> ingresar;
int fallos=0;
int hit=0;
int cual=0;

struct op{
    int page;
    int next;
    int pos;
};

void* genRandNum(void*){

    srand(time(NULL));
    
    //El ciclo genera n cantidad de referencias
    for(int i=0; i<80; i++){
        int num = rand() % (101 - 1); //Generar numeros aleatorios entre 0-100
        // cout<<"Numero de referencia de pagina: "<<num<<endl;
        ingresar.push_back(num);
    }
}

bool rep(int x){
    int num=1;
    for (int i = 0; i < 20; i++)
    {
        if(memoria[i]==x){
            num++;
        }
    }
    if(num==1){
        return false;
    }else{
        return true;
    }
}

int change(int index){
    if(index==ingresar.size()-1){
        return ingresar.size()-1;
    }
    vector<op> ver;
    for (int i = 0; i < 20; i++)
    {
        op temp;
        temp.next=0;
        temp.page=memoria[i];
        temp.pos=i;
        ver.push_back(temp);
    }
    for (int i = 0; i < ver.size(); i++)
    {
        op actual= ver[i];
        for (int j = index+1; j < ingresar.size(); j++)
        {
            if(ingresar[j]==actual.page){
                if(actual.next<(j-actual.next)){
                    actual.next=j-actual.next;
                    // cout<<"hubo\n";
                }
            }
        }
    }
    op tmp;
    tmp.next=0;
    for (int i = 0; i < ver.size(); i++)
    {   
        if(ver[i].next==0){
            tmp=ver[i];
            break;
        }
        else if(tmp.next<ver[i].next){
            tmp=ver[i];
        }
    }
    return tmp.pos;
}

void* opr(void*){
    int newNum= 0;
    for (int j = 0; j < ingresar.size(); j++)
    {
        newNum= ingresar[j];
        if(memoria[19]==NULL){
            for (int i = 0; i < 20; i++)
            {
                if(memoria[i]==NULL){
                    if(rep(newNum)){
                        cout<<"h";
                        hit=hit+1;
                    }else{
                        fallos++;
                        memoria[i]=newNum;
                        break;
                    }
                }
            }
        }else{
            if(rep(newNum)){
                cout<<"h";
                hit=hit+1;
            }else{
                //llamamos cual es el que vamos a cambiar y se cambia
                fallos++;
                int cual= change(j);
                memoria[cual]=ingresar[j];
            }
        }
    }
    // for (int i = 0; i < 20; i++)
    // {
    //     cout<<i<<" "<<memoria[i]<<endl;
    // }
    cout<<"hits "<<hit<<" fallos "<<fallos<<" \nnumeros\n";
    for (int i = 0; i < ingresar.size(); i++)
    {
        cout<<ingresar[i]<<"-";
    }
    cout<<endl;
    for (int i = 0; i < 20; i++)
    {
        cout<<"mem "<<i+1<<" :"<<memoria[i]<<endl;
    }
    
}

int main(){
    pthread_t thread1, thread2;
    int iret1, iret2;
    iret1 = pthread_create(&thread1, NULL, genRandNum, NULL);
    pthread_join(thread1, NULL);
    iret2 = pthread_create(&thread2, NULL, opr, NULL);
    pthread_join(thread2, NULL);
    
    pthread_exit(NULL);
    return 0;
}
