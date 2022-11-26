#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int const DIM_TABLA = 3;
// Pentru tabla 3*3 sunt necesare in jur de 31 miscari
int const DIM_SOL = 40;
int const DIM_POP = 50;
int const RATA_MUT = 10;

char populatie[DIM_POP][DIM_SOL];
char populatieTemp[DIM_POP][DIM_SOL];

int stareInitiala[][DIM_TABLA] = {
    {8, 0, 7},
    {4, 5, 1},
    {6, 3, 2}
};
int iPozitieLibera = 0;
int jPozitieLibera = 1;

int stareFinala[][DIM_TABLA] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

int stareCurenta[DIM_TABLA][DIM_TABLA];
char solutie[DIM_SOL];
int lungimeSol;

void genereazaPopulatieInitiala() {
    for (int i = 0; i < DIM_POP; i++) {
        for (int j = 0; j < DIM_SOL; j++) {
            int numarRandom = rand()%4;
            switch(numarRandom) {
            case 0:
                populatie[i][j] = 'N';
                break;
            case 1:
                populatie[i][j] = 'S';
                break;
            case 2:
                populatie[i][j] = 'V';
                break;
            case 3:
                populatie[i][j] = 'E';
                break;
            }
        }
    }
}

vector<pair<int, int>> selectie() {
    vector<pair<int, int>> parinti;

    for(int i=0; i<DIM_POP/2; i++){
        // alegem doi parinti la intamplare
        int pozitieParinte1 = rand()%DIM_POP;
        int pozitieParinte2 = rand()%DIM_POP;

        parinti.push_back(make_pair(pozitieParinte1, pozitieParinte2));
    }

    return parinti;
}

void recombinare(vector<pair<int, int>> parinti) {

    for(int i=0; i<DIM_POP/2; i++){
        //extragem pozitiile parintilor
        int pozitieParinte1 = parinti[i].first;
        int pozitieParinte2 = parinti[i].second;

        // alegem punct de taietura la intamplare
        int pozitieTaietura = rand()%DIM_SOL;

        // copiem genele pana la pct de taietura din parinte1 in copil1
        for(int j=0; j<pozitieTaietura; j++){
            populatieTemp[2*i][j] = populatie[pozitieParinte1][j];
        }
        // copiem genele de la pct de taietura din parinte2 in copil1
        for(int j=pozitieTaietura; j<DIM_SOL; j++){
            populatieTemp[2*i][j] = populatie[pozitieParinte2][j];
        }

        // copiem genele pana la pct de taietura din parinte2 in copil2
        for(int j=0; j<pozitieTaietura; j++){
            populatieTemp[2*i+1][j] = populatie[pozitieParinte2][j];
        }
        // copiem genele de la pct de taietura din parinte1 in copil2
        for(int j=pozitieTaietura; j<DIM_SOL; j++){
            populatieTemp[2*i+1][j] = populatie[pozitieParinte1][j];
        }
    }
}

void mutatie() {
    for(int i = 0; i<DIM_POP; i++) {
        int probabilitate = rand()%100;
        if (probabilitate < RATA_MUT) {
            // schimbam o miscare aleatoare cu o alta miscare
            int pozitieGena = rand()%DIM_SOL;
            int genaNoua = rand()%4;
            char caracter;
            switch(genaNoua) {
                case 0:
                    caracter = 'N';
                    break;
                case 1:
                    caracter = 'S';
                case 2:
                    caracter = 'V';
                    break;
                case 3:
                    caracter = 'E';
            }
            populatieTemp[i][pozitieGena] = caracter;
        }
    }
}

void afiseazaSolutie() {
    cout << "\n\n\n\nSOLUTIA ESTE: \n";
    for (int i = 0; i < lungimeSol; i++) {
        cout << solutie[i] << " ";
    }
}

int calculeazaFitness() {
    // numara cate piese din solutia curenta sunt in aceeasi pozitie
    // cu piesele din starea finala
    int pozitiiCorecte = 0;
    for (int i = 0; i < DIM_TABLA; i++) {
        for (int j = 0; j < DIM_TABLA; j++) {
            if (stareCurenta[i][j] == stareFinala[i][j]) {
                pozitiiCorecte++;
            }
        }
    }//cout<<pozitiiCorecte;
    return pozitiiCorecte;
}

void actualizeazaPopulatie(){
    for(int i=0; i<DIM_POP; i++){
        for(int j=0; j<DIM_SOL; j++){
            populatie[i][j] = populatieTemp[i][j];
        }
    }
}

void initializeazaStareCurenta() {
    for (int i = 0; i < DIM_TABLA; i++) {
        for (int j = 0; j < DIM_TABLA; j++) {
            stareCurenta[i][j] = stareInitiala[i][j];
        }
    }
}

int verificaStareCurenta() {
    for (int i = 0; i < DIM_TABLA; i++) {
        for (int j = 0; j < DIM_TABLA; j++) {
            if (stareCurenta[i][j] != stareFinala[i][j]) {
                return 0;
            }
        }
    }

    return 1;
}

int verificaConditieOprire() {

    for(int i = 0; i < DIM_POP; i++) {
        initializeazaStareCurenta();
        lungimeSol = 0;

        for(int j = 0; j < DIM_SOL; j++) {
            char directie = populatie[i][j];
            switch (directie) {
            case 'N':
                //Inainte de a face mutarea verific daca e valida
                if (iPozitieLibera-1 < 0) {
                    //daca e invalida se ignora
                    continue;
                }
                //Se gliseaza pozitia libera
                swap(stareCurenta[iPozitieLibera][jPozitieLibera], stareCurenta[iPozitieLibera-1][jPozitieLibera]);
                //Se actualizeaza i-ul si j-ul pozitiei libere
                iPozitieLibera--;
                break;
            case 'S':
                if (iPozitieLibera+1 == DIM_TABLA) {
                    continue;
                }
                swap(stareCurenta[iPozitieLibera][jPozitieLibera], stareCurenta[iPozitieLibera+1][jPozitieLibera]);
                iPozitieLibera++;
                break;
            case 'V':
                if (jPozitieLibera-1 < 0) {
                    continue;
                }
                swap(stareCurenta[iPozitieLibera][jPozitieLibera], stareCurenta[iPozitieLibera][jPozitieLibera-1]);
                jPozitieLibera--;
                break;
            case 'E':
                if (jPozitieLibera+1 == DIM_TABLA) {
                    continue;
                }
                swap(stareCurenta[iPozitieLibera][jPozitieLibera], stareCurenta[iPozitieLibera][jPozitieLibera+1]);
                jPozitieLibera++;
            }

            //Se adauga directia la solutie
            solutie[lungimeSol] = directie;
            lungimeSol++;

            //Daca s-a ajuns la starea finala mai repede se opreste cautarea
            if (verificaStareCurenta()) {
                return 1;
            }
        }
    }
    return 0;
}

void afiseazaPopulatie() {
    cout << "\n\n\nAFISARE POPULATIE:";
    for (int i = 0; i < DIM_POP; i++) {
        cout << "\nAFISARE INDIVID:\n";
        for (int j = 0; j < DIM_SOL; j++) {
            cout << populatie[i][j] << " ";
        }
    }
}
ofstream fout("iesire");
void scriePopulatieFisier(){


    fout << "\n\n\nAFISARE POPULATIE:";
    for (int i = 0; i < DIM_POP; i++) {
        fout << "\nAFISARE INDIVID:\n";
        for (int j = 0; j < DIM_SOL; j++) {
            fout << populatie[i][j] << " ";
        }
    }
}

int main() {

    genereazaPopulatieInitiala();

    while(verificaConditieOprire() == 0) {
            //afiseazaPopulatie();
            scriePopulatieFisier();
            vector<pair<int, int>> parinti = selectie();
            recombinare(parinti);
            mutatie();
            actualizeazaPopulatie();
    }

    afiseazaSolutie();

    return 0;
}
