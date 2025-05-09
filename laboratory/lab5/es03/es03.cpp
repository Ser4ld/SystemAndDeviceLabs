#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <random>
#include <chrono>
#include <cstdlib>

double target = 18.0; // Target value
double actual_temperature = 18.5;
bool heating = false;
std::mutex mtx;
std::mutex mtx_cout;
int input = 0;

void target_temp(){

    while(true){     
    
        int target_temp = 0;

        {
            std::lock_guard<std::mutex> lock(mtx_cout);
            std::cout<< "Enter target temperature" <<std::endl;
        }

        std::cin >> target_temp; 
        {
            std::lock_guard<std::mutex> lock(mtx);
            target = target_temp;
            {
                std::lock_guard<std::mutex> lock(mtx_cout);
                std::cout << "Target temperature set to: " << target << std::endl;
            }

            if(target == -1){
                break;
            }
        }
    
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate time taken to set target temperature
    
    }


}


void admin_mange(){

    while (true){
        {
            std::lock_guard<std::mutex> lock(mtx); //lock per la stampa
            if(target == -1){
                break;
            }

            if(actual_temperature - target > 0.2){
                
                if(heating){
                    heating = false;
                    std::lock_guard<std::mutex> lock(mtx_cout); //lock per la stampa
                    std::cout << "Heating OFF" << std::endl;
                }

            }else {
                if(!heating){
                    heating = true;
                    std::lock_guard<std::mutex> lock(mtx_cout); //lock per la stampa
                    std::cout << "Heating ON" << std::endl;
                }
            }
        
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));

    }
}

void update_current_temp(){
    while(true){
        {
            std::lock_guard<std::mutex> lock(mtx); //lock per la stampa
            if(target == -1){
                break;
            }
            
            if(heating){
                actual_temperature += 0.3; // Simulate heating
            }else{
                actual_temperature -= 0.3; // Simulate cooling
            }

            {
                std::lock_guard<std::mutex> lock(mtx_cout); //lock per la stampa
                std::cout << "Current temperature: " << actual_temperature << std::endl;
            }
           
        }



        std::this_thread::sleep_for(std::chrono::seconds(5));


    }

}

int main(){
    
    std::thread targetTemp(target_temp);
    std::thread admin(admin_mange);
    std::thread currentTemp(update_current_temp);
    
    targetTemp.join();
    admin.join();   
    currentTemp.join();





    return 0;
}