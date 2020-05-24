#include "Processor.hpp"

using namespace std;

int main(){
    vector<pthread_t> threads;
    
    srand(time(NULL));

    for(int i = 0; i < 10; i++)
    {
        list.shrink_to_fit();
        list.push_back(generarMatriz(rand() % 4 + 2,(rand() % 4 + 2)));
        emparejar();
    }

    return 0;
}