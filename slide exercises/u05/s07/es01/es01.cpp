#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <thread>

void take(std::promise<int>& p_in){

    int number;
    std::cout << "Insert a number:";
    std::cin >> number;
    p_in.set_value(number);
}

void check(std::future<int>& f_in, std::promise<bool>& p_res){


    int n = f_in.get(); // get the value from the future
    bool prime = true;
    if(n<=1) prime = false;

    for (int i=2; i<n; i++){
        if(n%i == 0){
            prime = false;
            break;
        }
    }

    p_res.set_value(prime);
}

void give(std::future<bool>& f_res){

    bool prime = f_res.get();

    if(prime){
        std::cout<< "The number is prime." << std::endl;
    } else{
        std::cout<< "The number is not prime." << std::endl;
    }
}


int main(){
    std::promise<int> p_in;
    std::future<int> f_in = p_in.get_future();

    std::promise<bool> p_res;
    std::future<bool> f_res = p_res.get_future();

    std::thread t1(take, std::ref(p_in));
    std::thread t2(check, std::ref(f_in), std::ref(p_res));
    std::thread t3(give, std::ref(f_res));

    t1.join();
    t2.join();  
    t3.join();

    return 0;

}