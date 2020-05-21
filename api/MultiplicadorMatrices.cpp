#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
using namespace std;

vector<vector<int>> generarMatriz(int n, int m)
{
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

void emparejar(queue<vector<vector<int>>> lista)
{
    if (lista.front()[0].size()==lista.back().size())
    {
        cout<<"La primera y última matriz de la cola son compatibles"<<endl;
    }
    else
    {
        cout<<"NO hay matrices compatibles"<<endl;
    }
}

int main()
{
    //vector<tuple<vector<vector<int>>,int>> list;
    queue<vector<vector<int>>> list;

    srand(time(NULL));

    list.push(generarMatriz(rand() % 4 + 2,(rand() % 4 + 2)));
    list.push(generarMatriz(rand() % 4 + 2,(rand() % 4 + 2)));

    emparejar(list);

    return 0;
}