#include <iostream>
#include <string>
#include <set>

using namespace std;

struct Player{

    string name;
    int score;
    
    /*Questa è una ridefinizione dell'operatore <, usata ad esempio per ordinare i 
    Player in un std::set o std::sort.*/

    bool operator<(const Player& other) const {
        if (score != other.score)
            return score > other.score; // score alto prima
        return name < other.name;       // in caso di parità, ordina per nome
    }

};


/*Questa è una ridefinizione dell'operatore di output <<, che ti 
permette di stampare un Player con cout << p;.*/

ostream& operator<<(ostream& os, const Player& p) {
    os << p.name << " - " << p.score;
    return os;
}


class Leaderboard{
    private:
    set<Player> s;

    public:

    void addPlayer(const string& name, const int& score){

        s.insert({name, score});
    
    }

    void removePlayer(const string& name){
        for(auto it = s.begin(); it != s.end(); ++it){
            if(it->name == name){
                s.erase(it);
                break;
            }
        }
        
    }

    void updateScore(const string& name, const int& newScore){
        for(auto it = s.begin(); it != s.end(); ++it){
            if(it->name == name){
                s.erase(it);
                break;
            }
        }
        s.insert({name, newScore});
    } 

    void printTopPlayers(const int& n){
        int count = 0;
        for (auto it = s.begin(); it != s.end() && count < n; ++it, ++count) {
            cout << *it << endl;
        }       

    }


};


int main( int argc, char **argv){

    bool flag=true;
    int choice;
    string nome;
    int score;
    int n;
    Leaderboard lb;
    while (flag)
    {
        cout<<"0)inserisci player"<<endl;
        cout<<"1)rimuovi player"<<endl;
        cout<<"2)modifica score player"<<endl;
        cout<<"3)stampa top player"<<endl;
        cout<<"4)esci"<<endl;
        cin>>choice;


        switch (choice)
        {
        case 0:
            cout<<"Nome: ";
            cin>>nome;
            cout<<"Score: ";
            cin>>score;
            lb.addPlayer(nome, score);
            break;
        case 1:
            cout<<"Nome: ";
            cin>>nome;
            lb.removePlayer(nome);
            break;
        case 2:
            cout<<"Nome: ";
            cin>>nome;
            cout<<"Score: ";
            cin>>score;
            lb.updateScore(nome, score);
            break;
        case 3:
            cout<<"Scrivi il numero di top rank player da visualizzare: ";
            cin>> n;
            lb.printTopPlayers(n);
            break;
        case 4:
            flag=false;
            break;
        default:
            
            break;
        }
    }
    return 0;
}