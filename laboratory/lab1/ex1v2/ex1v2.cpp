#include <iostream>
#include "MyArray.h"

using namespace std;

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