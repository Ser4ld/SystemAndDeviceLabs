#include <iostream>
#include <fstream>

using namespace std;

struct Record{
    int row;
    long reg;
    char surname[31];
    char name[31];
    int mark;
};

int main(int argc, char **argv){
    char selection;
    int n;
    bool loop=true;

    if(argc!=2){
        cerr << "Argument error" << endl;
        return EXIT_FAILURE;
    }

    fstream filein(argv[1], ios::in | ios::out | ios::binary);

    if(!filein.is_open()){
        cerr << "File error" << endl;
        return EXIT_FAILURE;
    }

    Record r;
    while(loop){
        cout << "Seleziona operazione" << endl;
        cin >> selection ;
        switch (selection)
        {
        case 'R':
            cin >> n;
            filein.seekg((n-1)*sizeof(Record), ios::beg);
            filein.read(reinterpret_cast<char*>(&r), sizeof(Record));
            cout << r.row << " " << r.reg << " " << r.surname << " " << r.name << " " << r.mark << endl;
            break;
        case 'W':
            cin >> n;
            cout << "Inserisci nuovo record" << endl;
            cin >> r.row >> r.reg >> r.surname >> r.name >> r.mark;
            filein.seekg((n-1)*sizeof(Record), ios::beg);
            filein.write(reinterpret_cast<char*>(&r), sizeof(Record));
            break;
        case 'E':
            loop=false;
            break;
        default:
            break;
        }
    }

    filein.close();
    return EXIT_SUCCESS;
}