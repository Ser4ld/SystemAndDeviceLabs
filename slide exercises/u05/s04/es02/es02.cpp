#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <random>
#include <chrono>

int var = 0;
const int ADDERS = 5; 
int completed_adders = 0;
bool done = false; 

std::mutex mtx;
std::condition_variable cv; 
std::condition_variable cv_started;

int randomRank(){

    // Generatore di numeri casuali
    static std::random_device rd;  // Dispositivo per generare numeri casuali
    static std::mt19937 gen(rd());  // Mersenne Twister per la generazione
    return std::uniform_int_distribution<int>(1, 2) (gen);  // Distribuzione per numeri casuali tra 1 e 1000
}


void adder(){
    
    std::unique_lock<std::mutex> lock (mtx);

    while(var == 0){
        cv_started.wait(lock);
    }

    int random_val= randomRank();

    if(var < 15){
        var += random_val;
        std::cout << "Thread " << std::this_thread::get_id() << " added " << random_val << ", new value of var: " << var << std::endl;

    }

    completed_adders++;

    if(completed_adders == ADDERS || var >= 15){
        done = true; 
        cv.notify_one();
    }   

}




void admin_set(){
    std::unique_lock<std::mutex> lock (mtx);
    
    var = 10; 
    cv_started.notify_all();
    
    while (!done){
        cv.wait(lock);
    }

    std::cout <<"Valore finale di var:"<<var<<std::endl;
}

int main(){
    std::thread admin(admin_set);

    std::vector<std::thread> adders;

    for (int i=0; i<ADDERS; i++){
        adders.emplace_back(adder);
    }

    for (auto& th: adders){
        th.join();
    }

    admin.join();
    return 0;
}