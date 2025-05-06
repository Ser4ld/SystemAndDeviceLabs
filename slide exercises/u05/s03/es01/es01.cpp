#include <iostream>
#include <semaphore>
#include <thread>
#include <chrono> // for sleep_for

// in questo caso usiamo dei semafori perchè i mutex devono essere lockati e sbloccati dallo stesso thread

using namespace std; 

std::counting_semaphore<1> sa(1); // inizialmente il semaforo è a 0
std::counting_semaphore<2> sb(2); // inizialmente il semaforo è a 0
std::counting_semaphore<1> me(1);  // mutex per il contatore

int n=0; //contatore per numero caratteri stampati per ogni gruppo

void TA(int count){
    for (int i=0; i<count; i++){
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 2));
        sa.acquire(); // aspetto che il semaforo sia libero
        me.acquire(); // prendo il mutex per il contatore
        
        cout<<"A";
        n++;

        if(n>=3){
            cout<<endl;
            n = 0;
            sa.release(); // rilascio il semaforo per il gruppo A
            sb.release(); // rilascio il semaforo per il gruppo B
            sb.release(); // rilascio il semaforo per il gruppo B

        }

        me.release(); // rilascio il mutex per il contatore
    
    }
}


void TB(int count){
    for (int i=0; i<count; i++){
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 2));
        sb.acquire(); // aspetto che il semaforo sia libero
        me.acquire(); // prendo il mutex per il contatore
        
        cout<<"B";
        n++;

        if(n>=3){
            cout<<endl;
            n = 0;
            sa.release(); // rilascio il semaforo per il gruppo A
            sb.release(); // rilascio il semaforo per il gruppo B
            sb.release(); // rilascio il semaforo per il gruppo B

        }

        me.release(); // rilascio il mutex per il contatore
    
    }
}


int main() {
    int n = 5; // quanti cicli per A; B sarà 2×n

    std::thread ta(TA, n);
    std::thread tb(TB, 2 * n);

    ta.join();
    tb.join();

    return 0;
}
// Compilare con: g++ -std=c++20 es01.cpp -o es01