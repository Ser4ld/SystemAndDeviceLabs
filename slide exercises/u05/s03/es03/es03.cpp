#include <semaphore>
#include <thread>
#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std;


map<int, unique_ptr<binary_semaphore>> prioritysem; // Usato il puntatore perchè il semaforo non è copiabile

mutex cout_mutex; // Mutex per il controllo dell'output in console, per la stampa del cout in quanto più thread cercano di stampare contemporaneamente

void worker(int i, int priority) {
    {
        //Serve per evitare che più thread stampino contemporaneamente, sovrapponendo l’output.
        //lock_guard<mutex> è un RAII lock: prende il lock del mutex all’inizio del blocco, e lo rilascia automaticamente alla fine.
        lock_guard<mutex> lock(cout_mutex);
        cout << "Il thread " << i << " con priorita' " << priority << " e' in lock" << endl;
    }

    // Creazione del semaforo binario specifico per questo thread
    //Crea un semaforo inzializzato a 0 (quindi bloccato) e con make_unique
    //permette di creare un semaforo binario unico (unique_ptr) che gestisce la memoria automaticamente.
    prioritysem.insert({priority, make_unique<binary_semaphore>(0)});

    // eseguiamo l'acquisizione del semaforo binario specifico per questo thread tramite il puntatore e il valore priority
    //Il thread si blocca qui, in quanto viene inizializzato con semaforo a 0
    (*prioritysem[priority]).acquire();

    // Locking per l'output sulla console
    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Sblocco thread " << i << " con priorita' " << priority << endl;
    }
}

int main() {
    int i, priority;
    int n = 10;
    vector<thread> pool;

    // Creazione dei thread con priorità
    for (i = 0; i < n; i++) {
        priority = (i + 1) * 100;  // Priorità crescente
        pool.emplace_back(thread(worker, i, priority));
    }

    // Assicuriamo che i thread vengano sbloccati in ordine di priorità crescente
    i = 0;

    // Aspetta che tutti i worker abbiano inserito il proprio semaforo nella mappa
    while(prioritysem.size() < n) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    for (const auto &t : prioritysem) {
        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Sbloccando thread " << i++ << " con priorita' " << t.first << endl;
        }
        // Rilascia il semaforo del thread uguale a scrivere (*t.second).release() ma in questo caso con -> viene fatta automaticamente la dereferenziazione
        t.second->release();  
    }

    // Attendi che tutti i thread finiscano
    for (i = 0; i < n; i++) {
        pool[i].join();
    }

    return 0;
}