#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <time.h>
#include <omp.h>
#include <unistd.h>

using namespace std;

struct arg_struct {
    vector<vector<int>> *arg1;
    vector<vector<int>> *arg2;
};

vector<vector<int>> generarMatriz(int n, int m)
{
    vector<vector<int>> vec(n, vector<int>(m, 0));

    //cout << "filas: " << vec.size() << "\tcolumnas: " << vec[0].size() << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            vec[i][j] = rand() % 9;
        }
    }

    /*
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << vec[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    */

    return vec;
}

void * multiplicar(void * param)
{
    arg_struct *temp = (arg_struct *) param;
    vector<vector<int>> m1 = *(temp->arg1);
    vector<vector<int>> m2 = *(temp->arg2);
    //vector<vector<int>> C(m1.size(), vector<int>(m2.size()));

    printf("I am M1\n");

    for (auto i : m1){
        for (auto j : i){
            printf("%d ", j);
        }

        printf("\n");
    }

    printf("I am M2\n");

    for (auto i : m2){
        for (auto j : i){
            printf("%d ", j);            
        }

        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < m1.size(); i++)
    {
        for (int j = 0; j < m2[0].size(); j++)
        {
            int a = 0;

            for (int k = 0; k < m1[0].size(); k++)
            {
                a += m1[i][k] * m2[k][j];
            }

            cout << a << " ";
        }

        cout << endl;
    }
}

bool emparejar(deque<vector<vector<int>>> list)
{
    if (list.front()[0].size() == list.back().size())
    {
        if (list.size() > 1)
        {
            //cout << "La primera y última matriz de la cola son compatibles" << endl;
            return true;
        }
    }

    return false;
}

#endif