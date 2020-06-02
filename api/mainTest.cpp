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
#include <fstream>

#define ITEMS INT_MAX
#define BSIZE 100

#define NP 1
int NC; //definition of global variable as  number of processors
int NCORES; //definition of global variable as number of cores
float alpha; //definition of alpha varible as duration event rc
float beta; //definition of beta variable as duration of event rb
float delta; //definiton of delta as duration of creating matrix's
float notgamma; //defition of notgamma varible as duration of poping elements
int c; // definition of global variable as probability of rc
time_t timeSim; //definition of global variable as duration of the simulation
int x; //definition of variable for the poisson distribution 
int nFail = 0;
int nFinish = 0;
vector <int> vec;
ofstream fout; 
ofstream fout2;
  


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t consume = PTHREAD_COND_INITIALIZER;

void *  productor(void *);
void *  consumidor(void *);

int in = 0, out = 0, count = 0;
int contador = 0;
int contador2 = 0;
bool globalFail=false;
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

int multiplicar(vector<vector<int>> A, vector<vector<int>> B)
{
    vector<vector<int>> C(A.size(), vector<int> (B[0].size(),0));
    omp_set_num_threads(NCORES);
	//poisson
	int eventRb;
	int eventRc;
	#pragma omp parallel for
    for(int i=0; i<A.size(); i++)
    {
		//srand(time(0));
				int e = (rand()% 100);
    			int xP = rand()+2;
    			int poissonD = (1/x) * (log( 1 + xP));
				// cout<<"this is poisson "<<poissonD<<endl;
				// cout<<"this is e "<<e<<endl;
		
		if (e<=poissonD)
		{
			int r = (rand() % 100);
				if (r<=c&&globalFail==false)
				{
					cout<<"recovery time"<<endl;
					globalFail=true;
					sleep(beta);
					eventRc=2;
					globalFail=false;
				//break;
				}
			if (r<=(100-c)&&globalFail==false)
				{
					cout<<"reboot"<<endl;
					globalFail=true;
					eventRb=1;
					sleep(alpha);
				}
		}
		
		//continue;
        printf("hilo: %d\n", omp_get_thread_num());
        for(int j=0; j<B[0].size(); j++)
        {
            for(int k=0; k<A[0].size(); k++) 
            {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
		//if rc rb
    }
    /*for (int i = 0; i < C.size(); i++) { 
        for (int j = 0; j < C[0].size(); j++){ 
            cout<< C[i][j]<< " "; 
        } 
        cout<< "\n"; 
    }*/
	if (eventRb == 1)
	{
		++nFail;
		return 2;
	}
	else if(eventRc == 2)
	{
		++nFail;
		return 3;
		
	}else{
		return 0;
	}
}

void imprimirMatrices(vector<int> vec, bool hold, int nPro, int status, int proT, int nFinish, int nFail)
{
		fout.open("./../frontend/elements/sility/prueba2.txt", std::ios_base::app); 
		
		if (hold == true)
		{
				fout << "1," << vec[0] << ",1,0,"<<nPro<<","<<status<<","<<proT<<","<<nFinish<<","<<nFail<<"\n";
		}else if (hold == false)
		{
				fout << "0," << vec[0] << ",0,1,"<<nPro<<","<<status<<","<<proT<<","<<nFinish<<","<<nFail<<"\n";
		}
		
		fout.close();
		
}

void imprimirResultados(int nFinish, int nFail)
{
		fout.open("./../frontend/elements/sility/resultados.txt", ios::out); 
		
				fout << nFinish <<","<<nFail;
		
		fout.close();
		
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
            //cout<<"NO hay matrices compatibles"<<endl;
        }
  }
        cout<<"COLA: "<<list.size()<<endl<<endl;
		return true;
}
void asignarValores(int processsors, int cores, float valalpha, float valbeta, float valdelta, float valnotgamma, int valc, time_t valtimeSim, int valx ){
	NC=processsors;
	NCORES=cores;
	alpha=1/valalpha;
	beta=1/valbeta;
	delta=valdelta;
	notgamma=valnotgamma;
	c=valc;
	timeSim=valtimeSim;
	x=valx;
}

int main(int argc, char *argv[])
{
	asignarValores(atoi(argv[1]), atoi(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]),atof(argv[6]), atof(argv[7]),atoi(argv[8]),atoi(argv[9]));

	srand(time(NULL));
	pthread_t hilos[NP+NC];
	int result, i, nh;

	fout.open("./../frontend/elements/sility/prueba2.txt",ios::out); 

	fout2.open("./../frontend/elements/sility/resultados.txt",ios::out); 

	fout << "matrizCreada,idMatriz,hold,mult,nProces,working,procesT,nFinish,nFail\n";

	
	fout.close();

	fout2.close();
	
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
	int flagrb;
	int i;
	int id = (long) arg;
	int status = 0;
	printf("--- Inicia consumidor %d\n", id);
		
	for(i = 0; i < ITEMS; ++i)
	{
		sleep(rand()%2);
		pthread_mutex_lock(&mutex);
		if (count > 0)
		{
			printf("C%d --- Voy a multiplicar\n", id);
			flagrb = multiplicar(buffer[out], buffer[out+1]);
			cout<<"+++++ ---"<< flagrb <<endl;
			vec.push_back(out);
			vec.push_back(out+1);
			status = 1;
			imprimirMatrices(vec,false,id,status,NC,nFinish,nFail);
			if (flagrb == 2)
			{
				list.push_back(buffer[out]);
				list.push_back(buffer[out+1]);
				printf("C%d --- Se reciclo el elemento %d \n", id, buffer[out]);
				globalFail = false;
				status = 2;
				cout<<"ENTRE A RB"<<endl;
				imprimirMatrices(vec,false,id,status,NC,nFinish,nFail);
				vec.pop_back();
				vec.pop_back();
			}
			else if(flagrb == 3){
				status = 3;
				cout<<"ENTRE A RC"<<endl;
				imprimirMatrices(vec,false,id,status,NC,nFinish,nFail);
				vec.pop_back();
				vec.pop_back();
				for(int i = 0; i < list.size()-1; i++)
				{
					if (list[i][0].size()==list.back().size())
        			{
						sleep(delta);
						list.erase(list.begin()+i); 
                		list.pop_back();
						break;
					}
				}
				contador2++;
			}else{
				printf("C%d --- Se consumió el elemento %d \n", id, buffer[out]);
				++nFinish;
				status = 0;
				imprimirMatrices(vec,false,id,status,NC,nFinish,nFail);
				vec.pop_back();
				vec.pop_back();
				for(int i = 0; i < list.size()-1; i++)
				{
					if (list[i][0].size()==list.back().size())
        			{
						sleep(delta);
						list.erase(list.begin()+i); 
                		list.pop_back();
						break;
					}
				}
				contador2++;
			}
			
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
		imprimirResultados(nFinish,nFail);
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
			vec.push_back(in);
			imprimirMatrices(vec,true,id,0,NC,nFinish,nFail);
			vec.pop_back();

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
