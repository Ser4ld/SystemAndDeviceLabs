#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <iterator>
#include <vector>

using namespace std;

template <class T>
class Stack{
    private:
    deque<T> v;

    public:

    void push(const T &element){
        v.push_front(element);
    }

    void pop(){
        v.pop_front();
    }

    void visit(){
        cout<<"Coda"<<endl;
        for(auto it=v.begin();it!=v.end(); ++it){
            cout << *it << " ";
        }
        cout << endl;
    }

    void getSize(){
        cout<< "Size della coda: "<< v.size()<<endl;
    }

    void empty(){
        if(v.empty())
            cout<< "la coda e vuota"<<endl;
        else
            cout<< "Il coda e piena "<<endl;
        }
};

template <class T>
class StackVector{
    private:
    vector<T> vec;
    public:
    void push(const T &element){
        vec.push_back(element);
    }

    void pop(){
        vec.pop_back();
    }

    void visit(){
        cout<<"Vettore"<<endl;
        for(auto it= vec.begin(); it!= vec.end(); ++it){
            cout<<*it<<endl;
        }
        cout << endl;
    }

    void getSize(){
        cout<< "Size: "<< vec.size()<<endl;
    }

    void empty(){
        if(vec.empty())
            cout<< "il vettore e vuoto"<<endl;
        else
            cout<< "Il vettore e pieno "<<endl;
    }
};

int main(int argc, char **argv){

    Stack<int> s;
    StackVector<int> v;
    bool flag=true;
    int choice;
    int val;

    while (flag)
    {
        cout<<"Fai una scelta da 0 a 5"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 0:
            cout<<"Inserisci un valore: ";
            cin>>val;
            s.push(val);
            v.push(val);
            break;
        case 1:
            s.pop();
            v.pop();
            break;
        case 2:
            s.visit();
            v.visit();
            break;
        case 3:
            s.getSize();
            v.getSize();
            break;
        case 4:
            s.empty();
            v.empty();
            break;
        case 5: 
            flag=false;
            break;
        default:
            
            break;
        }
    }
    return 0;

}