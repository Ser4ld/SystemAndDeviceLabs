#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <barrier>
#include <random>

bool sorted = false;
bool element_sorted = true;
std::mutex mtx_cout;

int randomNum(){

    // Generatore di numeri casuali
    static std::random_device rd;  // Dispositivo per generare numeri casuali
    static std::mt19937 gen(rd());  // Mersenne Twister per la generazione
    return std::uniform_int_distribution<int>(1, 10) (gen);  // Distribuzione per numeri casuali tra 1 e 1000
}

void bubble_sort(int pos, std::vector<int>& array, std::vector<std::mutex>& mtx, std::barrier<>& barrier){

    while(!sorted){

        {
            std::lock_guard<std::mutex> lock(mtx[pos]);
            std::lock_guard<std::mutex> lock_next(mtx[pos+1]);
    
            if(array[pos] > array[pos+1]){
                int temp = array[pos];
                array[pos] = array[pos+1];
                array[pos+1] = temp;
                element_sorted = false;
            }
        }

        barrier.arrive_and_wait(); // Aspetta che tutti i thread arrivino qui

        //il primo thread (ovvero quando pos = 0) controlla l'array)
        if(pos == 0){

            for (size_t i=0; i<array.size(); i++){
                std::cout<<array[i]<<" ";
             }
             std::cout<<std::endl;

            if(element_sorted)
                    sorted = true; //se non ci sono stati scambi(element_sorted è rimasto true) l'array è ordinato 
            else 
                element_sorted = true; //altrimenti lo setto a true per il prossimo giro
        }
        
        barrier.arrive_and_wait();



    }

}

int main(int argv, char **argc){

    if (argv != 2){
        std::cerr<< "Error"<<std::endl;
        return EXIT_FAILURE;
    }

    int array_size = std::stoi(argc[1]);
    int number_threads = array_size-1;
    std::vector<std::thread> threads;
    std::vector<int> array(array_size);
    std::barrier<> barrier (number_threads);
    std::vector<std::mutex> mtx(array_size);

    //inizializzo il vettore con n numeri casuali
    for (int i=0; i<array_size; i++){
       array[i] = randomNum();
       std::cout<<array[i]<<" ";
    }
    std::cout<<std::endl;

    for (int i=0; i<array_size-1; i++){
        threads.emplace_back(bubble_sort, i, std::ref(array), std::ref(mtx), std::ref(barrier));
    }

    for(auto& th:threads){
        th.join();
    }

    return 0;

}