#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>


std::mutex cout_mtx;

struct MySemaphore{
    std::mutex mtx;
    std::condition_variable cv; 
    int count = 0;

public: 
    //costruttore inizializza il semafore con valore count pari a initial_count
    MySemaphore(int initial_count) : count(initial_count){}


    //Acquisiamo il lock del mutex.
    //Se count == 0, significa che nessun permesso è disponibile, quindi il thread si mette in attesa sulla condition variable.
    //Quando il thread si risveglia (perché cv.notify_one() è stato chiamato), ricontrolla la condizione.
    //Se count > 0, decrementa count → il thread può procedere.
    void wait(){
        std::unique_lock<std::mutex> lock(mtx);
        while (count == 0){
            cv.wait(lock);
        }
        count--;
    }

    //Acquisisce il lock.
    //Incrementa il numero di permessi disponibili (count).
    //Risveglia un solo thread in attesa su cv (se ce n’è uno), che potrà ora passare la wait().
    void signal(){
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }



};

void worker(int id, MySemaphore& sem){
    sem.wait();
   
    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << "Thread " << id << " is working..." << std::endl;
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simula un lavoro}
    
    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << "Thread " << id << " finished working." << std::endl;
    }
    
    sem.signal();
}

int main(){
    const int MAX_CONCURRENT = 3;  // massimo 3 thread alla volta
    const int TOTAL_THREADS = 5;

    MySemaphore sem(MAX_CONCURRENT); // inizializza il semaforo con 3 permessi
    std::vector<std::thread> threads;

    for (int i=0; i < TOTAL_THREADS; i++){
        threads.emplace_back(worker, i, std::ref(sem));
    }

    for(auto& th: threads){
        th.join();
    }

    return 0; 

}


//g++ -std=c++20 es01.cpp -o es01