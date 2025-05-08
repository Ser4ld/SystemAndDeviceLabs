#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <semaphore>

const int NTH = 5;

std::counting_semaphore<NTH> sem(0);
std::counting_semaphore<NTH> sem2(0);
std::mutex mtx;
std::mutex mtx_out; 
int threads_arrived = 0;
int threads_finished = 0;
int num_iterations = 3;
int count = 0;



void worker(int id){
        while (count != num_iterations){

            {
                std::lock_guard<std::mutex> lock(mtx_out);
                std::cout<<"Thread with id: "<< id << " working"<<std::endl;
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
                std::cout<<"Thread with id: "<< id << " finished"<<std::endl;
            }

            mtx.lock();
            threads_arrived--;
            if(threads_arrived == 0){
                sem2.release(NTH);
                count++;
            }
            mtx.unlock();

            sem2.acquire();



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

