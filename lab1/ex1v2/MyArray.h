#ifndef MYARRAY_H
#define MYARRAY_H


class MyArray{
    private:
        float *vet;
        int size;
    public:
    MyArray(int size);
    ~MyArray();
    void generate();
    void increasingsort();
    void print();
};

#endif