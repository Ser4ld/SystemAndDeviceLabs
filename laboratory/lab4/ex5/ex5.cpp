#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <random>

using namespace std;


double random_gen(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_real_distribution<double>(-0.5, 0.5)(gen);
    
}

void compute_calc(const std::vector<double>& v1, const std::vector<double>& row, double& result){
    double sum = 0.0;
    for (size_t i=0; i<v1.size(); i++){
        sum += v1[i] * row[i];
    }
    result = sum;
    
}

int main(int argc, char **argv){

    if(argc != 2){
        cerr<<"Argument error"<< std::endl;
        return EXIT_FAILURE;
    }

    int n = stoi(argv[1]); //stoi converte una stringa in un intero 

    std::vector<double> v1(n), v2(n);
    std::vector<std::vector<double>> mat(n,std::vector<double>(n));

    cout<<"Vector 1: ";
    for (auto& v: v1){
        v= random_gen();
        cout<<v<<" ";
    }
    cout<<endl;
    
    cout<<"Vector 2: ";
    for(auto& v: v2){
        v = random_gen();
        cout<<v<<" ";
    }
    cout<<endl;
        
    

    for (int i=0; i<n; i++){
        cout<<"Row: ";
        for(int j=0; j<n; j++){
            mat[i][j] = random_gen();
            cout<<mat[i][j]<<" ";

        }
        cout<<endl;
    }

            

    std::vector<std::thread> threads;
    std::vector<double> v(n, 0.0);
    
    for (int i=0; i<n; i++){
        threads.emplace_back(compute_calc, ref(v1), ref(mat[i]), ref(v[i]));
    }

    for (auto& th: threads){
        th.join();
    }
    

    double final_result = 0.0;
    for (size_t i=0; i<v.size(); i++){
        final_result += v[i] * v2[i];
    }

    cout<<"Final result: " << final_result << endl;
    return 0;


}