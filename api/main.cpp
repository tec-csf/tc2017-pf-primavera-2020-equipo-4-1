#include "Processor.hpp"
#include "Matrices.hpp"

using namespace std;

int main(int argc, char *argv[]){
    int amountOfProcessors = atoi(argv[1]), amountOfCores = atoi(argv[2]);
    float alpha = atof(argv[3]), beta = atof(argv[4]), delta = atof(argv[5]), 
        gamma = atof(argv[6]), c = atof(argv[7]);
    int i;

    srand(time(NULL));

    vector<pthread_t> threads(amountOfProcessors);
    vector<Processor> processors(amountOfProcessors);

    for (i = 0; i < amountOfProcessors; i++){
        processors[i].setEverything(i, amountOfCores, alpha, beta, delta, gamma, c);
    }

    while(true){
        list.shrink_to_fit();
        list.push_back(generarMatriz(rand() % 4 + 2, (rand() % 4 + 2)));
        emparejar();
    }

    return 0;
}