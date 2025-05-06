#include <iostream>
#include <semaphore>
#include <thread>
#include <chrono> // for sleep_for
#include <chrono>


using namespace std; 

std::counting_semaphore<1> sp(1); // inizialmente il semaforo è a 1 per stampare i +
std::counting_semaphore<2> sm(0); // inizialmente il semaforo è a 0
std::counting_semaphore<1> ss(0);  // inizialmente il semaforo è a 0
std::counting_semaphore<1> snl(0);  // inizialmente il semaforo è a 0
std::counting_semaphore<1> me(1);  // mutex per il contatore
int contatore = 0;
bool stopFlag = false; // flag per fermare i thread

static void TP(int N){
    while(true){
        sp.acquire(); // aspetto che il semaforo sia libero
        if (stopFlag) break;
        for (int i=0; i<N; i++){
            cout<<"+";
        }
        snl.release(); // rilascio il semaforo per il gruppo A
    }
}


static void TM(int N){
    while(true){
        sm.acquire(); // aspetto che il semaforo sia libero
        if (stopFlag) break;
        for (int i=0; i<N; i++){
            cout<<"-";
        }
        snl.release(); // rilascio il semaforo per il gruppo A
    }
}

static void TS(int N){
    while(true){
        ss.acquire(); // aspetto che il semaforo sia libero
        if (stopFlag) break;
        for (int i=0; i<N; i++){
            cout<<"*";
        }
        snl.release(); // rilascio il semaforo per il gruppo A
    }
}

static void TNL(int N, int M){
    while(true){
        snl.acquire(); // aspetto che il semaforo sia libero
        cout<<endl;

        me.acquire(); // prendo il mutex per il contatore
        contatore++; // incremento il contatore
        if(contatore >= M){
            stopFlag = true;
            sp.release();
            sm.release();
            ss.release();

            me.release(); // rilascio il mutex per il contatore
            break; // esco dal ciclo se ho stampato M righe
        }
        int prossimo = contatore % 3; // calcolo il prossimo gruppo
        me.release(); // rilascio il mutex per il contatore

        if(prossimo == 0){
            sp.release(); // rilascio il semaforo per il gruppo M
        } else if(prossimo == 1){
            sm.release(); // rilascio il semaforo per il gruppo P
        } else {
            ss.release(); // rilascio il semaforo per il gruppo S
        }
    }
}


int main() {
    int N = 10; // numero di simboli per riga
    int M = 12; // numero di righe per simbolo
    std::thread tp(TP, N);
    std::thread tm(TM, N);
    std::thread ts(TS, N);
    std::thread tnl(TNL, N, M);

    tp.join();
    tm.join();
    ts.join();
    tnl.join();

    return 0;
}
// Compilare con: g++ -std=c++20 es02.cpp -o es02
