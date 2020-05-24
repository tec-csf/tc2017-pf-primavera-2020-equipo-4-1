#include "Processor.hpp"

using namespace std;

vector<vector<int>> Processor::generarMatriz(int n, int m){
    vector<vector<int>> vec(n, vector<int> (m,0));

    cout<<"filas: "<<vec.size()<<"\tcolumnas: "<<vec[0].size()<<endl;

    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            vec[i][j] = rand() % 9;
        }
    }

    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++){ 
            cout<< vec[i][j]<< " "; 
        } 
        cout<< "\n"; 
    }
    cout<< "\n"; 

    return vec;
}

void Processor::emparejar(){
    if (list.front()[0].size()==list.back().size())
    {
        if(list.size()>1)
        {
            cout<<"La primera y última matriz de la cola son compatibles"<<endl;
            multiplicar(list.front(), list.back());
            list.pop_front(); list.pop_back();
            list.shrink_to_fit();
        }
    }

    else
    {
        cout<<"NO hay matrices compatibles"<<endl;
    }
    
    cout<<"COLA: "<<list.size()<<endl<<endl;
}

void Processor::multiplicar(vector<vector<int>> A, 
vector<vector<int>> B){
    vector<vector<int>> C(A.size(), vector<int> (B[0].size(),0));

    for(int i=0; i<A.size(); i++)
    {
        for(int j=0; j<B[0].size(); j++)
        {
            for(int k=0; k<A[0].size(); k++) 
            {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }

    for (int i = 0; i < C.size(); i++) { 
        for (int j = 0; j < C[0].size(); j++){ 
            cout<< C[i][j]<< " "; 
        } 
        cout<< "\n"; 
    }
}