#include "mystack.h"
#include <iostream>
#include <string>
using namespace std;

int main() {


    MyStack<int> intStack; // creiamo uno stack di interi
    intStack.push(1);
    intStack.push(2);

    cout<<"top"<< intStack.top()<<endl; // stampiamo l'elemento in cima allo stack
    intStack.pop(); // rimuoviamo l'elemento in cima allo stack
    cout<<"top after pop"<< intStack.top()<<endl; // stampiamo l'elemento in cima allo stack dopo aver rimosso l'elemento"


    MyStack<string> stringStack;
    int choice;
   
    do {
        cout<<"che operazione vuoi eseguire? 1- push, 2- pop, 3- top, 4- empty, 5 -exit"<<endl;
        
        cin>>choice; // chiediamo all'utente di scegliere un'operazione
  
        switch (choice)
        {
        //Nel case 1:, le graffe {} sono messe apposta per racchiudere string element, altrimenti il compilatore 
        //può lamentarsi che una variabile viene "inizializzata in modo non sicuro nel switch".
        case 1:{
            cout<<"inserisci un elemento"<<endl;
            string element;
            cin>>element; // chiediamo all'utente di inserire un elemento
            stringStack.push(element); // aggiungiamo l'elemento allo stack
            break;
        }
        
        case 2: 
            cout<<"pop"<<endl;
            stringStack.pop(); // rimuoviamo l'elemento in cima allo stack
            break;
        
        case 3:
            cout<<"top: "<< stringStack.top()<<endl; // stampiamo l'elemento in cima allo stack
            break;
        
        case 4:  
            if (stringStack.isEmpty()) { // controlliamo se lo stack è vuoto
                cout<<"lo stack e vuoto"<<endl;
            } else {
                cout<<"lo stack non e vuoto"<<endl;
            }
            break;
        
        case 5:
            cout<<"exit"<<endl;
            break;
        
        default:
            break;
        }


    }while (choice != 5); // finchè l'utente non sceglie di uscire
    
    return 0; 
}