#pragma once 

#include <iostream>
#include <vector>
#include <deque>
#include <time.h>
#include <pthread.h>
#include <omp.h>

std::deque<std::vector<std::vector<int>>> list;

class Processor{
    private:
    int id, cores, rc = 1, rb = 1, failure = 1;
    float failureP, probRc, probRb, TRc, TRb, TRepair;

    public:
    std::vector<std::vector<int>> generarMatriz(int n, int m);
    void emparejar();
    void multiplicar(std::vector<std::vector<int>> A, 
    std::vector<std::vector<int>> B);
    
};