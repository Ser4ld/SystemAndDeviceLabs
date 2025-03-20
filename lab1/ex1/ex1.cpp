#include <iostream>
#include <algorithm>
using namespace std;

class MyArray{
    private:
        float *vet;
        int size;
    public:
    MyArray(int size) : size(size){
        vet= (float*)malloc(size*sizeof(float));
        if(vet==nullptr){
            cerr << "Memory allocation error"<< endl;
            exit(EXIT_FAILURE);
        }
    }
    ~MyArray(){
        free(vet);
    }
    void generate(){
        float value=0;
        for(int i=0;i<size; i++){
            cout << "Enter value :";
            cin >> value;
            vet[i]=value;
        }
    }
    void increasingsort(){
        sort(vet, vet+size);
    }
    void print(){
        cout << "Array :" ;
        for(int i=0;i<size;i++){
            cout << vet[i] << " " ;
        }
        cout << endl;
    }

};

int main(){
    int n;
    cout << "Enter the dimension: " ;
    cin >> n;
    MyArray array(n);
    array.generate();
    array.increasingsort();
    array.print();
    return 0;
}