#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <random>
#include <chrono>



std::vector<int> v;
std::mutex mtx;
std::condition_variable cv;
bool running = true;
int command = -1; // 0=exit, 1=print, 2=last value, 3=delete values

int randomNum(){

    // Generatore di numeri casuali
    static std::random_device rd;  // Dispositivo per generare numeri casuali
    static std::mt19937 gen(rd());  // Mersenne Twister per la generazione
    return std::uniform_int_distribution<int>(1, 10) (gen);  // Distribuzione per numeri casuali tra 1 e 1000
}

void writer(){
    while(running){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        int random_value = randomNum();

        std::lock_guard<std::mutex> lock(mtx);
        v.push_back(random_value);
        std::cout << "Writer thread added value: " << random_value << std::endl;
    }
}


void ui(){
    while(running){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout<< "Inserisci comando: (0=esci, 1 =stampa, 2=ultimo valore, 3= elimina valori)"<<std::endl;
        
        int input;
        std::cin>>input;
        std::lock_guard<std::mutex> lock(mtx);
        command=input;
        if(command == 0){
            running = false;
        }

        cv.notify_one();
    }
}

void worker(){
    while(running){
        std::unique_lock<std::mutex> lock(mtx);

        while(command == -1){
            cv.wait(lock);
        }

        switch (command){
            case 0:
                std::cout << "Exiting" << std::endl;
                running = false;
                break;
            case 1:
                std::cout << "Current values in vector: ";
                for(auto& i : v){
                    std::cout << i << " ";
                }
                std::cout << std::endl;
                break;
            case 2:
                if(!v.empty()){
                    std::cout << "Last value: " << v.back() << std::endl;
                } else {
                    std::cout << "Vector is empty" << std::endl;
                }
                break;
            case 3:
                v.clear();
                std::cout << "All values deleted" << std::endl;
                break;  
            default:
                std::cout << "Invalid command" << std::endl;
                break;
            
        }

        command = -1;
    }
}


int main(){
    std::thread t_writer(writer);
    std::thread t_ui(ui);
    std::thread t_worker(worker);

    t_ui.join();
    cv.notify_one(); //assicura che il worker non resti bloccato se command == 0
    t_writer.join();
    t_worker.join();

    return 0;
}








