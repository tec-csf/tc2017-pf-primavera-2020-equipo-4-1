#ifndef MATRICES
#define MATRICES

#include <iostream>
#include <vector>
#include <deque>
#include <time.h>
#include <omp.h>

using namespace std;

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

void multiplicar(vector<vector<int>> A, vector<vector<int>> B)
{
    vector<vector<int>> C(A.size(), vector<int>(B[0].size(), 0));

    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B[0].size(); j++)
        {
            for (int k = 0; k < A[0].size(); k++)
            {
                C[i][j] += A[i][k] * B[k][j];
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