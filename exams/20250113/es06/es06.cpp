#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <thread>
#include <random>
#include <chrono>



int randomNum(){

    // Generatore di numeri casuali
    static std::random_device rd;  // Dispositivo per generare numeri casuali
    static std::mt19937 gen(rd());  // Mersenne Twister per la generazione
    return std::uniform_int_distribution<int>(1, 10) (gen);  // Distribuzione per numeri casuali tra 1 e 1000
}

void produce_h1(std::promise<char>& p_H1){
    
        std::this_thread::sleep_for(std::chrono::seconds(randomNum()));
        std::cout << "H1 produced" <<std::endl;
        p_H1.set_value('H');
} 

void produce_h2(std::promise<char>& p_H2){
    
    std::this_thread::sleep_for(std::chrono::seconds(randomNum()));
    std::cout << "H2 produced" <<std::endl;
    p_H2.set_value('H');
} 


void produce_O(std::promise<char>& p_O){
    
    std::this_thread::sleep_for(std::chrono::seconds(randomNum()));
    std::cout << "O produced" <<std::endl;
    p_O.set_value('O');
} 

void consume (std::future<char>& f_H1,std::future<char>& f_H2, std::future<char>& f_O){

    char h1 = f_H1.get();
    char h2 = f_H2.get();
    char o = f_O.get();

    std::cout<<"Water produced: " << h1 << h2 << o << std::endl;
}


int main(){
    std::promise<char> p_H1, p_H2, p_O;
    std::future<char> f_H1 = p_H1.get_future();
    std::future<char> f_H2 = p_H2.get_future();
    std::future<char> f_O = p_O.get_future();

    std::thread t1(produce_h1, std::ref(p_H1));
    std::thread t2(produce_h2, std::ref(p_H2));
    std::thread t3(produce_O, std::ref(p_O));
    std::thread t4(consume, std::ref(f_H1), std::ref(f_H2), std::ref(f_O));

    t1.join();
    t2.join();
    t3.join();
    t4.join();




    return 0;
}