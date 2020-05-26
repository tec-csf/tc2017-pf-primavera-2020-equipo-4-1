//#include "Processor.hpp"
#include "Matrices.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <time.h>
#include <pthread.h>
#include <omp.h>
#include <limits>
#include <math.h>
#include <unistd.h>

using namespace std;

struct arg_struct {
    deque<vector<vector<int>>>::iterator arg1;
    deque<vector<vector<int>>>::iterator arg2;
};

struct thread {
    pthread_t tid;
    bool isWorking = false;
};

class Processor {
    private:
    int id, cores, rc = 1, rb = 1, failure = 1;
    float failureP, probRc, probRb, TRc, TRb, TRepair;

    public:
    void setEverything(int anID, int amountOfCores, float alpha, float beta,
                    float delta, float gamma, float c);
    int calculatePoisson(int x);
};

void Processor::setEverything(int anID, int amountOfCores, float alpha, 
                                float beta, float delta, float gamma, float c)
{
    id = anID;
    cores = amountOfCores;
    failureP = 1 / gamma;
    probRc = c;
    probRb = 1 - c;
    TRc = 1 / beta;
    TRb = 1 / alpha;
    TRepair = 1 / delta;
}

int Processor::calculatePoisson(int x){
    srand(time(0));
    float r = rand() / INT_MAX;
    int xPoisson = (1 / x) * log(1 - r);

    return xPoisson;
}

int main(int argc, char *argv[]){
    int amountOfProcessors = atoi(argv[6]), amountOfCores = atoi(argv[7]), i;
    float alpha = atof(argv[2]), beta = atof(argv[3]), delta = atof(argv[4]), 
            gamma = atof(argv[5]), c = atof(argv[8]);
    int timeSim = atoi(argv[9]);
    bool canTheyMultiply = false;
    struct arg_struct args;

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

            for (i = 0; i < amountOfProcessors; i++){
                deque<vector<vector<int>>>::iterator iter1 = list.front();
                deque<vector<vector<int>>>::iterator iter2 = list.back();
                tdata temp ={iter1, iter2};
                tdata *datos = (tdata *)malloc(sizeof(tdata));        
                memcpy(datos, &temp, sizeof(tdata))
                pthread_create(&listOfThreads[i].tid, NULL, multiplicar, datos);
            }

            multiplicar(list.front(), list.back());
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