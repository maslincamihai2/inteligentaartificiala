#include <iostream>

using namespace std;

int const DIM_TABLA = 3;
// Pentru tabla 3*3 sunt necesare maxim 31 miscari
int const DIM_SOL = 31;
int const DIM_POP = 200;

char populatie[DIM_POP][DIM_SOL];

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

void selectie() {

}

void recombinare() {

}

void mutatie() {

}

void afiseazaSolutie() {

}

int calculeazaFitness() {

}

int verificaConditieOprire() {
    return 0;
}

int main() {

    genereazaPopulatieInitiala();

    while(verificaConditieOprire() == 0) {
            selectie();
            recombinare();
            mutatie();
    }

    afiseazaSolutie();

    return 0;
}
