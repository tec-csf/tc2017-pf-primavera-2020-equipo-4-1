/**
 * Preguntas para Cubells:
 * 1. A que se refiere con "si el ultimo falla el sistema falla"?
 * 2. Por "tiempo promedio de RB/RC" se refiere a que tanto tarde en recuperarse
 *    o rebootearse?
 * 3. El valor de x en el tercer parrafo es igual que el valor de c en el 
 *    segundo?
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct processor
{
  int ID;
  int cores;
  //Probabilty of failure
  float failureP;
  //Probabilty of RC
  float probRc;
  //Probabilty of Rb
  float probRb;
  //Time of rc
  float TRc;
  //Time of rb
  float TRb;
  //Time of repair
  float TRepair;
  //1 = working, 0 = not working
  int rc = 1; 
  int rb = 1;
  int failure = 1; 
};

void insert(processor *arr, int n, int cores, float alpha, float beta, float delta, float gamma, float c)
{
  for (int i = 0; i < n; i++)
  {
    arr[i].ID = i;
    arr[i].cores = cores;
    arr[i].failureP = 1/gamma;
    arr[i].probRc = c;
    arr[i].probRb = 1 - c; 
    arr[i].TRc = 1/beta;
    arr[i].TRb = 1/alpha;
    arr[i].TRepair = 1/delta;
  }
}

int main(){
  int n = 3;
  //pedir usuario antes el n (procesadores)
  processor p[n];
  insert(p,n,3,4,5,6,7,.9);

  for (int i = 0; i < n; i++)
  {
    cout << "Time of RC: " << p[i].TRb << endl;
    //printf("Time of RC %f\n", p[i].TRb);
  }
  
  return 0;
}