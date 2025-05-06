#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

std::vector<std::vector<int>> sortArrays;


void readAndSort(const string& filename, int index){

    ifstream filein(filename, ios::binary);

    if(!filein){
        cerr << "Error opening file: " << filename <<endl;
        return;
    }

    int count = 0;
    //leggo il primo numero binario nel file, il size da leggere lo indico come secondo parametro sizeof(int)
    filein.read(reinterpret_cast<char*>(&count), sizeof(int));
    if(!filein || count <=0){
        cerr << "Error reading count from file: " << filename <<endl;
        return;
    }

    sortArrays[index].resize(count); // ridimensiono il vector in base al numero di elementi da leggere
    //numbers.data() restituisce il puntatore al primo elemento del vector
    //count*sizeof(int) è il numero di byte da leggere dal file
    //filein.read interpreta i byte letti come un array di int e li memorizza in numbers
    filein.read(reinterpret_cast<char*>(sortArrays[index].data()), count*sizeof(int));
    filein.close();

    std::sort(sortArrays[index].begin(), sortArrays[index].end()); // ordino i numeri letti dal file (ASC)

}

std::vector<int> mergeArrays (const std::vector<std::vector<int>>& arrays){
 std::vector<int> merged;
 for (const auto& arr : arrays){
        merged.insert(merged.end(), arr.begin(), arr.end());
 }

 std::sort(merged.begin(), merged.end()); // ordino i numeri letti dai file (ASC)
 return merged;

}

void writeOutput(const string& filename, const std::vector<int>& data){
    ofstream fileout (filename, ios::binary);

    if(!fileout){
        cerr << "Error opening file: " << filename <<endl;
        return; 
    }

    int size = data.size();

    fileout.write(reinterpret_cast<const char*>(&size), sizeof(int));
    fileout.write(reinterpret_cast<const char*>(data.data()), size * sizeof(int));
    fileout.close();
}

int main(int argc, char **argv){

    //controllo < 3 perchè se abbiamo solo 2 argomenti significa che possiamo al massimo specificare un solo file.bin
    if(argc<3){
        std::cerr<<"Argument error"<< std::endl;
        return EXIT_FAILURE;
    }

    fstream filein (argv[1], ios::in | ios::binary);

    int numInput = argc -2; // numero di file binari
    std::vector<std::string> input_files;

    //creo un vector con i nomi dei file binari di input
    for (int i=1; i<=numInput; i++){
        input_files.push_back(argv[i]);
    }

    string output_file = argv[argc-1]; // nome del file di output

    sortArrays.resize(numInput); // inizializza 3 righe (dove ogni riga è un vector di int) per i 3 file binari di input)

    std::vector<std::thread> threads;

    for (int i=0; i<numInput; i++){
        threads.emplace_back(readAndSort,input_files[i], i);
    }

    for(auto& th: threads){
        th.join();
    }

    writeOutput(output_file, mergeArrays(sortArrays));
    return 0;

}