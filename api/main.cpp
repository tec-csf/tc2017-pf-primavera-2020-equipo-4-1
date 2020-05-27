#include "Processor.hpp"
#include "Matrices.hpp"

using namespace std;

struct thread {
    pthread_t tid;
    bool isWorking = false;
};

int main(int argc, char *argv[]){
    int amountOfProcessors = atoi(argv[6]);
    int amountOfCores = atoi(argv[7]);
    float alpha = atof(argv[2]);
    float beta = atof(argv[3]);
    float delta = atof(argv[4]);
    float gamma = atof(argv[5]);
    float c = atof(argv[8]);
    int timeSim = atoi(argv[9]);
    bool canTheyMultiply = false;
    struct arg_struct args;
    int i;

    srand(time(NULL));

    vector<thread> listOfThreads(amountOfProcessors);
    vector<Processor> processors(amountOfProcessors);

    for (i = 0; i < amountOfProcessors; i++){
        processors[i].setEverything(i, amountOfCores, alpha, beta, delta, gamma, c);
    }

    while(true){
        list.shrink_to_fit();
        list.push_back(generarMatriz(rand() % 4 + 2, (rand() % 4 + 2)));
        canTheyMultiply = emparejar();
        if (canTheyMultiply == true){
            cout << "COLA: " << list.size() << endl;
                vector<vector<int>> iter1 = list.front();
                vector<vector<int>> iter2 = list.back();
                /* list pop list back */
                /* tdata temp ={iter1, iter2}; */
                arg_struct *datos = (arg_struct *) malloc(sizeof(arg_struct));
                datos-> arg1 = iter1;
                datos-> arg2 = iter2;
                //memcpy(datos, &temp, sizeof(tdata))
                pthread_create(&listOfThreads[i].tid, NULL, multiplicar, datos);
                list.pop_front();
                list.pop_back();
                list.shrink_to_fit();
        }

        /*
        else {
            cout << "The matrices were not compatible." << endl;
        }
        */
    }

    return 0;
}