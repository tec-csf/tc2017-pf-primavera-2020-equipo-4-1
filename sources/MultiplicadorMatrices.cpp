#include <iostream>
#include <tuple>
#include <vector>
#include <time.h>
using namespace std;

tuple<vector<vector<int>>, int> generarMatriz(int s)
{
    vector<vector<int>> vec(s, vector<int> (s,0));

    for (int i = 0; i < s; i++)
    {
        for(int j = 0; j < s; j++)
        {
            vec[i][j] = rand() % 9 + 1;
        }
    }
    for (int i = 0; i < s; i++) { 
        for (int j = 0; j < s; j++){ 
            cout<< vec[i][j]<< " "; 
        } 
        cout<< "\n"; 
    }
    cout<< "\n"; 

    return make_tuple(vec, s);
}

void emparejar(vector<tuple<vector<vector<int>>,int>> lista)
{
    for (int i = 0; i < lista.size(); i++)
    {
        for (int j = i+1; j < lista.size(); j++)
        {
            cout<<get<1>(lista[i])<<" - "<<get<1>(lista[j])<<endl;
            if(get<1>(lista[i])==get<1>(lista[j]))
            {
                cout<<"Se encontraron matrices compatibles"<<endl;
                return;
            }
        }
    }
    cout<<"NO hay matrices compatibles"<<endl;
}

int main()
{
    vector<tuple<   ,int>> list;
    srand(time(NULL));
    list.push_back(generarMatriz(rand() % 4 + 2));
    list.push_back(generarMatriz(rand() % 4 + 2));
    list.push_back(generarMatriz(rand() % 4 + 2));


    for (int i = 0; i < list.size(); i++)
    {
        cout<<get<1>(list[i])<<endl;
    }

    emparejar(list);

    return 0;
}
