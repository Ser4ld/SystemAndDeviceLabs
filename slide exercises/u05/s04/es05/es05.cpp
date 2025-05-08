//La richiesta è di implementare lo schema "First Reader-Writer" 
//(o "Readers-Writers Problem, First Readers") usando std::condition_variable
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <random>
#include <chrono>

std::mutex mtx;
std::mutex mtx_cout;
std::condition_variable cv;
int readersCount = 0;
bool writerActive = false;
const int NUM_READERS = 5;
const int NUM_WRITERS = 5;


void reader(){
    {
        std::unique_lock<std::mutex> lock(mtx);
        while(writerActive){
            cv.wait(lock);
        }
        readersCount++;

    }
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate reading time
    {
        std::lock_guard<std::mutex> lock(mtx_cout);
        std::cout<< "Reading..."<<std::endl;
    }

    {
        std::unique_lock<std::mutex> lock(mtx);
        readersCount--;
        if(readersCount == 0){
            cv.notify_all();
        }

    }
}

void writer(){
    {
        std::unique_lock<std::mutex> lock(mtx);
        while(readersCount > 0){
            cv.wait(lock);
        }
        writerActive = true;
    }

    {
        std::lock_guard<std::mutex> lock(mtx_cout);
        std::cout<< "Writing..."<<std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate writing time

    {
        std::unique_lock<std::mutex> lock(mtx);
        writerActive = false;
        cv.notify_all();
    }
}

int main(){
std::vector<std::thread> readers;
std::vector<std::thread> writers;

for(int i = 0; i<NUM_READERS; i++){
    readers.emplace_back(reader);
    writers.emplace_back(writer);
}

for (auto& t: readers){
    t.join();   

}
for(auto& t: writers){
    t.join();       
}

return 0;
}