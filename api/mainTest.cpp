/*
  Solución al problema del productor-consumidor utilizando variables de condición
  - NP productores y NC consumidores
  - Se utiliza pthread_cond_broadcast()
*/
using namespace std;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <cstdint>
#include <vector>
#include <time.h>
#include <omp.h>
#include <limits.h>
#include <math.h>

#define ITEMS 1000
#define BSIZE 100

#define NP 1
#define NC 4
#define NCORES 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t consume = PTHREAD_COND_INITIALIZER;

void *  productor(void *);
void *  consumidor(void *);

int in = 0, out = 0, count = 0;
int contador = 0;
int contador2 = 0; 
vector<vector<int>> buffer[BSIZE];

vector<vector<vector<int>>> list;

using namespace std;

vector<vector<int>> generarMatriz(int n, int m)
{
    vector<vector<int>> vec(n, vector<int> (m,0));
    cout<<"***filas: "<<vec.size()<<"\tcolumnas: "<<vec[0].size()<<endl;
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            vec[i][j] = rand() % 9;
        }
    }
    /*for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++){ 
            cout<< vec[i][j]<< " "; 
        } 
        cout<< "\n"; 
    }
    cout<< "\n";*/

    return vec;
}

void multiplicar(vector<vector<int>> A, vector<vector<int>> B)
{
    vector<vector<int>> C(A.size(), vector<int> (B[0].size(),0));
    omp_set_num_threads(NCORES);
    #pragma omp parallel for 
    for(int i=0; i<A.size(); i++)
    {
        printf("hilo: %d\n", omp_get_thread_num());
        for(int j=0; j<B[0].size(); j++)
        {
            for(int k=0; k<A[0].size(); k++) 
            {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    /*for (int i = 0; i < C.size(); i++) { 
        for (int j = 0; j < C[0].size(); j++){ 
            cout<< C[i][j]<< " "; 
        } 
        cout<< "\n"; 
    }*/
}

bool emparejar()
{
    bool flag = true;
    for(int i = 0; i < list.size()-1; i++)
    {
        cout<<list[i][0].size()<<" X "<<list.back().size()<<endl;
        if (list[i][0].size()==list.back().size())
        {
            if(list.size()>1)
            {
                cout<<"Se encontraron matrices compatibles"<<endl;
                //multiplicar(list[i], list.back());
                //cout<<"multiplicó"<<endl;
                //list.erase(list.begin()+i); 
                //list.pop_back();
                //cout<<"eliminó"<<endl;
                flag = false;
				return false;
            }
        }
        else if (flag)
        {
            cout<<"NO hay matrices compatibles"<<endl;
        }
  }
        cout<<"COLA: "<<list.size()<<endl<<endl;
		return true;
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	pthread_t hilos[NP+NC];
	int result, i, nh;
	
	//Crear los hilos
	for (i = 0; i < NP; ++i)
	{
		result = pthread_create(&hilos[i], NULL, productor, (void *) i);
		if (result)
			printf("Error al crear el productor \n");
	}
	
	for (i = 0; i < NC; ++i )
	result = pthread_create(&hilos[NP+i], NULL, consumidor, (void *)i);
	if (result)
		printf("Error al crear el consumidor \n");
	
		
	/* Esperar a que terminen los hilos */
	nh  = NP + NC;
	for(i = 0; i < nh; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (result)
			printf("Error al adjuntar el hilo %d \n", i);
	}

	for(int x = 0; x < BSIZE;x++)
	{
		for (int i = 0; i < buffer[x].size(); i++) { 
			for (int j = 0; j < buffer[x][0].size(); j++){ 
				cout<< buffer[x][i][j]<< " "; 
			} 
			cout<< "\n"; 
		}
		cout<< "\n"; 
	}
	
	/* Garantizar que se liberen los recursos */
	pthread_exit(NULL);
	return 0;
}

void * consumidor(void * arg)
{
	int i;
	int id = (long) arg;
	
	printf("--- Inicia consumidor %d\n", id);
		
	for(i = 0; i < ITEMS; ++i)
	{
		sleep(rand()%2);
		pthread_mutex_lock(&mutex);
		if (count > 0)
		{
			printf("C%d --- Voy a multiplicar\n", id);
			multiplicar(buffer[out], buffer[out+1]);
			printf("C%d --- Se consumió el elemento %d \n", id, buffer[out]);

			for(int i = 0; i < list.size()-1; i++)
			{
				if (list[i][0].size()==list.back().size())
        		{
					list.erase(list.begin()+i); 
                	list.pop_back();
					break;
				}
			}
			contador2++;
			cout<<"Consumidos: "<<contador2<<endl;
			out += 2;
			out %= BSIZE;
			count -= 2;
			if (count == (BSIZE-2)) pthread_cond_broadcast(&produce);
		}
		else {
			printf("-------------- Consumidor %d se durmió ------------\n", id);
			pthread_cond_wait(&consume, &mutex);
			printf("-------------- Consumidor %d se despertó ------------\n", id);
		}
		 
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}

void * productor(void * arg)
{
	bool flag = true;
	int i;
	int id = (long) arg;
	
	/* Producir elementos */
	printf("+++ Inicia productor %d\n", id);
	
	for(i = 0; i < ITEMS; ++i)
	{
		sleep(rand()%1);
		pthread_mutex_lock(&mutex);
		if (count < BSIZE)
		{
			while (flag)
			{
				list.push_back(generarMatriz(rand() % 8 + 2, rand() % 8 + 2));
        		flag = emparejar();
			}

			for(int i = 0; i < list.size()-1; i++)
			{
				if (list[i][0].size()==list.back().size())
        		{
					buffer[in] = list[i];
                	buffer[in+1] = list.back();
					list.erase(list.begin()+i); 
                	list.pop_back();
					break;
				}
			}

			flag = true;
			printf("P%d --- Se produjo el elemento %d \n", id, buffer[in]);
			contador++;
			cout<<"Producido: "<<contador<<endl;
			in += 2; 
			cout<<in<<endl;
			in %= BSIZE;
			count += 2;
			cout<<count<<endl;
			if (count == 2) pthread_cond_broadcast(&consume);
		}
		else {
			printf("-------------- Productor %d se durmió ------------\n", id);
			pthread_cond_wait(&produce, &mutex);
			printf("-------------- Productor %d se despertó ------------\n", id);
		}
		 
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}
