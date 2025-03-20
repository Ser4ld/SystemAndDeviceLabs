#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <iterator>

using namespace std;

class Stack{
    private:
    deque<string> v;
    int size;
    public:
    Stack(){

    }
    ~Stack(){
        v.clear();
    }
    void push(string str){
        v.push_back(str);
    }

    void pop(){
        v.pop_back();
    }

    void visit(){
        deque<string>::iterator it;
        for(it=v.begin();it!=v.end(); ++it){
            cout << *it << " ";
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
    s.push("AAA");
    s.push("BBB");
    s.push("CCC");
    cout << s.empty() << endl;
    cout << s.getSize() << endl;
    s.visit();
    s.pop();
    s.visit();
    return EXIT_SUCCESS;
}