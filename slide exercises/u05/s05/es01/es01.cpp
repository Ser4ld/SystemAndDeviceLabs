#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <semaphore>


const int NTH = 10;

std::counting_semaphore<NTH> sem(0);
std::mutex mtx;
std::mutex mtx_out; 
int threads_arrived = 0;


void worker(int id){
    {
        std::lock_guard<std::mutex> lock(mtx_out);
        std::cout<<"Thread with id "<< id << "working"<<std::endl;
    }

    mtx.lock();
    threads_arrived++;
    if(threads_arrived == NTH ){    
        sem.release(NTH);
    }
    mtx.unlock();
    
    sem.acquire();

    {
        std::lock_guard<std::mutex> lock(mtx_out);
        std::cout<<"Thread with id "<< id << " finished"<<std::endl;
    }


}

int main(){

    std::vector<std::thread> threads;
    for (int i=0; i<NTH; i++){
        threads.emplace_back(worker, i);
    }

    for(auto& t: threads){
        t.join();
    }

    return 0;

}