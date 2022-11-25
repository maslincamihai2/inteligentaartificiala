#include <iostream>
#include <vector>

using namespace std;

int const DIM_TABLA = 3;
// Pentru tabla 3*3 sunt necesare maxim 31 miscari
int const DIM_SOL = 31;
int const DIM_POP = 200;
int const RATA_MUT = 10;

char populatie[DIM_POP][DIM_SOL];
char populatieTemp[DIM_POP][DIM_SOL];

int stareInitiala[][DIM_TABLA] = {
    {2, 0, 4},
    {7, 6, 3},
    {5, 1, 8}
};

int stareFinala[][DIM_TABLA] = {
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}
};

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

    for(int i=0; i<DIM_POP; i+=2){
        //extragem pozitiile parintilor
        int pozitieParinte1 = parinti[i].first;
        int pozitieParinte2 = parinti[i].second;

        // alegem punct de taietura la intamplare
        int pozitieTaietura = rand()%DIM_SOL;

        // copiem genele pana la pct de taietura din parinte1 in copil1
        for(int j=0; j<pozitieTaietura; j++){
            populatieTemp[i][j] = populatie[pozitieParinte1][j];
        }
        // copiem genele de la pct de taietura din parinte2 in copil1
        for(int j=pozitieTaietura; j<DIM_SOL; j++){
            populatieTemp[i][j] = populatie[pozitieParinte2][j];
        }

        // copiem genele pana la pct de taietura din parinte2 in copil2
        for(int j=0; j<pozitieTaietura; j++){
            populatieTemp[i+1][j] = populatie[pozitieParinte2][j];
        }
        // copiem genele de la pct de taietura din parinte1 in copil2
        for(int j=pozitieTaietura; j<DIM_SOL; j++){
            populatieTemp[i+1][j] = populatie[pozitieParinte1][j];
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

}

int calculeazaFitness() {
    // numara cate piese din solutia curenta sunt in aceeasi pozitie
    // cu piesele din starea finala
    //NETERMINAT------------------------------------------------------
    int pozitiiCorecte = 0;
    return pozitiiCorecte;
}

void actualizeazaPopulatie(){
    for(int i=0; i<DIM_POP; i++){
        for(int j=0; j<DIM_SOL; j++){
            populatie[i][j] = populatieTemp[i][j];
        }
    }
}

int verificaConditieOprire() {
    //NETERMINAT------------------------------------------------------

    if (calculeazaFitness() == DIM_TABLA*DIM_TABLA) {
        return 1;
    }
    return 0;
}

int main() {

    genereazaPopulatieInitiala();

    while(verificaConditieOprire() == 0) {
            vector<pair<int, int>> parinti = selectie();
            recombinare(parinti);
            mutatie();
            actualizeazaPopulatie();
    }

    afiseazaSolutie();

    return 0;
}
