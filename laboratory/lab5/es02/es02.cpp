#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <random>
#include <chrono>
#include <cstdlib>

std::mutex mtx; //mutex per la stampa
std::mutex mtx_cout;
bool stop = false;

int randomNum(int min_value, int max_value){

    // Generatore di numeri casuali
    static std::random_device rd;  // Dispositivo per generare numeri casuali
    static std::mt19937 gen(rd());  // Mersenne Twister per la generazione
    return std::uniform_int_distribution<int>(min_value, max_value) (gen);  // Distribuzione per numeri casuali tra 1 e 1000
}

void enter_parking(int& available_parking){
    while(true){
        {
            std::lock_guard<std::mutex> lock(mtx); //lock per la stampa
            if(stop){
                break;
            }

        }
        
        {
            std::lock_guard<std::mutex> lock(mtx); //lock per la stampa

            if(available_parking > 0){
                available_parking--;
                {
                    std::lock_guard<std::mutex> lock_cout(mtx_cout); //lock per la stampa
                    std::cout<<"Car entered the parking. Available parking: "<<available_parking<<std::endl;
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(randomNum(1,3)));
    
    }
}

void exit_parking(int& available_parking){
    while(true){
        {
            std::lock_guard<std::mutex> lock(mtx); //lock per la stampa
            if(stop){
                break;
            }

        }

        {
            std::lock_guard<std::mutex> lock(mtx); //lock per la stampa
            available_parking++;
            {
                std::lock_guard<std::mutex> lock_cout(mtx_cout); //lock per la stampa
                std::cout<<"Car exit the parking. Available parking: "<<available_parking<<std::endl;
            }
            
        }
        std::this_thread::sleep_for(std::chrono::seconds(randomNum(4,7))); //simulazione del tempo di attesa
        
    }
}

int main(int argv, char **argc){
    
    if(argv != 3){
        std::cout<<"Error"<<std::endl;
        return EXIT_FAILURE;
    }

    int number_parking = std::stoi(argc[1]);
    int time_simulation = std::stoi(argc[2]);
    int available_parking = number_parking; //numero di parcheggi disponibili
    
    
    std::thread t_enter(enter_parking,std::ref(available_parking));
    std::thread t_exit(exit_parking,std::ref(available_parking));






    while (true){
        std::this_thread::sleep_for(std::chrono::seconds(1)); //simulazione del tempo di attesa
        time_simulation--;
        
        if(time_simulation ==0){
            std::lock_guard<std::mutex> lock(mtx); //lock per la stampa
            std::cout<<"Simulation ended"<<std::endl;
            stop = true;
            break; 
        }

    }

    t_enter.join();
    t_exit.join();
    




}

// Compilazione: g++ -std=c++20 es02.cpp -o es02 