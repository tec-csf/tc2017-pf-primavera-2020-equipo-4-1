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
    vector<vector<int>> arg1;
    vector<vector<int>> arg2;
};

deque<vector<vector<int>>> list;

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
    vector<vector<int>> C(temp->arg1[0].size(), vector<int>(temp->arg2.size()));

    for (int i = 0; i < temp->arg1.size(); i++)
    {
        for (int j = 0; j < temp->arg2[0].size(); j++)
        {
            for (int k = 0; k < temp->arg1[0].size(); k++)
            {
                C[i][j] += temp->arg1[i][k] * temp->arg2[k][j];
            }
        }
    }

    /*
    for (int i = 0; i < C.size(); i++)
    {
        for (int j = 0; j < C[0].size(); j++)
        {
            cout << C[i][j] << " ";
        }
        cout << "\n";
    }
    */

   //free(temp);
   //pthread_exit(0);
}

bool emparejar()
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