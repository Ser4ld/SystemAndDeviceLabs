#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Stack{
    private:
    vector<int> v;
    int size;
    public:
    Stack(){

    }
    ~Stack(){
        v.clear();
    }
    void push(int num){
        v.push_back(num);
    }

    void pop(){
        v.pop_back();
    }

    void visit(){
        for(int i=0;i<v.size();i++){
            cout << v[i] << " ";
        }
        cout << endl;
    }

    int getSize(){
        return v.size();
    }

    bool empty(){
        return v.empty();
    }
};

int main(int argc, char **argv){
    Stack s;
    cout << s.empty() << endl;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << s.empty() << endl;
    cout << s.getSize() << endl;
    s.visit();
    s.pop();
    s.visit();
    return EXIT_SUCCESS;
}