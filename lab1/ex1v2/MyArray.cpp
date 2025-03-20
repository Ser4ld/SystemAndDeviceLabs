#include "MyArray.h"
#include <iostream>
#include <algorithm>

using namespace std;


MyArray::MyArray(int size) : size(size){
    vet= (float*)malloc(size*sizeof(float));
    if(vet==nullptr){
        cerr << "Memory allocation error"<< endl;
        exit(EXIT_FAILURE);
    }
}
MyArray::~MyArray(){
    free(vet);
}
void MyArray::generate(){
    float value=0;
    for(int i=0;i<size; i++){
        cout << "Enter value :";
        cin >> value;
        vet[i]=value;
    }
}
void MyArray::increasingsort(){
    sort(vet, vet+size);
}
void MyArray::print(){
    cout << "Array :" ;
    for(int i=0;i<size;i++){
        cout << vet[i] << " " ;
    }
    cout << endl;
}