#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <random>
#include <chrono>
#include <queue>


std::mutex mtx;
std::condition_variable cv;
bool stop = false;
const int NP = 3;
const int NC = 2;
const int NUM_ITEMS = 5;
int producer_completed = 0;
std::queue<int> buffer;
std::mutex mtx_cout;

int randomNum(){

    // Generatore di numeri casuali
    static std::random_device rd;  // Dispositivo per generare numeri casuali
    static std::mt19937 gen(rd());  // Mersenne Twister per la generazione
    return std::uniform_int_distribution<int>(1, 10) (gen);  // Distribuzione per numeri casuali tra 1 e 1000
}

void produce(){

    for (int i=0; i<NUM_ITEMS; i++){
        {
        std::lock_guard<std::mutex> lock(mtx);
        int random_value = randomNum();
        buffer.push(random_value);
        std::lock_guard<std::mutex> lock_cout(mtx_cout); //lock per la stampa
        std::cout<<"Produced: "<< random_value<<std::endl;
        }
        
        //notifico che un nuovo elemento è stato prodotto 
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        producer_completed++;
        if(producer_completed == NP){
            stop = true;
        }
    }
    
    
    cv.notify_all();

}

void consume(){
    while(true){
        std::unique_lock<std::mutex> lock(mtx);
        //mi metto in attesa se il buffer è vuoto e se il producer non ha finito
        // cona lambda cv.wait(lock, [] { return !buffer.empty() || stop; }); Svegliami quando c’è qualcosa da consumare (!buffer.empty())
        // oppure il producer ha terminato (stop == true)
        while(!stop && buffer.empty()){
            cv.wait(lock);
        }

        //se i producer hanno finito e il buffer è vuoto, esco dal ciclo (tutti item consumati)
        if(stop && buffer.empty()){
            break;
        }

        int value = buffer.front(); //prendo il primo elemento
        buffer.pop(); //lo tolgo dal buffer 
       
        lock.unlock(); //sblocco il mutex per permettere al producer di produrre
        std::lock_guard<std::mutex> lock_cout(mtx_cout); //lock per la stampa
        std::cout<<"Consumed: "<<value<<std::endl; //consumo l’elemento
        
   

    }
}


int main(){

std::vector<std::thread> producers;
std::vector<std::thread> consumers;

for (int i = 0; i<NP; i++){
    producers.emplace_back(produce);
}

for (int i = 0; i<NC; i++){
    consumers.emplace_back(consume);
}

for(auto& t: producers){
    t.join();
}

for(auto& t: consumers){
    t.join();
}

return 0;



}