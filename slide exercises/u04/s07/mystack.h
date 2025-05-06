#ifndef MYSTACK_H
#define MYSTACK_H


#include <vector>
#include <stdexcept> //libreria che contiene eccezzioni predefinite, ovvero classi per gestire errori a runtime. Nel nostro caso le funzioni top() e pop() potrebbero lanciare un errore se lo stack è vuoto, quindi usiamo std::out_of_range per gestire questa situazione.

template <class T>
class MyStack {
    private: 
    std::vector<T> stack; // usiamo un vector per implementare lo stack

    public: 
        void push(const T &element);
        void pop();
        T top() const; // usiamo const per indicare che non modifichiamo lo stack
        bool isEmpty() const; // usiamo const per indicare che non modifichiamo lo stack
};

template <class T>
void MyStack<T>::push(const T &element) {
    stack.push_back(element); // aggiungiamo l'elemento alla fine del vector
}

template <class T>
void MyStack<T>::pop() {
    if (stack.empty()){
        throw std::out_of_range("Stack is empty"); // lanciamo un'eccezione se lo stack è vuoto
    }
    stack.pop_back(); // rimuoviamo l'elemento alla fine del vector  
}

template <class T>
T MyStack<T>::top() const {
    if (stack.empty()){
        throw std::out_of_range("Stack is empty"); // lanciamo un'eccezione se lo stack è vuoto
    }
    return stack.back(); // restituiamo l'elemento alla fine del vector
}

template <class T>
bool MyStack<T>::isEmpty() const {
    return stack.empty(); // restituiamo true se lo stack è vuoto, false altrimenti
}


#endif // MYSTACK_H